/**
 * AI Fashion ( https://github.com/viticm/AIFashion )
 * $Id asignal.h
 * @link https://github.com/viticm/AIFashion for the canonical source repository
 * @copyright Copyright (c) 2017- viticm( viticm.ti@gmail.com )
 * @license
 * @user viticm<viticm.ti@gmail.com>
 * @date 2017/10/10 15:15
 * @uses The signal module.
*/
#ifndef AIN_SIGNAL_H_
#define AIN_SIGNAL_H_

#include "ain/config.h"

enum {
  kAINSignalWhatsMe = 0,                          //What's me signal.
  kAINSignalThink = 1,                            //Think signal.
  kAINSignalLearn = 2,                            //Learn signal.
};

//The signal of all artificial intelligence accept.
typedef struct ain_signal_t {

  /* Signal operator code. */
  int signal;

  /* The  */

} ain_signal_t;

#endif //AIN_SIGNAL_H_
