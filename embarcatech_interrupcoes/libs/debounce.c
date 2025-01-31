#include "debounce.h"
#include "pico/time.h"
#include "config.h"
#include "pico/stdlib.h"
#include <stdint.h>



// Função de debouncing
bool debounce(uint32_t gpio) {
    static uint64_t last_interrupt_time = 0;
    uint64_t interrupt_time = time_us_64();

    // Verifica se o tempo desde a última interrupção é maior que 200 ms
    if (interrupt_time - last_interrupt_time > 200000) {
        last_interrupt_time = interrupt_time;
        return true;
    }
    return false;
}
