#include <cstring>
#include <cstdlib>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_system.h"
#include "esp_log.h"

#include "lcd12864.hpp"


// 
static void lcd_task(void *pvParameters) {
    LCD12864 lcd(GPIO_NUM_17, GPIO_NUM_18, GPIO_NUM_19);

    lcd.init();
    lcd.clear();
    lcd.setpos(0, 0);
    lcd.putstr("1.First item");
    lcd.setpos(1, 0);
    lcd.putstr("2.Second item");
    lcd.setpos(2, 0);
    lcd.putstr("3.Thrid item");
    lcd.setpos(3, 0);
    lcd.putstr("4.Fourth item");
    vTaskDelay(100);
    lcd.clear();
    lcd.setpos(0, 0);
    lcd.putstr("1.First item");
    vTaskDelete(0);
}

extern "C" void app_main() {
    xTaskCreatePinnedToCore(&lcd_task,"lcd_task",2048,NULL,5,NULL,0);
}