#include <SoftwareSerial.h>

#define BT_RX 11
#define BT_TX 10

#define PWM_WIDTH 500
#define PORATE 115200


SoftwareSerial btSerial(BT_RX, BT_TX); // Bluetoothとやりとりするためのシリアル設定

void setup()
{
  // Mac側のシリアルポートの初期化
  Serial.begin(PORATE);
  // Bluetooth側のシリアルポートの初期化
  btSerial.begin(PORATE);
}


void loop()
{
  char c;
  if (Serial.available()){
    c = Serial.read();
    if (c == 'd') {
     sendKey((byte)0x2A);
    }
    else if (c == 's') {
      btSerial.print("arigatou");
    }
    else {
      btSerial.print(c);
    }
   delay(10);
  }
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


