#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ame.h"
#include "ain.h"

#if !defined(AIN_PROMPT)
#define AIN_PROMPT		"> "
#define AIN_PROMPT2		">> "
#endif

#if !defined(AIN_PROGNAME)
#define AIN_PROGNAME		"ain"
#endif

#if !defined(AIN_MAXINPUT)
#define AIN_MAXINPUT		512
#endif

#if !defined(AIN_INIT_VAR)
#define AIN_INIT_VAR		"AIN_INIT"
#endif

#define AIN_INITVARVERSION	AIN_INIT_VAR AIN_VERSUFFIX

/*
** ain_stdin_is_tty detects whether the standard input is a 'tty' (that
** is, whether we're running lua interactively).
*/
#if !defined(ain_stdin_is_tty)	/* { */

#if defined(AIN_USE_POSIX)	/* { */

#include <unistd.h>
#define ain_stdin_is_tty()	isatty(0)

#elif defined(AIN_USE_WINDOWS)	/* }{ */

#include <io.h>
#include <windows.h>

#define ain_stdin_is_tty()	_isatty(_fileno(stdin))

#else				/* }{ */

/* ISO C definition */
#define ain_stdin_is_tty()	1  /* assume stdin is a tty */

#endif				/* } */

#endif				/* } */


/*
** ain_readline defines how to show a prompt and then read a line from
** the standard input.
** ain_saveline defines how to "save" a read line in a "history".
** ain_freeline defines how to free a line read by ain_readline.
*/
#if !defined(ain_readline)	/* { */

#if defined(AIN_USE_READLINE)	/* { */

#include <readline/readline.h>
#include <readline/history.h>
#define ain_readline(me,b,p)	((void)me, ((b)=readline(p)) != NULL)
#define ain_saveline(me,line)	((void)me, add_history(line))
#define ain_freeline(me,b)	((void)me, free(b))

#else				/* }{ */

#define ain_readline(me,b,p) \
        ((void)me, fputs(p, stdout), fflush(stdout),  /* show prompt */ \
        fgets(b, AIN_MAXINPUT, stdin) != NULL)  /* get line */
#define ain_saveline(me,line)	{ (void)me; (void)line; }
#define ain_freeline(me,b)	{ (void)me; (void)b; }

#endif				/* } */

#endif				/* } */

#define INPUTSTR_MAX (AIN_MAXINPUT * 1024)
#define INPUTFULL_ERR "input string is full"

static const char *progname = AIN_PROGNAME;
static int prompt_type = 0;
static char inputstr[INPUTSTR_MAX];
static int inputlen = 0;

/* Clean the input string. */
static void clean_inputstr() {
  memset(inputstr, 0, sizeof(inputstr));
  inputlen = 0;
}

/* PROMPT type. */
#define PROMPT_NONE 0
#define PROMPT_THINK 1
#define PROMPT_LEARN 2
#define PROMPT_ACTION 3

/*
** Returns the string to be used as a prompt by the interpreter.
*/
static const char *get_prompt (ain_me_t *me) {
  const char *p;
  switch (prompt_type) {
    case PROMPT_THINK:
      p = "(think)" AIN_PROMPT2;
      break;
    case PROMPT_LEARN:
      p = "(learn)" AIN_PROMPT2;
      break;
    case PROMPT_ACTION:
      p = "(action)" AIN_PROMPT2;
      break;
    default:
      p = AIN_PROMPT;
      break;
  }
  UNUSED(me);
  return p;
}

/* Check quit state. */
static int checkquit(ain_me_t *me, const char *str) {
  UNUSED(me);
  if (0 == strcmp("quit", str)) {
    prompt_type = PROMPT_NONE;
    return 0;
  }
  return -1;
}

/* Load from string. */
static void load(ain_me_t *me, const char *str) {
  if (0 == strcmp("think", str)) 
    prompt_type = PROMPT_THINK;
  else if (0 == strcmp("learn", str))
    prompt_type = PROMPT_LEARN;
  else if (0 == strcmp("action", str))
    prompt_type = PROMPT_ACTION;
  else {

  }
}

/* Think from string. */
static void think(ain_me_t *me, const char *str) {
  if (checkquit(me, str) != -1) return;
}

/* Learn from string. */
static void learn(ain_me_t *me, const char *str) {
  if (checkquit(me, str) != -1) return;
}

