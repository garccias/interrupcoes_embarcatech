#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "config.h" // Inclui as definições globais
#include <stdint.h>


// Configura os LEDs
void setup_leds() {
    gpio_init(LED_RED);       // Inicializa o pino do LED vermelho
    gpio_set_dir(LED_RED, GPIO_OUT); // Define como saída
}

// Configura os botões com interrupções
void setup_buttons(void (*irq_a)(uint32_t, uint32_t), void (*irq_b)(uint32_t, uint32_t)) {
    // Configura o Botão 
    gpio_init(BUTTON_A);       // Inicializa o pino do Botão A
    gpio_set_dir(BUTTON_A, GPIO_IN); // Define como entrada
    gpio_pull_up(BUTTON_A);    // Habilita resistor pull-up
    gpio_set_irq_enabled_with_callback(BUTTON_A, GPIO_IRQ_EDGE_FALL, true, irq_a);

    // Configura o Botão B
    gpio_init(BUTTON_B);       // Inicializa o pino do Botão B
    gpio_set_dir(BUTTON_B, GPIO_IN); // Define como entrada
    gpio_pull_up(BUTTON_B);    // Habilita resistor pull-up
    gpio_set_irq_enabled_with_callback(BUTTON_B, GPIO_IRQ_EDGE_FALL, true, irq_b);
}