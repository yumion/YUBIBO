#include <Arduino.h>
#include <SPI.h>
#include "Adafruit_BLE.h"
#include "Adafruit_BluefruitLE_SPI.h"
#include "Adafruit_BluefruitLE_UART.h"

#include "BluefruitConfig.h"

#if SOFTWARE_SERIAL_AVAILABLE
  #include <SoftwareSerial.h>
#endif

#define FACTORYRESET_ENABLE         0
#define MINIMUM_FIRMWARE_VERSION    "0.6.6"
/* ...hardware SPI, using SCK/MOSI/MISO hardware SPI pins and then user selected CS/IRQ/RST */
Adafruit_BluefruitLE_SPI ble(BLUEFRUIT_SPI_CS, BLUEFRUIT_SPI_IRQ, BLUEFRUIT_SPI_RST);

// A small helper
void error(const __FlashStringHelper*err) {
  Serial.println(err);
  while (1);
}


#define THUMBPIN 2   // analogPin(親指read用)

 /* --- 入力 --- 
 *  22:Space 23:Backspace 24:Enter
 *  1:あ 2:か 3:さ
 *  4:た 5:な 6:は
 *  7:ま 8:や 9:ら
 *  21:濁点/半濁点/小文字 10:わ 20:記号
 *  0:接触なし
 */

char consonant_words[9] = {'k', 's', 't', 'n', 'h', 'm', 'y', 'r', '\0'};  // 子音
char voiced_consonant_words[6] = {'g', 'z', 'd', '\0', 'b', '\0'};  // 濁点
char vowel_words[6] = "aiueo";  // 母音
char yayuyo_words[7] = "yayuyo";  // や行
char wawonn_words[7] = "wawonn";  // わ行
char token_words[6] = {'-', ',', '.', '!', '?', '\0'};  // 記号
char output_words[3] = {};  // 文字結合して出力する用

int location = 0;
int pre_location = 0;
int count = 0; 
int p_flag = 0; // ぱ行撥音フラグ


void setup(void)
{
  while (!Serial);  // required for Flora & Micro
  delay(500);

  Serial.begin(115200);
  Serial.println(F("Adafruit Bluefruit HID Keyboard Example"));
  Serial.println(F("---------------------------------------"));

  /* Initialise the module */
  Serial.print(F("Initialising the Bluefruit LE module: "));

  if ( !ble.begin(VERBOSE_MODE) )
  {
    error(F("Couldn't find Bluefruit, make sure it's in CoMmanD mode & check wiring?"));
  }
  Serial.println( F("OK!") );

  if ( FACTORYRESET_ENABLE )
  {
    /* Perform a factory reset to make sure everything is in a known state */
    Serial.println(F("Performing a factory reset: "));
    if ( ! ble.factoryReset() ){
      error(F("Couldn't factory reset"));
    }
  }

  /* Disable command echo from Bluefruit */
  ble.echo(false);

  Serial.println("Requesting Bluefruit info:");
  /* Print Bluefruit information */
  ble.info();

  /* Change the device name to make it easier to find */
  Serial.println(F("Setting device name to 'Bluefruit Keyboard': "));
  if (! ble.sendCommandCheckOK(F( "AT+GAPDEVNAME=Bluefruit Keyboard" )) ) {
    error(F("Could not set device name?"));
  }

  /* Enable HID Service */
  Serial.println(F("Enable HID Service (including Keyboard): "));
  if ( ble.isVersionAtLeast(MINIMUM_FIRMWARE_VERSION) )
  {
    if ( !ble.sendCommandCheckOK(F( "AT+BleHIDEn=On" ))) {
      error(F("Could not enable Keyboard"));
    }
  }else
  {
    if (! ble.sendCommandCheckOK(F( "AT+BleKeyboardEn=On"  ))) {
      error(F("Could not enable Keyboard"));
    }
  }

  /* Add or remove service requires a reset */
  Serial.println(F("Performing a SW reset (service changes require a reset): "));
  if (! ble.reset() ) {
    error(F("Couldn't reset??"));
  }

  Serial.println();
  Serial.println(F("Go to your phone's Bluetooth settings to pair your device"));
  Serial.println(F("then open an application that accepts keyboard input"));

  Serial.println();
  Serial.println(F("Enter the character(s) to send:"));
  Serial.println(F("- \\r for Enter"));
  Serial.println(F("- \\n for newline"));
  Serial.println(F("- \\t for tab"));
  Serial.println(F("- \\b for backspace"));

  Serial.println();
}