/* Action from string. */
static void action(ain_me_t *me, const char *str) {
  if (checkquit(me, str) != -1) return;
}

/* Load input line and excute it. */
static int loadline (ain_me_t *me) {
  char buffer[AIN_MAXINPUT];
  char *b = buffer;
  size_t l;
  const char *prmt = get_prompt(me);
  int readstatus = ain_readline(me, b, prmt);
  if (readstatus == 0) return -1; /* empty */
  l = strlen(b);
  if (l > 0 && b[l - 1] == '\n')  /* line ends with newline */
    b[--l] = '\0'; /* remove it */
  if (l + inputlen > INPUTSTR_MAX) {
    clean_inputstr(); /* Get error. */
    ain_writestring(INPUTFULL_ERR, strlen(INPUTFULL_ERR));
    ain_writeline();
    return -2;
  }
  strncat(inputstr, b , l);
  ain_saveline(me, b);
  inputlen += l;
  inputstr[inputlen - 1] = '\0';
  if (';' == b[l - 1]) {
    return AIN_OK;
  }
  return -2;
}

/*
** Do the REPL: repeatedly read (load) a line, evaluate (call) it, and
** print any results.
*/
static void doREPL (ain_me_t *me) {
  clean_inputstr();
  int status;
  const char *oldprogname = progname;
  progname = NULL;  /* no 'progname' on errors in interactive mode */

  while ((status = loadline(me)) != -1) {
    if (AIN_OK == status) {
      switch (prompt_type) {
        case PROMPT_THINK:
          think(me, inputstr);
          break;
        case PROMPT_LEARN:
          learn(me, inputstr);
          break;
        case PROMPT_ACTION:
          action(me, inputstr);
          break;
        default:
          load(me, inputstr);
          break;
      }
      clean_inputstr(); /* Wait the next string. */
    }
  }

  progname = oldprogname;
}

/* Print version information. */
static void print_version (void) {
  ain_writestring(AIN_COPYRIGHT, strlen(AIN_COPYRIGHT));
  ain_writeline();
}

/* bits of various argument indicators in 'args' */
#define has_error	1	/* bad option */
#define has_i		2	/* -i */
#define has_v		4	/* -v */
#define has_e		8	/* -e */
#define has_E		16	/* -E */

/*
** Traverses all arguments from 'argv', returning a mask with those
** needed before running any Ain code (or an error code if it finds
** any invalid argument). 'first' returns the first not-handled argument
** (either the script name or a bad argument in case of error).
*/
static int collectargs (char **argv, int *first) {
  int args = 0;
  int i;
  for (i = 1; argv[i] != NULL; i++) {
    *first = i;
    if (argv[i][0] != '-')  /* not an option? */
        return args;  /* stop handling options */
    switch (argv[i][1]) {  /* else check option */
      case '-':  /* '--' */
        if (argv[i][2] != '\0')  /* extra characters after '--'? */
          return has_error;  /* invalid option */
        *first = i + 1;
        return args;
      case '\0':  /* '-' */
        return args;  /* script "name" is '-' */
      case 'E':
        if (argv[i][2] != '\0')  /* extra characters after 1st? */
          return has_error;  /* invalid option */
        args |= has_E;
        break;
      case 'i':
        args |= has_i;  /* (-i implies -v) *//* FALLTHROUGH */
      case 'v':
        if (argv[i][2] != '\0')  /* extra characters after 1st? */
          return has_error;  /* invalid option */
        args |= has_v;
        break;
      case 'e':
        args |= has_e;  /* FALLTHROUGH */
      case 'l':  /* both options need an argument */
        if (argv[i][2] == '\0') {  /* no concatenated argument? */
          i++;  /* try next 'argv' */
          if (argv[i] == NULL || argv[i][0] == '-')
            return has_error;  /* no next argument or it is another option */
        }
        break;
      default:  /* invalid option */
        return has_error;
    }
  }
  *first = i;  /* no script name */
  return args;
}


int main(int argc, char **argv) {
  UNUSED(argc);
  int script;
  int args = collectargs(argv, &script);
  if (args & has_v)
    print_version();
  ain_me_t me;

  if (args & has_i)
    doREPL(&me);
  else if (script == argc && !(args & (has_e | has_v))) {  /* no arguments? */
    if (ain_stdin_is_tty()) {  /* running in interactive mode? */
      print_version();
      doREPL(&me);  /* do read-eval-print loop */
    }
  }
  return 0;
}
