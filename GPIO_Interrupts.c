#include <stdio.h>
#include "pico/stdlib.h"

#define BUTTON_PIN 3

int main() {
    stdio_init_all();               // enable serial output (USB/UART)

    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_PIN);       // input pull-up: idle = 1, pressed = 0

    bool last_pressed = !gpio_get(BUTTON_PIN);  // active-low
    int rising_edge = 0, falling_edge = 0;

    while (true) {
        bool pressed = !gpio_get(BUTTON_PIN);

        if (pressed != last_pressed) {      // still a real change
            if (pressed) {
                rising_edge++;
            }
            else {
                falling_edge++;
            }

            last_pressed = pressed;
        }

        printf("rising edges: %d \t falling edges: %d \n", rising_edge, falling_edge);

        sleep_ms(10);                            // polling interval
    }
}