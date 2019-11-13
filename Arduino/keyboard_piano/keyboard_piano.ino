#include <SoftwareSerial.h>

#define BT_RX 7
#define BT_TX 8
SoftwareSerial btSerial(BT_RX, BT_TX); // Bluetoothとやりとりするためのシリアル設定

#define PWM_WIDTH 500
#define PORATE 115200
#define BUFSIZE 3

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


void setup() {
  // Mac側のシリアルポートの初期化
  Serial.begin(PORATE);
  // Bluetooth側のシリアルポートの初期化
  btSerial.begin(PORATE);
  Serial.println("start");
}


void loop() {
    /* Read */
    char keys[BUFSIZE+1];
    location = readLocation();  // デバイス用
//    if (location == 0) { getUserInput(keys, BUFSIZE); }
    if (location != 0) {Serial.print("location: "); Serial.println(location);}

    if (location == 1) {
      btSerial.print('z');
      Serial.print("\nSending ");
      Serial.println('z');
    }
    else if (location == 2) {
      btSerial.print('x');
      Serial.print("\nSending ");
      Serial.println('x');
    }
    else if (location == 3) {
      btSerial.print('c');
      Serial.print("\nSending ");
      Serial.println('c');
    }
    else if (location == 4) {
      btSerial.print('v');
      Serial.print("\nSending ");
      Serial.println('v');
    }
    else if (location == 5) {
      btSerial.print('b');
      Serial.print("\nSending ");
      Serial.println('b');
    }
    else if (location == 6) {
      btSerial.print('n');
      Serial.print("\nSending ");
      Serial.println('n');
    }
    else if (location == 7) {
      btSerial.print('m');
      Serial.print("\nSending ");
      Serial.println('m');
    }
    else if (location == 8) {
      btSerial.print('q');
      Serial.print("\nSending ");
      Serial.println('q');
    }
    else {
//      btSerial.print(keys);
      Serial.print("\nSending ");
      Serial.println(keys);
    }
    delay(200);
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


int divideRegion(int thumb) {
  // 読み値から区分けする
  int num = 0;
  if (thumb > 1000)
  {
    // 濁点
    num = 21;
  }
  else if (thumb > 950)
  {
    // わ
    num = 10;
  }
  else if (thumb > 900)
  {
    // 記号
    num = 20;
  }
  else if (thumb > 720)
  {
    // は
    num = 7;
  }
  else if (thumb > 690)
  {
    // や
    num = 8;
  }
  else if (thumb > 600)
  {
    // ら
    num = 9;
  }
  else if (thumb > 560)
  {
    // た
    num = 4;
  }
  else if (thumb > 551)
  {
    // な
    num = 5;
  }
  else if (thumb > 520)
  {
    // は
    num = 6;
  }
  else if (thumb > 481)
  {
    // あ
    num = 1;
  }
    else if (thumb > 472)
  {
    // か
    num = 2;
  }
    else if (thumb > 460)
  {
    // さ
    num = 3;
  }
    else if (thumb > 449)
  {
    // Enter
    num = 24;
  }
    else if (thumb > 440)
  {
    // Backspace
    num = 23;
  }
    else if (thumb > 400)
  {
    // Space
    num = 22;
  }
  else
  {
    // 接触なし
    num = 0;
  }
  return num;
}


void sendKeyModifier(byte key, byte modifier){
  sendKeyCode(key, modifier);
  delay(100);
  sendKeyCode((byte)0x00, (byte)0x00);
}

void sendKey(byte key){
  sendKeyModifier(key, (byte)0x00);
}

void sendKeyCode(byte key, byte modifier){
    btSerial.write(0xFD);
    btSerial.write(0x09);
    btSerial.write(0x01);
    btSerial.write(modifier);
    btSerial.write((byte)0x00);
    btSerial.write(key);
    btSerial.write((byte)0x00);
    btSerial.write((byte)0x00);
    btSerial.write((byte)0x00);
    btSerial.write((byte)0x00);
    btSerial.write((byte)0x00);
}

void backspaceKey() {
  sendKey((byte)0x2A);
}

void enterKey() {
  sendKey((byte)0x28);
}

void spaceKey() {
  sendKey((byte)0x2C);
}

void shiftKey() {
  sendKey((byte)0xE1);
}

void deleteKey() {
  sendKey((byte)0x4C);
}

