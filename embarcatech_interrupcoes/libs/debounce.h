#ifndef DEBOUNCE_H
#define DEBOUNCE_H
#include "pico/stdlib.h"

#include <stdbool.h>
#include <stdint.h>

// Função para debouncing de botões
bool debounce(uint32_t gpio);

#endif // DEBOUNCE_H