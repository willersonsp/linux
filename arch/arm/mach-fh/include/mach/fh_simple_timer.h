/*
 * fh_simple_timer.h
 *
 *  Created on: Jan 22, 2017
 *      Author: duobao
 */

#ifndef FH_SIMPLE_TIMER_H_
#define FH_SIMPLE_TIMER_H_

#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/types.h>
#include <linux/list.h>
#include <linux/time.h>
#include <linux/ktime.h>
#include <linux/timerqueue.h>
#include <mach/pmu.h>
#include <mach/timex.h>
#include <mach/io.h>
#include <mach/fh_predefined.h>

enum simple_timer_state {
	SIMPLE_TIMER_STOP,
	SIMPLE_TIMER_START,
	SIMPLE_TIMER_ERROR,
};

struct fh_simple_timer
{
	struct timerqueue_node		node;
	ktime_t it_interval;	/* timer period */
	ktime_t it_value;	/* timer expiration */
	ktime_t it_delay;
	void (*function) (void *);
	void *param;
};


int fh_simple_timer_interrupt(void);
int fh_simple_timer_create(struct fh_simple_timer* tim);
int fh_timer_start(void);
int fh_simple_timer_init(void);

#endif /* FH_SIMPLE_TIMER_H_ */
