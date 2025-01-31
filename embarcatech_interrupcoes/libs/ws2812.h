#ifndef WS2812_H
#define WS2812_H
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include <stdint.h>    


// Funções públicas
void ws2812_init(PIO pio, uint32_t sm, uint32_t offset, uint32_t pin);
void ws2812_display_number(uint32_t number);

#endif // WS2812_H