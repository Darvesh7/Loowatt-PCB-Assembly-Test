#include <U8g2lib.h>
#include <TaskScheduler.h>
#include "pins.h"
#include <string.h>

U8G2_SSD1306_128X64_NONAME_F_4W_HW_SPI oled(U8G2_R0, OLED_CS, OLED_DC, OLED_RESET);

void setup() {
  
  Serial.begin(9600);
  pinMode(STATUS_LED, OUTPUT);
  pinMode(MOTOR_INA, OUTPUT);
  pinMode(MOTOR_INB, OUTPUT);
  pinMode(MOTOR_PWM, OUTPUT);

  delay(1000);
  
  // Startup oled
  oled.begin();
  oled.clearBuffer();
  oled.setFont(u8g2_font_9x18B_mr);      // choose a suitable font
  oled.drawStr(10, 24, "HELLO WORLD!");         // write something to the internal memory // ends at 30
  oled.sendBuffer();

}

void loop() {

  digitalWrite(STATUS_LED, HIGH);
  D1_led();
  delay(1000);
  D2_led();
  delay(1000);
  digitalWrite(STATUS_LED,LOW);
  delay(1000);

}


void D1_led()
{
  digitalWrite(MOTOR_INA, HIGH);
  digitalWrite(MOTOR_INB, LOW);
  digitalWrite(MOTOR_PWM, HIGH);
}

void D2_led()
{
  digitalWrite(MOTOR_INA, LOW);
  digitalWrite(MOTOR_INB, HIGH);
  digitalWrite(MOTOR_PWM, HIGH);
}
