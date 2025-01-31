#include "ws2812.pio.h" // Inclui o cabeçalho gerado pelo pioasm
#include "hardware/pio.h" // Para funções do PIO
#include "hardware/clocks.h" // Para clock_get_hz e clk_sys
#include <stdint.h> // Para uint32_t
#include "pico/stdlib.h"


// Função auxiliar para enviar dados para os LEDs WS2812
void ws2812_put_pixel(uint32_t pixel_grb) {
    pio_sm_put_blocking(pio0, 0, pixel_grb << 8u);
}

// Implementação da função ws2812_program_init
void ws2812_program_init(PIO pio, uint32_t sm, uint32_t offset, uint32_t pin, uint32_t freq, bool invert) {
    // Adiciona o programa PIO à memória do PIO
    pio_add_program(pio, &ws2812_program);

    // Configura o estado da máquina (SM)
    pio_sm_config c = ws2812_program_get_default_config(offset);

    // Define o pino de saída
    sm_config_set_out_pins(&c, pin, 1);

    // Define a frequência do clock
    sm_config_set_clkdiv(&c, (float)clock_get_hz(clk_sys) / freq);

    // Define o modo de inversão (se necessário)
    if (invert) {
        sm_config_set_out_shift(&c, true, true, 32);
    }

    // Inicializa o estado da máquina (SM)
    pio_sm_init(pio, sm, offset, &c);

    // Habilita o estado da máquina (SM)
    pio_sm_set_enabled(pio, sm, true);
}

// Função de inicialização do WS2812
void ws2812_init(PIO pio, uint32_t sm, uint32_t offset, uint32_t pin) {
    // Inicializa o programa PIO
    ws2812_program_init(pio, sm, offset, pin, 800000, false);
}

// Função para exibir um número nos LEDs WS2812
void ws2812_display_number(uint32_t number) {
    // Limpa todos os LEDs
    for (int i = 0; i < 10; i++) { // Assume 10 LEDs na matriz
        ws2812_put_pixel(0x000000); // Cor preta (desligado)
    }

    // Define as cores para cada número (0-9)
    uint32_t colors[10] = {
        0xFF0000, // 0: Vermelho
        0x00FF00, // 1: Verde
        0x0000FF, // 2: Azul
        0xFFFF00, // 3: Amarelo
        0xFF00FF, // 4: Magenta
        0x00FFFF, // 5: Ciano
        0xFFFFFF, // 6: Branco
        0x800000, // 7: Marrom
        0x008000, // 8: Verde escuro
        0x000080  // 9: Azul escuro
    };

    // Exibe o número correspondente
    if (number < 10) {
        ws2812_put_pixel(colors[number]); // Envia a cor correspondente ao número
    }
}