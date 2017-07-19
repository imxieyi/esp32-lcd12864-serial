#pragma once

#include "driver/gpio.h"
#include "rom/ets_sys.h"

// pin layout http://www.waveshare.net/shop/LCD12864-ST-price.htm
class LCD12864 {
private:
    gpio_num_t cs, sid, sclk, rst, ch;
    bool simple_mode;
public:
    LCD12864(gpio_num_t sid, gpio_num_t sclk, gpio_num_t rst);
    LCD12864(gpio_num_t cs, gpio_num_t sid, gpio_num_t sclk, gpio_num_t rst, gpio_num_t ch);
    void init();
    void sendbyte(uint8_t zdata);
    void write_com(uint8_t cmdcode);
    void write_data(uint8_t dispdata);
    void putstr(const char *str);
    void clear();
    void setpos(int y, int x);
};
