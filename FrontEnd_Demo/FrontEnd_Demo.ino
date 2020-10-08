#include "Button.h"
#include <U8g2lib.h>
#include <TaskScheduler.h>
#include <WiFiNINA.h>
#include "pins.h"
#include <string.h>

#define WIFISSID "123456"   //Enter your WiFi SSID here
#define PASSWORD "123456" //Enter your WiFi Password here

WiFiClient wifi;

Button btn_up(BTN_UP);
Button btn_down(BTN_DOWN);
Button btn_sel(BTN_SEL);
Button btn_mode(BTN_MEN);
Button btn_flush(BTN_FLUSH);
Button btn_rear(BTN_REAR);



U8G2_ST7565_NHD_C12864_F_4W_HW_SPI u8g2(U8G2_R2, LCD_CS, LCD_DC, LCD_RESET);


void pollMenuEvent();


Task pollMenuEventTask(100, TASK_FOREVER, &pollMenuEvent);



Scheduler runner;

bool ShowButtonUp = false;
bool ShowButtonDown = false;
bool ShowButtonSelect = false;
bool ShowButtonMode = false;
bool ShowButtonFlush = false;
bool ShowButtonRear = false;



void pollMenuEvent()
{
  btn_up.read();
  btn_down.read();
  btn_sel.read();
  btn_mode.read();
  btn_flush.read();
  btn_rear.read();


    if (WiFi.status() != WL_CONNECTED)
  {
    //do nothing
    //Serial.println("no wifi");
  }
  else
  {
    u8g2.setFont(u8g2_font_open_iconic_www_1x_t);
    u8g2.drawGlyph(115, 10, 81);
    u8g2.sendBuffer();
    //Serial.println("wifi connected");
  }

}


void setup() {
  
  Serial.begin(115200);
  pinMode(FLUSH_LED, OUTPUT);
  pinMode(BTN_REAR, INPUT_PULLUP);
  pinMode(BUZZER, OUTPUT);
  analogWrite(LCD_LED, 255);
  digitalWrite(FLUSH_LED, HIGH);


  WiFi.disconnect();
  delay(500);

  int wifi_retries_count = 0;

  while (WiFi.status() != WL_CONNECTED && wifi_retries_count < 5)
  {
    wifi_retries_count++;
    WiFi.begin(WIFISSID, PASSWORD);
    Serial.print(".");
    delay(500);
    Serial.println(WiFi.status());
  }

  
  u8g2.begin();

  btn_up.begin();
  btn_down.begin();
  btn_sel.begin();
  btn_mode.begin();
  btn_flush.begin();
  btn_rear.begin();

  runner.init();

  runner.addTask(pollMenuEventTask);


  pollMenuEventTask.enable();

  defaultFrame();


}

void loop() {
  
  runner.execute();

  if (btn_up.isPressed())
    {
      tone(BUZZER, 1000);
      up_frame();              
    }

    else if (btn_down.isPressed())
    {
      tone(BUZZER, 1000);
      down_frame();            
    }

    else if (btn_sel.isPressed())
    {
      tone(BUZZER, 1000);
      select_frame();
    }
    else if (btn_mode.isPressed())
    {
      tone(BUZZER, 1000);
      mode_frame();      
    }
    else if (btn_rear.isPressed())
    {
      tone(BUZZER, 1000);
      rear_frame();      
    }
    else if (btn_flush.isPressed())
    {
      tone(BUZZER, 1000);
      flush_frame();     
    }
    else
    {
      noTone(BUZZER);     
    }    
}

void defaultFrame()
{
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_9x15B_mf);
  u8g2.drawStr(25, 10, "Test");
  u8g2.setFont(u8g2_font_6x12_tr);
  u8g2.drawStr(15, 32, "Press Buttons");
  u8g2.setCursor(90, 32);
  u8g2.sendBuffer();
  
  
}

void up_frame()
{
  u8g2.clearBuffer();

  u8g2.setFont(u8g2_font_6x12_tr);
  u8g2.drawStr(5, 32, "Up Button Pressed");
  u8g2.setCursor(90, 32);
  u8g2.sendBuffer();
  tone(BUZZER, 1000);
}

void down_frame()
{
  u8g2.clearBuffer();

  u8g2.setFont(u8g2_font_6x12_tr);
  u8g2.drawStr(10, 32, "Down Button Pressed");
  u8g2.setCursor(90, 32);
  u8g2.sendBuffer();
  tone(BUZZER, 1000);
}

void select_frame()
{
  u8g2.clearBuffer();

  u8g2.setFont(u8g2_font_6x12_tr);
  u8g2.drawStr(5, 32, "Right Button Pressed");
  u8g2.setCursor(90, 32);
  u8g2.sendBuffer();
  tone(BUZZER, 1000);
}

void mode_frame()
{
  u8g2.clearBuffer();

  u8g2.setFont(u8g2_font_6x12_tr);
  u8g2.drawStr(5, 32, "Left Button Pressed");
  u8g2.setCursor(90, 32);
  u8g2.sendBuffer();
  tone(BUZZER, 1000);
}


void flush_frame()
{
  u8g2.clearBuffer();

  u8g2.setFont(u8g2_font_6x12_tr);
  u8g2.drawStr(5, 32, "Flush Button Pressed");
  u8g2.setCursor(90, 32);
  u8g2.sendBuffer();
  tone(BUZZER, 1000);
}

void rear_frame()
{
  u8g2.clearBuffer();

  u8g2.setFont(u8g2_font_6x12_tr);
  u8g2.drawStr(5, 32, "Rear Button Pressed");
  u8g2.setCursor(90, 32);
  u8g2.sendBuffer();
  tone(BUZZER, 1000);
}
