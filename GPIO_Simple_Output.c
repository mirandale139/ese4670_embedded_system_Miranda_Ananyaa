#include <stdio.h>
#include "pico/stdlib.h"

#define BUTTON_PIN 3
#define LED_PIN 15

int main() {
    stdio_init_all();               // enable serial output (USB/UART)

    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_PIN);       // input pull-up: idle = 1, pressed = 0

    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    bool last_pressed = !gpio_get(BUTTON_PIN);  // active-low
    bool LED_LAST_STATE = false;
    gpio_put(LED_PIN, 1);

    while (true) {
        bool pressed = !gpio_get(BUTTON_PIN);
        bool LED_STATE = gpio_get(LED_PIN);

        if (pressed != last_pressed) {      // still a real change       
            gpio_put(LED_PIN, LED_LAST_STATE);

            LED_LAST_STATE = !LED_STATE;
            last_pressed = pressed;
        }

        sleep_ms(10);                            // polling interval
    }
}