#include "dice.h"
#include "led_strip.h"
#include "esp_log.h"
#include "freertos/task.h"
#include "rand/rand.h"

#define LED_GPIO 8
static led_strip_handle_t led_strip;

static uint8_t matrix [6][25] = {    
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

static void rauschen(void){
    for(int i = 0; i < 20; i++){
        led_strip_clear(led_strip);

        led_strip_set_pixel(led_strip, nextRand() % 25, 10, 10, 10);
        led_strip_set_pixel(led_strip, nextRand() % 25, 10, 10, 10);
        led_strip_set_pixel(led_strip, nextRand() % 25, 10, 10, 10);
        led_strip_set_pixel(led_strip, nextRand() % 25, 10, 10, 10);
        led_strip_set_pixel(led_strip, nextRand() % 25, 10, 10, 10);

        led_strip_refresh(led_strip);

        vTaskDelay(50 / 10);
    }
    led_strip_clear(led_strip);
    led_strip_refresh(led_strip);
}

void displayMatrix(uint8_t rand){
    rauschen();
    led_strip_clear(led_strip);

    for(int i = 0; i < 25; i++){
        led_strip_set_pixel(led_strip, i, matrix[rand][i] * 10, matrix[rand][i] * 10, matrix[rand][i] * 10);
    }

    led_strip_refresh(led_strip);
    
}

void configure_led(void){
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


