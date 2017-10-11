/**
 * AI Fashion ( https://github.com/viticm/AIFashion )
 * $Id aauxlib.h
 * @link https://github.com/viticm/AIFashion for the canonical source repository
 * @copyright Copyright (c) 2017- viticm( viticm.ti@gmail.com )
 * @license
 * @user viticm<viticm.ti@gmail.com>
 * @date 2017/09/22 16:48
 * @uses Auxiliary functions for building Ain libraries(like ain).
*/
#ifndef AIN_AUXILIARY_H_
#define AIN_AUXILIARY_H_

/*
** {==================================================================
** "Abstraction Layer" for basic report of messages and errors(from ain)
** ===================================================================
*/

/* print a string */
#if !defined(ain_writestring)
#define ain_writestring(s,l)   fwrite((s), sizeof(char), (l), stdout)
#endif

/* print a newline and flush the output */
#if !defined(ain_writeline)
#define ain_writeline()        (ain_writestring("\n", 1), fflush(stdout))
#endif

/* print an error message */
#if !defined(ain_writestringerror)
#define ain_writestringerror(s,p) \
        (fprintf(stderr, (s), (p)), fflush(stderr))
#endif

/* }================================================================== */

#endif //AIN_AUXILIARY_H_
