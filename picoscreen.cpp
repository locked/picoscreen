#include <stdio.h>
#include "pico/stdlib.h"

const uint pin_anode1 = 7;
const uint pin_anode2 = 8;

const uint pin_b = 1;
const uint pin_bl = 2;
const uint pin_br = 3;
const uint pin_tr = 4;
const uint pin_tl = 5;
const uint pin_t = 6;
const uint pin_m = 7;

const uint pin_relay1 = 28;

int nums[10][8] = {
  {pin_b, pin_bl, pin_br, pin_tr, pin_tl, pin_t},		// 0
  {pin_br, pin_tr},
  {pin_t, pin_tr, pin_m, pin_bl, pin_b},
  {pin_t, pin_tr, pin_m, pin_br, pin_b},
  {pin_tl, pin_tr, pin_m, pin_br},
  {pin_t, pin_tl, pin_m, pin_br, pin_b},
  {pin_t, pin_tl, pin_m, pin_bl, pin_br, pin_b},
  {pin_t, pin_tr, pin_br},
  {pin_b, pin_bl, pin_br, pin_tr, pin_tl, pin_t, pin_m},	// 8
  {pin_t, pin_tr, pin_tl, pin_m, pin_br, pin_b},
};

void led_num(int num) {
    printf("NUMBER:[%d]\n", num);
    for (uint pin=0; pin<7; pin++) {
        gpio_put(pin, 1);
    }
    for (uint pin=0; pin<7; pin++) {
        //printf("PIN:[%d]\n", nums[num][pin]);
        if (nums[num][pin] > 0) {
            gpio_put(nums[num][pin] - 1, 0);
        }
    }
}

int main() {
    // setup_default_uart();

    stdio_init_all();
    printf("Hello, world!\n");

    const uint LED_PIN = PICO_DEFAULT_LED_PIN;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    for (uint pin=0; pin<9; pin++) {
        gpio_init(pin);
        gpio_set_dir(pin, GPIO_OUT);
    }

    gpio_init(pin_relay1);
    gpio_set_dir(pin_relay1, GPIO_OUT);

    while (true) {
        gpio_put(pin_relay1, 1);

        gpio_put(LED_PIN, 1);
        sleep_ms(200);
        gpio_put(LED_PIN, 0);
        printf(".");

        gpio_put(pin_anode1, 1);
        for (uint n=0; n<10; n++) {
            led_num(n);
            sleep_ms(500);
        }
        gpio_put(pin_anode1, 0);

        gpio_put(pin_relay1, 0);

        gpio_put(pin_anode2, 1);
        for (uint n=0; n<10; n++) {
            led_num(n);
            sleep_ms(1000);
        }
        gpio_put(pin_anode2, 0);

        gpio_put(pin_anode1, 1);
        for (uint pin=0; pin<7; pin++) {
            gpio_put(pin, 1);
            sleep_ms(1500);
            gpio_put(pin, 0);
            sleep_ms(1500);
        }
        gpio_put(pin_anode1, 0);

        /*gpio_put(pin_anode2, 1);
        for (uint pin=0; pin<7; pin++) {
            gpio_put(pin, 1);
            sleep_ms(300);
            gpio_put(pin, 0);
            sleep_ms(300);
        }
        gpio_put(pin_anode2, 0);*/
    }

    return 0;
}
