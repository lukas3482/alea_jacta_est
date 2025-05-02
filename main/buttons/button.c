#include "driver/gpio.h"
#include "button.h"

#define RAND_BUTTON_GPIO 9
#define CHEAT_BUTTON_GPIO 2


void buttonIsrHandler(void* handler){
  buttonHandle_t* buttonHandle = (buttonHandle_t*)handler;
  if (buttonHandle->callback) {
    buttonHandle->callback(buttonHandle);
  }
}

bool initButton(buttonHandle_t* p_handle){
  gpio_config_t io_conf = {
    .pin_bit_mask = ((1ULL << p_handle->pin)),
    .mode = GPIO_MODE_INPUT,
    .pull_up_en = GPIO_PULLUP_ENABLE,
    .pull_down_en = GPIO_PULLDOWN_DISABLE,
    .intr_type = GPIO_INTR_NEGEDGE
  };
  gpio_config(&io_conf);

  gpio_isr_handler_add(p_handle->pin, buttonIsrHandler, (void*)p_handle);
  return true;
}



/*
void randButtonInit() {
  gpio_config_t io_conf = {
    .pin_bit_mask = ((1ULL << RAND_BUTTON_GPIO)|(1ULL << CHEAT_BUTTON_GPIO)),
    .mode = GPIO_MODE_INPUT,
    .pull_up_en = GPIO_PULLUP_ENABLE,
    .pull_down_en = GPIO_PULLDOWN_DISABLE,
    .intr_type = GPIO_INTR_DISABLE
  };
  gpio_config(&io_conf);
}

bool randButtonPressed() { 
    return gpio_get_level(RAND_BUTTON_GPIO) == 0; 
}

bool cheatButtonPressed() { 
    return gpio_get_level(CHEAT_BUTTON_GPIO) == 0;
}
    */