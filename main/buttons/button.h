#ifndef BUTTON_WOLL
#define BUTTON_WOLL

typedef enum {
    GPIO_MODE_IN,
    GPIO_MODE_OUT,
  } gpioMode_t;
  
  typedef struct buttonHandle_t buttonHandle_t;
  typedef void (*buttonPressedCallback_t)(buttonHandle_t* handle);
  
  typedef struct buttonHandle_t{
    uint32_t pin;
    gpio_mode_t mode;
    bool pullUp;
    bool pullDown;
    bool irqEnabled;
    buttonPressedCallback_t callback;
  } buttonHandle_t;

  bool initButton(buttonHandle_t* p_handle);


#endif