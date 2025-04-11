#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "led_strip.h"
#include "sdkconfig.h"
#include "rand/rand.h"
#include "buttons/button.h"

static const char *TAG = "example";

#define LED_GPIO CONFIG_BLINK_GPIO

static uint8_t s_led_state = 0;

static led_strip_handle_t led_strip;

int matrix [6][25] = {    
    {
        0,0,0,0,0,
        1,0,0,1,0,
        1,1,1,1,1,
        1,0,0,0,0,
        0,0,0,0,0, 
    },   
    {
        1,0,0,1,0,
        1,0,0,0,1,
        1,1,0,0,1,
        1,0,1,0,1,
        1,0,0,1,0
    },      
    {
        0,0,0,0,0,
        1,0,0,0,1,
        1,0,1,0,1,
        1,0,1,0,1,
        0,1,0,1,0
    },  
    {
        0,1,0,0,0,
        0,1,1,0,0,
        0,1,0,1,0,
        1,1,1,1,1,
        0,1,0,0,0
    },  
    {
        1,0,1,1,1,
        1,0,1,0,1,
        1,0,1,0,1,
        1,0,1,0,1,
        0,1,0,0,1
    }, 
    {
        0,1,1,1,0,
        1,0,1,0,1,
        1,0,1,0,1,
        1,0,1,0,1,
        0,1,0,0,0
    },
};

static void writeLed(void){
    led_strip_clear(led_strip);
    int zahl = 5;
    for(int i = 0; i < 25; i++){
        led_strip_set_pixel(led_strip, i, matrix[zahl][i] * 10, matrix[zahl][i] * 10, matrix[zahl][i] * 10);
    }

    led_strip_refresh(led_strip);
}

static void rauschen(void){
    for(int i = 0; i < 20; i++){
        led_strip_clear(led_strip);

        led_strip_set_pixel(led_strip, nextRand() % 25, 10, 10, 10);
        led_strip_set_pixel(led_strip, nextRand() % 25, 10, 10, 10);
        led_strip_set_pixel(led_strip, nextRand() % 25, 10, 10, 10);
        led_strip_set_pixel(led_strip, nextRand() % 25, 10, 10, 10);
        led_strip_set_pixel(led_strip, nextRand() % 25, 10, 10, 10);

        led_strip_refresh(led_strip);

        vTaskDelay(50 / portTICK_PERIOD_MS);
    }
    led_strip_clear(led_strip);
    led_strip_refresh(led_strip);
}

static void randomDice(bool cheat){
    rauschen();
    led_strip_clear(led_strip);

    uint8_t rand = nextRand() % 6;
    if(cheat){
        rand = 5;
    }
    for(int i = 0; i < 25; i++){
        led_strip_set_pixel(led_strip, i, matrix[rand][i] * 10, matrix[rand][i] * 10, matrix[rand][i] * 10);
    }

    led_strip_refresh(led_strip);
    
}

static void configure_led(void){
    ESP_LOGI(TAG, "Example configured to blink addressable LED!");
    led_strip_config_t strip_config = {
        .strip_gpio_num = LED_GPIO,
        .max_leds = 25,
    };
    led_strip_rmt_config_t rmt_config = {
        .resolution_hz = 10 * 1000 * 1000,
        .flags.with_dma = false,
    };
    ESP_ERROR_CHECK(led_strip_new_rmt_device(&strip_config, &rmt_config, &led_strip));

    led_strip_clear(led_strip);
    led_strip_refresh(led_strip);
}


void app_main(void){
    switchOnRtc20MClk();
    configure_led();
    randButtonInit();
    cheatButtonInit();

    while (1) {
        if(randButtonPressed()){
            randomDice(false);
        }

        if(cheatButtonPressed()){
            randomDice(true);
        }

        //writeLed();
        vTaskDelay(1 / portTICK_PERIOD_MS);

    }
}
