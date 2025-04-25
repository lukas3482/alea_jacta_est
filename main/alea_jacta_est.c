#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "sdkconfig.h"
#include "rand/rand.h"
#include "buttons/button.h"
#include "matrix/matrix.h"

static const char *TAG = "example";

static void randomDice(bool cheat){
    uint8_t rand = nextRand() % 6;
    if(cheat){
        rand = 5;
    }
    displayMatrix(rand);
}

void app_main(void){
    switchOnRtc20MClk();
    configure_led();
    randButtonInit();

    while (1) {
        if(randButtonPressed()){
            randomDice(false);
        }

        if(cheatButtonPressed()){
            randomDice(true);
        }

        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}
