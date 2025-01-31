cmake_minimum_required(VERSION 3.13)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Configuração do SDK do Raspberry Pi Pico
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.1.0)
set(toolchainVersion 13_3_Rel1)
set(picotoolVersion 2.1.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if(EXISTS ${picoVscode})
    include(${picoVscode})
endif()

# Inicialização do SDK
set(PICO_BOARD pico_w CACHE STRING "Board type")
include(pico_sdk_import.cmake)
project(embarcatech_interrupcoes C CXX ASM)
pico_sdk_init()

# Adição de executável
add_executable(embarcatech_interrupcoes
    ${CMAKE_CURRENT_LIST_DIR}/main.c
    ${CMAKE_CURRENT_LIST_DIR}/libs/ws2812.c
    ${CMAKE_CURRENT_LIST_DIR}/libs/debounce.c
    ${CMAKE_CURRENT_LIST_DIR}/libs/gpio_config.c
)

# Configuração de nome e versão
pico_set_program_name(embarcatech_interrupcoes "embarcatech_interrupcoes")
pico_set_program_version(embarcatech_interrupcoes "0.1")

# Habilitação de saída serial
pico_enable_stdio_uart(embarcatech_interrupcoes 0)
pico_enable_stdio_usb(embarcatech_interrupcoes 1)

# Vinculação de bibliotecas
target_link_libraries(embarcatech_interrupcoes
    pico_stdlib
    hardware_pio
    hardware_timer
    hardware_clocks
    hardware_gpio
    hardware_irq
    pico_sync
)

# Inclusão de diretórios
target_include_directories(embarcatech_interrupcoes PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
    ${CMAKE_CURRENT_LIST_DIR}/libs
)

# Geração de saídas adicionais
pico_add_extra_outputs(embarcatech_interrupcoes)