/**
 * AI Fashion ( https://github.com/viticm/AIFashion )
 * $Id mind.h
 * @link https://github.com/viticm/AIFashion for the canonical source repository
 * @copyright Copyright (c) 2017- viticm( viticm.ti@gmail.com )
 * @license
 * @user viticm<viticm.ti@gmail.com>
 * @date 2017/06/09 14:52
 * @uses The mind module.
 *       What's the normal mind doing?
 *       ain_signal->ain_thinking->ain_learning ...
*/
#ifndef AIN_MIND_H_
#define AIN_MIND_H_

#include "ain/event.h"
#include "ain/me.h"

/* Mind thinking and return now status. */
int ain_thinking(ain_me_t *me);

/* Mind learning and return now status. */
int ain_learning(ain_me_t *me);

/* Mind accept a signal and return now status. */
int ain_signal(ain_me_t *me, ain_signal_t *signal);

#endif //AIN_MIND_H_
