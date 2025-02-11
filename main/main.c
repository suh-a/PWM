#include "pico/stdlib.h"
#include "hardware/pwm.h"

#define SERVO_PIN 22
#define PWM_FREQ 50
#define PWM_WRAP 19999
#define PWM_DIV 125.0f
#define PULSE_MIN 500
#define PULSE_MID 1470
#define PULSE_MAX 2400
#define DELAY_5_SEC 5000
#define SMOOTH_DELAY_MS 10
#define SMOOTH_INCREMENT 5

void set_servo_pulse(uint16_t pulse_width) {
    if (pulse_width > (PWM_WRAP + 1)) {
        pulse_width = PWM_WRAP + 1;
    }
    pwm_set_gpio_level(SERVO_PIN, pulse_width);
}

void smooth_move_servo(uint16_t start, uint16_t end) {
    if (start < end) {
        for (uint16_t pulse = start; pulse <= end; pulse += SMOOTH_INCREMENT) {
            pwm_set_gpio_level(SERVO_PIN, pulse);
            sleep_ms(SMOOTH_DELAY_MS);
        }
    } else {
        for (uint16_t pulse = start; pulse >= end; pulse -= SMOOTH_INCREMENT) {
            pwm_set_gpio_level(SERVO_PIN, pulse);
            sleep_ms(SMOOTH_DELAY_MS);
            if (pulse < SMOOTH_INCREMENT) break;
        }
    }
}

int main() {
    stdio_init_all();
    gpio_set_function(SERVO_PIN, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(SERVO_PIN);
    pwm_set_clkdiv(slice_num, PWM_DIV);
    pwm_set_wrap(slice_num, PWM_WRAP);
    pwm_set_enabled(slice_num, true);
    set_servo_pulse(PULSE_MAX);
    sleep_ms(DELAY_5_SEC);
    set_servo_pulse(PULSE_MID);
    sleep_ms(DELAY_5_SEC);
    set_servo_pulse(PULSE_MIN);
    sleep_ms(DELAY_5_SEC);
    while (true) {
        smooth_move_servo(PULSE_MIN, PULSE_MAX);
        smooth_move_servo(PULSE_MAX, PULSE_MIN);
    }
    return 0;
}
