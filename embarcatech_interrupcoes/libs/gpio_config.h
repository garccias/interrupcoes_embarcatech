#ifndef GPIO_CONFIG_H
#define GPIO_CONFIG_H
#include <stdint.h>

#include "pico/stdlib.h"

void setup_leds(void);
void irq_button_a(unsigned int gpio, uint32_t events);
void irq_button_b(unsigned int gpio, uint32_t events);

#endif // GPIO_CONFIG_H
