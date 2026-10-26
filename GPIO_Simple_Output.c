#include "pico/stdlib.h"

#define BUTTON_PIN 3
#define LED_PIN 15

int main() {
    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_PIN);

    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    gpio_put(LED_PIN, 0);

    bool last_pressed = !gpio_get(BUTTON_PIN);

    while (true) {
        bool pressed = !gpio_get(BUTTON_PIN);

        if (pressed && !last_pressed) {          // press only, not release
            gpio_put(LED_PIN, !gpio_get(LED_PIN));
        }
        last_pressed = pressed;

        sleep_ms(10);
    }
}
