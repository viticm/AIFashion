/**
 * AI Fashion ( https://github.com/viticm/AIFashion )
 * $Id me.h
 * @link https://github.com/viticm/AIFashion for the canonical source repository
 * @copyright Copyright (c) 2017- viticm( viticm.ti@gmail.com )
 * @license
 * @user viticm<viticm.ti@gmail.com>
 * @date 2017/06/09 15:14
 * @uses The me module.
*/
#ifndef AIN_ME_H_
#define AIN_ME_H_

#include "ain/config.h"

//Function for do action.
typedef bool (__stdcall *function_action)();

//The thing of all artificial intelligence do.
typedef struct ain_thing_t {
  
  /* What's me want do things. */
  function_action *want;

  /* What's me doing thing. */
  function_action current;

  /* What's me wait do things. */
  function_action *wait;

} ain_thing_t;

//The me struct.
typedef struct ain_me_t {

  /* What is me from basic way. */
  unsigned char original;
  
  /* Current state bit value. */
  int state;

  /* Current things. */
  ain_thing_t *things;

} ain_me_t;

enum {

  /* Me is thinking. */
  kAinStateThinking = 0,

  /* Me is learning. */
  kAinStateLearning = 1,
};

#endif //AIN_ME_H_
