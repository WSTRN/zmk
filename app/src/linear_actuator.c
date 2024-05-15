/*
 * Copyright (c) 2021 The ZMK Contributors
 *
 * SPDX-License-Identifier: MIT
 */

#include <drivers/behavior.h>
#include <zephyr/logging/log.h>

LOG_MODULE_DECLARE(zmk, CONFIG_ZMK_LOG_LEVEL);

#include <zephyr/drivers/pwm.h>

static const struct pwm_dt_spec pwm_led0 = PWM_DT_SPEC_GET(DT_NODELABEL(pwm_led0));
static const struct pwm_dt_spec pwm_led1 = PWM_DT_SPEC_GET(DT_NODELABEL(pwm_led1));

static int zmk_linear_actuator_init(void) {

    if (!device_is_ready(pwm_led0.dev)) {
        printk("Error: PWM device %s is not ready\n", pwm_led0.dev->name);
        return;
    }
    LOG_INF("Linear actuator initialized");
    pwm_set_pulse_dt(&pwm_led0, pwm_led0.period / 2);
    pwm_set_pulse_dt(&pwm_led1, pwm_led0.period / 2);
    return 0;
}

SYS_INIT(zmk_linear_actuator_init, APPLICATION, CONFIG_APPLICATION_INIT_PRIORITY);