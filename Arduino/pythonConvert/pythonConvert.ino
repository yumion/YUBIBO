#include <SoftwareSerial.h>

#define BT_RX 11
#define BT_TX 10
SoftwareSerial btSerial(BT_RX, BT_TX); // Bluetoothとやりとりするためのシリアル設定

#define PWM_WIDTH 500
#define PORATE 115200

#define THUMBPIN 3   // analogPin(親指read用)

/* --- 入力 --- */
// 0:あ 1:か 2:さ
// 3:た 4:な 5:は
// 6:ま 7:や 8:ら
// 11:濁点/半濁点/小文字 10:わ 9:何もなし
// 12:Space 13:Backspace 14:Enter
// 15:接触なし

char consonant_words[13] = {'\0', 'k', 's', 't', 'n', 'h', 'm', 'y', 'r', '\0', 'w', '\0', '\0'};  // 子音
char voiced_consonant_words[7] = {'\0', 'g', 'z', 'd', '\0', 'b', '\0'};  // 濁点
char vowel_words[6] = {'a', 'i', 'u', 'e', 'o', '\0'};  // 母音
char yayuyo_words[7] = "yayuyo";  // や行
char wawonn_words[7] = "wawonn";  // わ行
char output_words[3] = {};  // 文字結合して出力する用

int location = 15;
int pre_num = 0;    // 1つ前のキーを覚えておく（グローバル変数）
int pre_location = 15;
int count = 0;
int op_count = 0;


void setup() {
  // Mac側のシリアルポートの初期化
  Serial.begin(PORATE);
  // Bluetooth側のシリアルポートの初期化
  btSerial.begin(PORATE);
  Serial.println("start");
}

void loop() {
//    if (Serial.available()) { byte c = Serial.read(); location = c - 0x30; }
    location = readLocation();
    Serial.print("num: "); Serial.println(location);
    count = count % 5;
    
    /* 入力なし/や行/わ行/濁点/入力なし(9)以外入力された場合 */
    if (location != 15 && location < 9 && location != 7) {
        if (pre_location != location) {
            count = 0;
            output_words[0] = consonant_words[location];
            output_words[1] = vowel_words[count];
            btSerial.print(output_words);
            pre_location = location;
        }
        else {
            backspaceKey();
            output_words[0] = consonant_words[location];
            output_words[1] = vowel_words[count];
            btSerial.print(output_words);
        count += 1;
        }
    }
    /* や行 */
    else if (location == 7) {
        if (pre_location != location) {
            count = 0;
            output_words[0] = consonant_words[location];
            output_words[1] = vowel_words[count];
            btSerial.print(output_words);
            pre_location = location;
        }
        else {
            backspaceKey();
            output_words[0] = yayuyo_words[count];
            output_words[1] = yayuyo_words[count + 1];
            btSerial.print(output_words);
        }
        count += 2;
        if (count >= 5) {
            count = 0;
        }
    }
    /* わ行 */
    else if (location == 10) {
        if (pre_location != location) {
            count = 0;
            output_words[0] = consonant_words[location];
            output_words[1] = vowel_words[count];
            btSerial.print(output_words);
            pre_location = location;
        }
        else {
            backspaceKey();
            output_words[0] = wawonn_words[count];
            output_words[1] = wawonn_words[count + 1];
            btSerial.print(output_words);
        }
        count += 2;
        if (count >= 5) {
            count = 0;
        }
    }
    /* 濁点 */
    else if (location == 11) {
        if (op_count == 0 && (pre_location == 1 || pre_location == 2 || pre_location == 3 || pre_location == 5) ) {
            backspaceKey();
            output_words[0] = voiced_consonant_words[pre_location];
            output_words[1] = vowel_words[count - 1];
            btSerial.print(output_words);
            if (pre_location == 5 || (pre_location == 3 && count == 3)) {
                op_count += 1;
            }
        }
        /* 半濁音(ぱ行) */
        else if (op_count == 1 && pre_location == 5) {
            backspaceKey();
            output_words[0] = 'p';
            output_words[1] = vowel_words[count - 1];
            btSerial.print(output_words);
            op_count = 0;
        }
        /* 小文字 */
        else if ( (pre_location == 0 || pre_location == 7) || (pre_location == 3 && count == 3) ) {
            backspaceKey();
            output_words[0] = 'x';
            output_words[1] = vowel_words[count - 1];
            btSerial.print(output_words);
            op_count = 0;
        }
    }
    /* 変換(Space) */
    else if (location == 12) {
        spaceKey();
    }
    /* Backspace */
    else if (location == 13) {
        backspaceKey();
    }
    /* Enter */
    else if (location == 14) {
        enterKey();
        count = 0;  // Enterすると文字確定するのでリセット  
    }
    
    delay(200);
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

int readLocation() {
  // どの位置を触れたか検出
  int thumb, location;
  thumb = analogRead(THUMBPIN);
//  Serial.print("vol: ");
//  Serial.println(thumb);
  location = divideRegion(thumb); // 0-1023を離散値へ変換
  return location;
}

int divideRegion(int thumb)
{
  int num = 15;
  // 指のどの関節にいるか検知
  if (thumb > 450)
  {
    // あ
    num = 0;
  }
  else if (thumb > 390)
  {
    // か
    num = 1;
  }
  else if (thumb > 350)
  {
    // さ
    num = 2;
  }
  else if (thumb > 310)
  {
    // た
    num = 3;
  }
  else if (thumb > 285)
  {
    // な
    num = 4;
  }
  else if (thumb > 250)
  {
    // は
    num = 5;
  }
  else if (thumb > 218)
  {
    // ま
    num = 6;
  }
  else if (thumb > 212)
  {
    // や
    num = 7;
  }
  else if (thumb > 210)
  {
    // ら
    num = 8;
  }
  else if (thumb > 5)
  {
    // わ
    num = 9;
  }
  else
  {
    // 
    num = 15;
  }
  return num;
}

