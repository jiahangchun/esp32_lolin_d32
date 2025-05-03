#include "BLU.h"
BLU blu;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  //开启蓝牙模块
  blu.initBlu();
}

void loop() {
  // 简单示例：每隔5秒 触发蓝牙loop逻辑
  static unsigned long lastMillis = 0;
  if (millis() - lastMillis > 5000) {
    lastMillis = millis();
    blu.loopBlu();
  }
}
