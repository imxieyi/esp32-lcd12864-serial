# ESP32 LCD12864 中文字符液晶屏驱动
工作在串行模式，需要占用5个GPIO，具体可参考[http://www.waveshare.net/shop/LCD12864-ST-price.htm](http://www.waveshare.net/shop/LCD12864-ST-price.htm)。

如果需要显示中文，请将文件编码转换成GB2312，直接调用putstr即可。
