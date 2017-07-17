#include "lcd12864.hpp"

#define CS0 gpio_set_level(cs, 0)
#define CS1 gpio_set_level(cs, 1)
#define SID0 gpio_set_level(sid, 0)
#define SID1 gpio_set_level(sid, 1)
#define SCLK0 gpio_set_level(sclk, 0)
#define SCLK1 gpio_set_level(sclk, 1)
#define RST0 gpio_set_level(rst, 0)
#define RST1 gpio_set_level(rst, 1)
#define CH0 gpio_set_level(ch, 0)
#define CH1 gpio_set_level(ch, 1)

void delay(int t) {
    ets_delay_us(t * 100);
}

LCD12864::LCD12864(gpio_num_t cs, gpio_num_t sid, gpio_num_t sclk, gpio_num_t rst, gpio_num_t ch) {
    this -> cs = cs;
    this -> sid = sid;
    this -> sclk = sclk;
    this -> rst = rst;
    this -> ch = ch;
    gpio_set_pull_mode(cs, GPIO_PULLUP_ONLY);
    gpio_set_pull_mode(sid, GPIO_PULLUP_ONLY);
    gpio_set_pull_mode(sclk, GPIO_PULLUP_ONLY);
    gpio_set_pull_mode(rst, GPIO_PULLUP_ONLY);
    gpio_set_pull_mode(ch, GPIO_PULLUP_ONLY);
    gpio_set_direction(cs, GPIO_MODE_OUTPUT);
    gpio_set_direction(sid, GPIO_MODE_OUTPUT);
    gpio_set_direction(sclk, GPIO_MODE_OUTPUT);
    gpio_set_direction(rst, GPIO_MODE_OUTPUT);
    gpio_set_direction(ch, GPIO_MODE_OUTPUT);
}

void LCD12864::init() {
    CH0;
    delay(1);
    RST0;
    delay(100);
    RST1;
    delay(20000);
    write_com(0x30);
    delay(50);
    write_com(0x0c);
    delay(50);
    delay(10);
}

void LCD12864::sendbyte(uint8_t zdata) {
    for(int i=0; i<8; i++) {
        if((zdata << i) & 0x80) {
            SID1;
        } else {
            SID0;
        }
        SCLK0;
        SCLK1;
    }
}

void LCD12864::write_com(uint8_t cmdcode) {
    CS1;
    sendbyte(0xf8);
    sendbyte(cmdcode & 0xf0);
    sendbyte((cmdcode << 4) & 0xf0);
    delay(2);
}

void LCD12864::write_data(uint8_t dispdata) {
    CS1;
    sendbyte(0xfa);
    sendbyte(dispdata & 0xf0);
    sendbyte((dispdata << 4) & 0xf0);
    delay(2);
}

void LCD12864::putstr(const char *str) {
    uint8_t *s = (uint8_t*)str;
    while(*s > 0) {
        write_data(*s);
        s++;
        delay(50);
    }
}

void LCD12864::clear() {
    write_com(0x01);
    delay(50);
}

void LCD12864::setpos(int y, int x) {
    switch(y) {
        case 0:
            write_com(0x80 + x);
            return;
        case 1:
            write_com(0x90 + x);
            return;
        case 2:
            write_com(0x88 + x);
            return;
        case 3:
            write_com(0x98 + x);
            return;
    }
}
