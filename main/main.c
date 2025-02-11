#include "pico/stdlib.h"
#include "hardware/pwm.h"

#define SERVO_PIN 22
#define LED_BLUE 12

#define PWM_FREQ 50
#define PWM_WRAP 19999
#define PWM_DIV 125.0f

#define PULSE_MIN 500
#define PULSE_MID 1470
#define PULSE_MAX 2400

#define DELAY_5_SEC 5000

#define SMOOTH_DELAY_MS 10
#define SMOOTH_INCREMENT 5

// Período do piscar do LED durante o loop (em milissegundos)
#define LED_BLINK_PERIOD_MS 250

// Função que define o pulso do servo
void set_servo_pulse(uint16_t pulse_width) {
    if (pulse_width > (PWM_WRAP + 1)) {
        pulse_width = PWM_WRAP + 1;
    }
    pwm_set_gpio_level(SERVO_PIN, pulse_width);
}

// Função original para mover o servo suavemente (mantida inalterada)
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

// Nova função para mover o servo com a LED piscando durante o movimento
void smooth_move_servo_blink(uint16_t start, uint16_t end) {
    int blink_counter = 0;
    bool led_state = false; // Inicia com LED desligada
    int iterations_per_blink = LED_BLINK_PERIOD_MS / SMOOTH_DELAY_MS; 
    
    if (start < end) {
        for (uint16_t pulse = start; pulse <= end; pulse += SMOOTH_INCREMENT) {
            pwm_set_gpio_level(SERVO_PIN, pulse);
            blink_counter++;
            if (blink_counter >= iterations_per_blink) {
                led_state = !led_state;
                gpio_put(LED_BLUE, led_state);
                blink_counter = 0;
            }
            sleep_ms(SMOOTH_DELAY_MS);
        }
    } else {
        for (uint16_t pulse = start; pulse >= end; pulse -= SMOOTH_INCREMENT) {
            pwm_set_gpio_level(SERVO_PIN, pulse);
            blink_counter++;
            if (blink_counter >= iterations_per_blink) {
                led_state = !led_state;
                gpio_put(LED_BLUE, led_state);
                blink_counter = 0;
            }
            sleep_ms(SMOOTH_DELAY_MS);
            if (pulse < SMOOTH_INCREMENT) break;
        }
    }
}

int main() {
    stdio_init_all();

    // Configura o LED azul
    gpio_init(LED_BLUE);
    gpio_set_dir(LED_BLUE, GPIO_OUT);
    // Estado inicial do LED: desligado
    gpio_put(LED_BLUE, 0);

    // Configura o servo
    gpio_set_function(SERVO_PIN, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(SERVO_PIN);
    pwm_set_clkdiv(slice_num, PWM_DIV);
    pwm_set_wrap(slice_num, PWM_WRAP);
    pwm_set_enabled(slice_num, true);

    // Movimentos iniciais do servo com controle da LED:
    // 1º movimento: Servo em 180° (PULSE_MAX) com LED desligada
    set_servo_pulse(PULSE_MAX);
    gpio_put(LED_BLUE, 0);
    sleep_ms(DELAY_5_SEC);

    // 2º movimento: Servo em 90° (PULSE_MID) com LED ligada
    set_servo_pulse(PULSE_MID);
    gpio_put(LED_BLUE, 1);
    sleep_ms(DELAY_5_SEC);

    // 3º movimento: Servo em 0° (PULSE_MIN) com LED desligada
    set_servo_pulse(PULSE_MIN);
    gpio_put(LED_BLUE, 0);
    sleep_ms(DELAY_5_SEC);

    // Loop: movimento suave de 0° a 180° e vice-versa, com a LED piscando durante todo o percurso
    while (true) {
        smooth_move_servo_blink(PULSE_MIN, PULSE_MAX);
        smooth_move_servo_blink(PULSE_MAX, PULSE_MIN);
    }
    return 0;
}
