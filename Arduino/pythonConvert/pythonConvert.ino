#include <SoftwareSerial.h>

#define BT_RX 6
#define BT_TX 5
SoftwareSerial btSerial(BT_RX, BT_TX); // Bluetoothとやりとりするためのシリアル設定

#define PWM_WIDTH 500
#define PORATE 115200

#define THUMBPIN 3   // analogPin(親指read用)


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
int op_count = 0; //濁点,半濁点,小文字カウント


void setup() {
  // Mac側のシリアルポートの初期化
  Serial.begin(PORATE);
  // Bluetooth側のシリアルポートの初期化
  btSerial.begin(PORATE);
  Serial.println("start");
}

void loop() {
    /* Read */
    location = serialMonitorTest();  // シリアルモニタ用
//    location = readLocation();  // デバイス用
    if (location != 0) {Serial.print("location: "); Serial.println(location);}
    count = count % 5;

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
        btSerial.print(output_words);
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
        btSerial.print(output_words);
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
        btSerial.print(output_words);
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
        btSerial.print(output_words);
        count += 1;
        if (count == 3) {
            count = 0;
        }
    }
    /* 濁点,半濁音,小文字 */
    else if (location == 21) {
        /* 濁音(か行/さ行/た行/は行) */
        if (op_count == 0 && (pre_location == 2 || pre_location == 3 || pre_location == 4 || pre_location == 6) ) {
            backspaceKey();
            output_words[0] = voiced_consonant_words[pre_location - 2];
            output_words[1] = vowel_words[count - 1];  // か->がでcount+1される
            if (pre_location == 6 || (pre_location == 4 && count == 3)) {
              // は行/つ
                op_count += 1;
            }
        }
        /* 半濁音(ぱ行) */
        else if (op_count == 1 && pre_location == 6) {
            backspaceKey();
            output_words[0] = 'p';
            output_words[1] = vowel_words[count - 1];
            op_count = 0;
        }
        /* 小文字(あ行/や行/っ) */
        else if ( pre_location == 1 || pre_location == 8 || (pre_location == 4 && count == 3) ) {
            backspaceKey();
            output_words[0] = 'x';
            output_words[1] = vowel_words[count - 1];
            op_count = 0;
        }
        btSerial.print(output_words);
    }
    /*  */
    else if (location == 20) {
        if (pre_location != location) {
            count = 0;
            pre_location = location;
        } else {
            backspaceKey();
        }
        output_words[0] = token_words[count];
        output_words[1] = '\0';
        btSerial.print(output_words);
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

void deleteKey() {
  sendKey((byte)0x4C);
}

int readLocation() {
  // どの位置を触れたか検出
  int thumb, location;
  thumb = analogRead(THUMBPIN);
//  Serial.print("vol: ");
//  Serial.println(thumb);
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
  else
  {
    // 
    num = 0;
  }
  return num;
}

float serialMonitorTest() {
  /* シリアルモニタから数値を打ち込む */
  float num = 0;
  if (Serial.available() > 0) {
    delay(20);
    int data_size = Serial.available();
    int buf[data_size];
//    Serial.print("data size: "); Serial.println(data_size);
    for (int i = 0 ; i < data_size ; i++)
    {
      buf[i] = Serial.read() - 0x30;
//      Serial.print(buf[i]);
    }
    for (int i = 0; i < data_size; i++) {
      num += buf[data_size - 1 - i] * pow(10, i);
    }
  } else {
    num = 0;
  }
  return num;
}

