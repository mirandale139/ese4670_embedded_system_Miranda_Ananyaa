#include <stdio.h>
#include "pico/stdlib.h"

#define BUTTON_PIN 3

volatile uint32_t rising_edges = 0;    // low to high
volatile uint32_t falling_edges = 0;   // high to low

void button_press(uint gpio, uint32_t events) {

    if (gpio != BUTTON_PIN) return;

    if (events & GPIO_IRQ_EDGE_RISE) {
        rising_edges++;
    }
    if (events & GPIO_IRQ_EDGE_FALL) {
        falling_edges++;
    }
}

int main() {
    stdio_init_all();

    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_PIN);    // idle = 1, pressed = 0

    // Interrupt on both rising and falling edges
    gpio_set_irq_enabled_with_callback(
        BUTTON_PIN,
        GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL,
        true,
        &button_press);


    while (true) {
        printf("rising edges: %d \t falling edges: %d \n", rising_edges, falling_edges);
        sleep_ms(100);
    }
}
