// analog read
int thumbPin = 4;

int thumb = 0;
int num = 12;
int pre_num = 0;
int flag = 0;

void setup() {
  Serial.begin(115200);
  pinMode(thumbPin, OUTPUT);
}

void loop() {
  delay(100);
  type_key();
}

void type_key() {
  thumb = analogRead(thumbPin);
   
    // 指のどの関節にいるか検知
    if (thumb > 4000) {
      // 接触なし
      num = 12;
    }
    else if (thumb > 3700) {
      // あ
      num = 0;
    }
    else if (thumb > 3400) {
      // か
      num = 1;
    }
    else if (thumb > 3200) {
      // さ
      num = 2;
    }
    else if (thumb > 3000) {
      // た
      num = 3;
    }
    else if (thumb > 2900) {
      // な
      num = 4;
    }
    else if (thumb >2700) {
      // は
      num = 5;
    }
    else if (thumb > 2500) {
      // ま
      num = 6;
    }
    else if (thumb > 2200) {
      // や
      num = 7;
    }
    else if (thumb > 1800) {
      // ら
      num = 8;
    }
    else if (thumb > 1200) {
      // Space
      num = 9;
    }
    else if (thumb > 500) {
    // わ
    num = 10;
    }
    else {
      // Enter
      num = 11;
   }
   if (pre_num != num) {
    Serial.println(num);
    pre_num = num;
   }
}
