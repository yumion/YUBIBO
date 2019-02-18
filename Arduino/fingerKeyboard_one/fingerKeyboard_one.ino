// analog read
int thumbPin = 4;
// touch sensor
int upPin = T4; // 13pin
int downPin = T6; // 14pin
int finger2Pin = T3; // 15pin
int finger3Pin = T7; // 27pin
int finger4Pin = T8; // 12pin
int finger5Pin = T9; // 14pin

int thumb = 0;
int finger2 = 0;
int finger3 = 0;
int finger4 = 0;
int finger5 = 0;
int up = 0;
int down = 0;

int flag_finger = 0;

void setup() {
  Serial.begin(115200);
  pinMode(thumbPin, OUTPUT);
}
 
void loop() {
  delay(500);
  // 5本指
  finger2 = touchRead(finger2Pin);
  finger3 = touchRead(finger3Pin);
  finger4 = touchRead(finger4Pin);
  finger5 = touchRead(finger5Pin);

  // どの指か検知
  if ((finger2 < 25  && finger2 > 5)|| flag_finger == 2) {
    Serial.println("finger2");
    type_key();
    if (flag_finger != 0) {
      flag_finger = 0;
    }
    else {
      flag_finger = 2;
    }
  } else if ((finger3 < 25 && finger3 > 5) || flag_finger == 3){
    Serial.println("finger3");
    type_key();
    if (flag_finger != 0) {
      flag_finger = 0;
    }
    else {
      flag_finger = 3;
    }
  } else if ((finger4 < 25 && finger4 > 5) || flag_finger == 4){
    Serial.println("finger4");
    type_key();
    if (flag_finger != 0) {
      flag_finger = 0;
    }
    else {
      flag_finger = 4;
    }
  } else if ((finger5 < 25 && finger5 > 5) || flag_finger == 5){
    Serial.println("finger5");
    type_key();
    if (flag_finger != 0) {
      flag_finger = 0;
    }
    else {
      flag_finger = 5;
    }
  } else Serial.println("7");
}

void type_key() {

  thumb = analogRead(thumbPin);
      // 上下
  up = touchRead(upPin);
  down = touchRead(downPin); 
/*
  Serial.print("thumb: ");
  Serial.println(thumb);
  Serial.print("up: ");
  Serial.println(up);
  Serial.print("down: ");
  Serial.println(down);
  Serial.print("type: ");
*/
  // 上or下にフリックを検知
  if (up < 25 && up > 5) {
    // う
    Serial.println("0");
  }
  else if (down < 25 && down > 5) {
    // お
    Serial.println("1");
  }

  // 指のどの関節にいるか検知
  else if (thumb < 500) {
    // い
    Serial.println("2");
  }
  else if (thumb < 1500) {
    // あ
    Serial.println("3");
  }
  else if (thumb < 2500) {
    // か
    Serial.println("4");
  }
  else if (thumb < 4000) {
    // さ
    Serial.println("5");
  }
   else {
    // せ
    Serial.println("6");
  }

}

