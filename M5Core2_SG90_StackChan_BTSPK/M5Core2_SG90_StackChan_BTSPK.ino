#include <Arduino.h>

#if defined(ARDUINO_M5STACK_Core2)
  #include <M5Core2.h>
  #define SERVO_PIN_X 13
  #define SERVO_PIN_Y 14
#elif defined( ARDUINO_M5STACK_FIRE )
  #include <M5Stack.h>
  #define SERVO_PIN_X 21
  #define SERVO_PIN_Y 22
#elif defined( ARDUINO_M5Stack_Core_ESP32 )
  #include <M5Stack.h>
  #define SERVO_PIN_X 21
  #define SERVO_PIN_Y 22
#endif

#include <Avatar.h> // https://github.com/meganetaaan/m5stack-avatar
#include <ServoEasing.hpp> // https://github.com/ArminJo/ServoEasing       
#include "AtaruFace.h"
#include "RamFace.h"
#include "BluetoothA2DPSink.h"

BluetoothA2DPSink a2dp_sink;

using namespace m5avatar;
Avatar avatar;
Face* faces[3];
ColorPalette* cps[3];

#define START_DEGREE_VALUE_X 90
#define START_DEGREE_VALUE_Y 90

ServoEasing servo_x;
ServoEasing servo_y;

extern int16_t audio_level;
void behavior(void *args)
{
  float gazeX, gazeY;
  DriveContext *ctx = (DriveContext *)args;
  Avatar *avatar = ctx->getAvatar();
   for (;;)
  {
    int level = audio_level;
    level = abs(level);
    if(level > 3500)
    {
      level = 3500;
    }
    float open = (float)level/3500.0;
    avatar->setMouthOpenRatio(open);
    avatar->getGaze(&gazeY, &gazeX);
    servo_x.setEaseTo(START_DEGREE_VALUE_X + (int)(20.0 * gazeX));
    if(gazeY < 0) {
      int tmp = (int)(20.0 * gazeY + open * 15.0);
      if(tmp > 20) tmp = 20;
      servo_y.setEaseTo(START_DEGREE_VALUE_Y + tmp);
    } else {
      servo_y.setEaseTo(START_DEGREE_VALUE_Y + (int)(10.0 * gazeY) - open * 15.0);
    }
    synchronizeAllServosStartAndWaitForAllServosToStop();
  
    delay(33);
//    delay(50);
  }
}

void setup() {

#if defined(ARDUINO_M5STACK_Core2)
  M5.begin(true, true, true, false, kMBusModeOutput);
  M5.Axp.SetSpkEnable(true);
#elif defined( ARDUINO_M5STACK_FIRE ) || defined( ARDUINO_M5Stack_Core_ESP32 )
  M5.begin(true, true, true, false); // Grove.Aを使う場合は第四引数(I2C)はfalse
#endif
  if (servo_x.attach(SERVO_PIN_X, START_DEGREE_VALUE_X, DEFAULT_MICROSECONDS_FOR_0_DEGREE, DEFAULT_MICROSECONDS_FOR_180_DEGREE)) {
    Serial.print("Error attaching servo x");
  }
  if (servo_y.attach(SERVO_PIN_Y, START_DEGREE_VALUE_Y, DEFAULT_MICROSECONDS_FOR_0_DEGREE, DEFAULT_MICROSECONDS_FOR_180_DEGREE)) {
    Serial.print("Error attaching servo y");
  }
  servo_x.setEasingType(EASE_QUADRATIC_IN_OUT);
  servo_y.setEasingType(EASE_QUADRATIC_IN_OUT);
  setSpeedForAllServos(60);

  M5.Lcd.setBrightness(30);
  M5.Lcd.clear();
  M5.Lcd.setTextSize(2);
  delay(1000);

#if defined(ARDUINO_M5STACK_Core2)
  i2s_pin_config_t tx_pin_config;
  tx_pin_config.bck_io_num    = 12;
  tx_pin_config.ws_io_num     = 0;
  tx_pin_config.data_out_num  = 2;
  tx_pin_config.data_in_num   = I2S_PIN_NO_CHANGE;
  a2dp_sink.set_pin_config(tx_pin_config);
  a2dp_sink.start("Avatar");  
#elif defined( ARDUINO_M5STACK_FIRE ) || defined( ARDUINO_M5Stack_Core_ESP32 )
  static const i2s_config_t i2s_config = {
      .mode = (i2s_mode_t) (I2S_MODE_MASTER | I2S_MODE_TX | I2S_MODE_DAC_BUILT_IN),
      .sample_rate = 44100, // corrected by info from bluetooth
      .bits_per_sample = (i2s_bits_per_sample_t) 16, /* the DAC module will only take the 8bits from MSB */
      .channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT,
      .communication_format = I2S_COMM_FORMAT_I2S_MSB,
      .intr_alloc_flags = 0, // default interrupt priority
      .dma_buf_count = 8,
      .dma_buf_len = 64,
      .use_apll = false
  };
  a2dp_sink.set_i2s_config(i2s_config);  
  a2dp_sink.start("Avatar");  
#endif

  faces[0] = new AtaruFace();
  faces[1] = new RamFace();
  faces[2] = avatar.getFace();
  cps[0] = new ColorPalette();
  cps[1] = new ColorPalette();
  cps[2] = new ColorPalette();
  cps[0]->set(COLOR_PRIMARY, TFT_BLACK);
  cps[0]->set(COLOR_BACKGROUND, TFT_WHITE);
  cps[0]->set(COLOR_SECONDARY, TFT_WHITE);
  cps[1]->set(COLOR_PRIMARY, TFT_BLACK);
  cps[1]->set(COLOR_BACKGROUND, TFT_WHITE);
  cps[1]->set(COLOR_SECONDARY, TFT_WHITE);

  avatar.init();
  avatar.setFace(faces[0]);
  avatar.setColorPalette(*cps[0]);
  avatar.addTask(behavior, "behavior");
}

void loop() {
  M5.update(); 
  if (M5.BtnA.wasPressed())
  {
    avatar.setFace(faces[0]);
    avatar.setColorPalette(*cps[0]);
  }
  if (M5.BtnB.wasPressed())
  {
    avatar.setFace(faces[1]);
    avatar.setColorPalette(*cps[1]);
  }
  if (M5.BtnC.wasPressed())
  {
    avatar.setFace(faces[2]);
    avatar.setColorPalette(*cps[2]);
  }
}