/**************************************************************************/
/*!
    @brief  Constantly poll for new command or response data
*/
/**************************************************************************/
void loop(void)
{
  // Display prompt
  Serial.print(F("keyboard > "));

  // Check for user input and echo it back if anything was found
//  char keys[BUFSIZE+1];
//  getUserInput(keys, BUFSIZE);
  location = readLocation();

    /* 接触なし/あ行/や行/わ行/濁点/未割り当て(20) 以外 */
    if (location > 1 && location < 10 && location != 8) {
        if (pre_location != location) {
            count = 0;
            pre_location = location;
        } else {
            backspaceKey(); 
        }
        output_words[0] = consonant_words[location - 2];
        output_words[1] = vowel_words[count];
        ble.print("AT+BleKeyboard=");
        ble.println(output_words);
        count += 1;
    }
    /* あ行 */
    else if (location == 1) {
        if (pre_location != location) {
            count = 0;
            pre_location = location;
        } else {
            backspaceKey();
        }
        output_words[0] = vowel_words[count];
        output_words[1] = '\0';
        ble.print("AT+BleKeyboard=");
        ble.println(output_words);
        count += 1;
    }
    /* や行 */
    else if (location == 8) {
        if (pre_location != location) {
            count = 0;
            pre_location = location;
        } else {
            backspaceKey();
        }
        output_words[0] = yayuyo_words[2 * count];
        output_words[1] = yayuyo_words[2 * count + 1];
        ble.print("AT+BleKeyboard=");
        ble.println(output_words);
        count += 1;
        if (count == 3) {
            count = 0;
        }
    }
    /* わ行 */
    else if (location == 10) {
        if (pre_location != location) {
            count = 0;
            pre_location = location;
        } else {
            backspaceKey();
        }
        output_words[0] = wawonn_words[2 * count];
        output_words[1] = wawonn_words[2 * count + 1];
        ble.print("AT+BleKeyboard=");
        ble.println(output_words);
        count += 1;
        if (count == 3) {
            count = 0;
        }
    }
    /* 濁点/半濁音/小文字 */
    else if (location == 21) {
        /* 濁音(か行/さ行/た行/は行) */
        if (p_flag == 0 && (pre_location == 2 || pre_location == 3 || pre_location == 4 || pre_location == 6) ) {
            backspaceKey();
            output_words[0] = voiced_consonant_words[pre_location - 2];
            output_words[1] = vowel_words[count - 1];  // か->がでcount+1される
            if (pre_location == 6 || (pre_location == 4 && count == 3)) {
              // は行/つ
                p_flag = 1;
            }
        }
        /* 半濁音(ぱ行) */
        else if (p_flag == 1 && pre_location == 6) {
            backspaceKey();
            output_words[0] = 'p';
            output_words[1] = vowel_words[count - 1];
            p_flag = 0;
        }
        /* 撥音(っ) */
        else if (p_flag == 1 && (pre_location == 4 && count == 3)) {
            backspaceKey();
            ble.print("AT+BleKeyboard=");
            ble.println('x');
            output_words[0] = 't';
            output_words[1] = 'u';
            p_flag = 0;
        }
        /* 小文字(あ行) */
        else if (pre_location == 1) {
            backspaceKey();
            output_words[0] = 'x';
            output_words[1] = vowel_words[count - 1];
            p_flag = 0;
        }
        /* 小文字(や行) */
        else if (pre_location == 8) {
            backspaceKey();
            ble.print("AT+BleKeyboard=");
            ble.println('x');
            output_words[0] = yayuyo_words[2 * (count - 1)];
            output_words[1] = yayuyo_words[2 * (count - 1) + 1];
            p_flag = 0;
        }
        ble.print("AT+BleKeyboard=");
        ble.println(output_words);
    }
    /* 記号 */
    else if (location == 20) {
        if (pre_location != location) {
            count = 0;
            pre_location = location;
        } else {
            backspaceKey();
        }
        output_words[0] = token_words[count];
        output_words[1] = '\0';
        ble.print("AT+BleKeyboard=");
        ble.println(output_words);
        count += 1;
        if (count == strlen(token_words)) {
            count = 0;
        }
    }
    /* 変換(Space) */
    else if (location == 22) {
        spaceKey();
    }
    /* Backspace */
    else if (location == 23) {
        backspaceKey();
    }
    /* Enter */
    else if (location == 24) {
        enterKey();
        count = 0;  // Enterすると文字確定するのでリセット  
    }

  if( ble.waitForOK() )
  {
    Serial.println( F("OK!") );
  }else
  {
    Serial.println( F("FAILED!") );
  }
}


int readLocation() {
  // どの位置を触れたか検出
  int thumb, location;
  thumb = analogRead(THUMBPIN);
  Serial.print("vol: ");
  Serial.println(thumb);
  location = divideRegion(thumb);  // 0-1023を離散値へ変換
  return location;
}


int divideRegion(int thumb) {
  // 読み値から区分けする
  int num = 0;
  if (thumb > 450)
  {
    // あ
    num = 1;
  }
  else if (thumb > 390)
  {
    // か
    num = 2;
  }
  else if (thumb > 350)
  {
    // さ
    num = 3;
  }
  else if (thumb > 310)
  {
    // た
    num = 4;
  }
  else if (thumb > 285)
  {
    // な
    num = 5;
  }
  else if (thumb > 250)
  {
    // は
    num = 6;
  }
  else if (thumb > 218)
  {
    // ま
    num = 7;
  }
  else if (thumb > 212)
  {
    // や
    num = 8;
  }
  else if (thumb > 210)
  {
    // ら
    num = 9;
  }
  else if (thumb > 5)
  {
    // わ
    num = 10;
  }
    else if (thumb > 5)
  {
    // 記号
    num = 20;
  }
    else if (thumb > 5)
  {
    // 濁点
    num = 21;
  }
    else if (thumb > 5)
  {
    // space
    num = 22;
  }
    else if (thumb > 5)
  {
    // backspace
    num = 23;
  }
    else if (thumb > 5)
  {
    // enter
    num = 24;
  }
  else
  {
    // 
    num = 0;
  }
  return num;
}


void backspaceKey() {
  ble.print("AT+BleKeyboard=");
  ble.println("\b");
}

void enterKey() {
  ble.print("AT+BleKeyboard=");
  ble.println("\r");
}

void spaceKey() {
  ble.print("AT+BleKeyboard=");
  ble.println("\t");
}


void getUserInput(char buffer[], uint8_t maxSize)
{
  memset(buffer, 0, maxSize);
  while( Serial.available() == 0 ) {
    delay(1);
  }

  uint8_t count=0;

  do
  {
    count += Serial.readBytes(buffer+count, maxSize);
    delay(2);
  } while( (count < maxSize) && !(Serial.available() == 0) );
}
