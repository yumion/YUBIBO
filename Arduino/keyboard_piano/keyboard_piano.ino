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


int location = 0;
int pre_location = 0;
int count = 0; 


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
//    if (location != 0) {Serial.print("location: "); Serial.println(location);}

    if (location == 2) {
      btSerial.print('z');
      Serial.print("Sending ");
      Serial.println("ド");
      Serial.print("\n");
    }
    else if (location == 1) {
      btSerial.print('x');
      Serial.print("Sending ");
      Serial.println("レ");
      Serial.print("\n");
    }
    else if (location == 4) {
      btSerial.print('c');
      Serial.print("Sending ");
      Serial.println("ミ");
      Serial.print("\n");
    }
    else if (location == 3) {
      btSerial.print('v');
      Serial.print("Sending ");
      Serial.println("ファ");
      Serial.print("\n");
    }
    else if (location == 6) {
      btSerial.print('b');
      Serial.print("Sending ");
      Serial.println("ソ");
      Serial.print("\n");
    }
    else if (location == 5) {
      btSerial.print('n');
      Serial.print("Sending ");
      Serial.println("ラ");
      Serial.print("\n");
    }
    else if (location == 8) {
      btSerial.print('m');
      Serial.print("Sending ");
      Serial.println("シ");
      Serial.print("\n");
    }
    else if (location == 7) {
      btSerial.print('q');
      Serial.print("Sending ");
      Serial.println("ド↑");
      Serial.print("\n");
    }
//    else if (location == 9) {
//      btSerial.print('w');
//      Serial.print("Sending ");
//      Serial.println('w');
//      Serial.print("\n");
//    }
//    else {
////      btSerial.print(keys);
//      Serial.print("\nSending ");
//      Serial.println(keys);
//    }
    delay(250);
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
  if (thumb > 950)
  {
    // 
    num = 8;
  }
  else if (thumb > 850)
  {
    // 
    num = 7;
  }
  else if (thumb > 734)
  {
    // 
    num = 6;
  }
  else if (thumb > 675)
  {
    // 
    num = 5;
  }
  else if (thumb > 580)
  {
    // 
    num = 4;
  }
  else if (thumb > 510)
  {
    // 
    num = 3;
  }
  else if (thumb > 450)
  {
    // 
    num = 2;
  }
  else if (thumb > 300)
  {
    // 
    num = 1;
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

