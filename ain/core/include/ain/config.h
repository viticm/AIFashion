/**
 * AI Fashion ( https://github.com/viticm/AIFashion )
 * $Id config.h
 * @link https://github.com/viticm/AIFashion for the canonical source repository
 * @copyright Copyright (c) 2017- viticm( viticm.ti@gmail.com )
 * @license
 * @user viticm<viticm.ti@gmail.com>
 * @date 2017/06/09 14:47
 * @uses The base config file.
 *       Refer: some define from lua code.
*/
#ifndef AIN_CONFIG_H_
#define AIN_CONFIG_H_

/*
@@ AIN_DIRSEP is the directory separator (for submodules).
** CHANGE it if your machine does not use "/" as the directory separator
** and is not Windows. (On Windows Ain automatically uses "\".)
*/
#if defined(_WIN32)
#define AIN_DIRSEP	"\\"
#else
#define AIN_DIRSEP	"/"
#endif

/* }================================================================== */


/*
** {==================================================================
** Marks for exported symbols in the C code
** ===================================================================
*/

/*
@@ AIN_API is a mark for all core API functions.
@@ AINLIB_API is a mark for all auxiliary library functions.
@@ AINMOD_API is a mark for all standard library opening functions.
** CHANGE them if you need to define those functions in some special way.
** For instance, if you want to create one Windows DLL with the core and
** the libraries, you may want to use the following definition (define
** AIN_BUILD_AS_DLL to get it).
*/
#if defined(AIN_BUILD_AS_DLL)	/* { */

#if defined(AIN_CORE) || defined(AIN_LIB)	/* { */
#define AIN_API __declspec(dllexport)
#else						/* }{ */
#define AIN_API __declspec(dllimport)
#endif						/* } */

#else				/* }{ */

#define AIN_API		extern

#endif				/* } */


/* more often than not the libs go together with the core */
#define AINLIB_API	AIN_API
#define AINMOD_API	AINLIB_API

/*
@@ AINI_FUNC is a mark for all extern functions that are not to be
** exported to outside modules.
@@ AINI_DDEF and AINI_DDEC are marks for all extern (const) variables
** that are not to be exported to outside modules (AINI_DDEF for
** definitions and AINI_DDEC for declarations).
** CHANGE them if you need to mark them in some special way. Elf/gcc
** (versions 3.2 and later) mark them as "hidden" to optimize access
** when Ain is compiled as a shared library. Not all elf targets support
** this attribute. Unfortunately, gcc does not offer a way to check
** whether the target offers that support, and those without support
** give a warning about it. To avoid these warnings, change to the
** default definition.
*/
#if defined(__GNUC__) && ((__GNUC__*100 + __GNUC_MINOR__) >= 302) && \
    defined(__ELF__)		/* { */
#define AINI_FUNC	__attribute__((visibility("hidden"))) extern
#else				/* }{ */
#define AINI_FUNC	extern
#endif				/* } */

#define AINI_DDEC	AINI_FUNC
#define AINI_DDEF	/* empty */

/* }================================================================== */


#endif //AIN_CONFIG_H_
