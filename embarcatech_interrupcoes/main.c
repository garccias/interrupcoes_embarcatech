#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "libs/ws2812.h"   // Biblioteca para controle do WS2812
#include "libs/debounce.h" // Biblioteca para debounce de botões
#include "libs/gpio_config.h" // Configuração dos GPIOs
#include "config.h"        // Definições globais
#include <stdint.h>


int numero = 0; // Variável global para armazenar o número atual (0-9)

// Rotina de Interrupção para Botão A (Incrementa o número)
void irq_button_a(unsigned int gpio, uint32_t events) {
    if (debounce(gpio)) { // Verifica se o botão foi pressionado (com debounce)
        numero = (numero + 1) % 10; // Incrementa e mantém entre 0 e 9
    }
}

// Rotina de Interrupção para Botão B (Decrementa o número)
void irq_button_b(unsigned int gpio, uint32_t events) {
    if (debounce(gpio)) { // Verifica se o botão foi pressionado (com debounce)
        numero = (numero - 1 + 10) % 10; // Decrementa e mantém entre 0 e 9
    }
}

// Função principal
int main() {
    stdio_init_all(); // Inicializa a interface USB para depuração (opcional)

    // Configuração dos LEDs e botões
    setup_leds(); // Configura os LEDs (ex.: LED vermelho)
    setup_buttons(irq_button_a, irq_button_b); // Configura os botões com suas interrupções

    // Configuração da matriz de LEDs WS2812
    ws2812_init(pio0, 0, 0, LED_MATRIX); // Inicializa o WS2812 com o pino definido em config.h

    while (true) {
        // Pisca o LED vermelho (5 vezes por segundo)
        for (int i = 0; i < 5; i++) {
            gpio_put(LED_RED, 1); // Liga o LED vermelho
            sleep_ms(100);        // Mantém ligado por 100 ms
            gpio_put(LED_RED, 0); // Desliga o LED vermelho
            sleep_ms(100);        // Mantém desligado por 100 ms
        }

        // Atualiza a matriz de LEDs com o número atual
        ws2812_display_number(numero);
    }

    return 0;
}