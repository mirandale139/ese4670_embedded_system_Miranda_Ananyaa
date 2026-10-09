#include <stdio.h>
#include "pico/stdlib.h"

#define BUTTON_PIN 3

int main() {
    stdio_init_all();               // enable serial output (USB/UART)

    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_PIN);       // input pull-up: idle = 1, pressed = 0

    bool last_pressed = !gpio_get(BUTTON_PIN);  // active-low

    while (true) {
        bool pressed = !gpio_get(BUTTON_PIN);

        printf(pressed ? "pressed\n" : "released\n");

        sleep_ms(1);                            // polling interval
    }
}