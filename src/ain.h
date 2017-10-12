/**
 * AI Fashion ( https://github.com/viticm/AIFashion )
 * $Id ain.h
 * @link https://github.com/viticm/AIFashion for the canonical source repository
 * @copyright Copyright (c) 2017- viticm( viticm.ti@gmail.com )
 * @license
 * @user viticm<viticm.ti@gmail.com>
 * @date 2017/09/21 15:49
 * @uses The ain executable software.
*/
#ifndef AIN_H_
#define AIN_H_

#include "ainconf.h"

#define AIN_VERSION_MAJOR	"0"
#define AIN_VERSION_MINOR	"0"
#define AIN_VERSION_NUM		0
#define AIN_VERSION_RELEASE	"1"

#define AIN_VERSION	"Ain " AIN_VERSION_MAJOR "." AIN_VERSION_MINOR
#define AIN_RELEASE	AIN_VERSION "." AIN_VERSION_RELEASE
#define AIN_COPYRIGHT	AIN_RELEASE "  Copyright (C) 2017 by viticm "
#define AIN_AUTHORS	"viticm<viticm.ti@gmail.com>"

/* mark for precompiled code ('<esc>Ain') */
#define AIN_SIGNATURE	"\x1bAin"


#include "aauxlib.h"
#include "alimits.h"


/* Me status. */
#define AIN_OK 0

#endif //AIN_H_
