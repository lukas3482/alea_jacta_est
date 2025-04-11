#include "driver/gpio.h"

#define RAND_BUTTON_GPIO 9
#define CHEAT_BUTTON_GPIO 2

void randButtonInit() {
  gpio_config_t io_conf = {.pin_bit_mask = (1ULL << RAND_BUTTON_GPIO),
                           .mode = GPIO_MODE_INPUT,
                           .pull_up_en = GPIO_PULLUP_ENABLE,
                           .intr_type = GPIO_INTR_DISABLE};
  gpio_config(&io_conf);
}

void cheatButtonInit() {
    gpio_config_t io_conf = {.pin_bit_mask = (1ULL << CHEAT_BUTTON_GPIO),
                             .mode = GPIO_MODE_INPUT,
                             .pull_up_en = GPIO_PULLUP_ENABLE,
                             .intr_type = GPIO_INTR_DISABLE};
    gpio_config(&io_conf);
  }

bool randButtonPressed() { 
    return gpio_get_level(RAND_BUTTON_GPIO) == 0; 
}

bool cheatButtonPressed() { 
    return gpio_get_level(CHEAT_BUTTON_GPIO) == 1;
}