#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "sdkconfig.h"
#include "rand/rand.h"
#include "buttons/button.h"
#include "dice/dice.h"

static const char *TAG = "example";

static void randomDice(bool cheat){
    uint8_t rand = nextRand() % 6;
    if(cheat){
        rand = 5;
    }
    displayMatrix(rand);
}

volatile bool randButtonPressed = false;
static void irq_randButtonPressed(buttonHandle_t* handle){
    randButtonPressed = true;
}

volatile bool cheatButtonPressed = false;
static void irq_cheatButtonPressed(buttonHandle_t* handle){
    cheatButtonPressed = true;
}

void app_main(void){
    gpio_install_isr_service(0);
    switchOnRtc20MClk();
    configure_led();

    buttonHandle_t randButtonHandle = {
        .pin = 9,
        .mode = GPIO_MODE_IN,
        .pullUp = true,
        .pullDown = false,
        .irqEnabled = true,
        .callback = irq_randButtonPressed
    };
    initButton(&randButtonHandle);

    buttonHandle_t cheatButtonHandle = {
        .pin = 2,
        .mode = GPIO_MODE_IN,
        .pullUp = true,
        .pullDown = false,
        .irqEnabled = true,
        .callback = irq_cheatButtonPressed
    };
    initButton(&cheatButtonHandle);

    while(1){
        if(randButtonPressed){
            randButtonPressed = false;
            randomDice(false);
        }

        if(cheatButtonPressed){
            cheatButtonPressed = false;
            randomDice(true);
        }
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}
