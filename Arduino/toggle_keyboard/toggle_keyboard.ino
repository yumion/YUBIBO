// analog read
int thumbPin = 4;
// touch sensor
int upPin = T4; // 13pin
int downPin = T6; // 14pin
int finger2Pin = T3; // 15pin

int thumb = 0;
int finger2 = 0;
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

  // どの指か検知
  if ((finger2 < 25  && finger2 > 5)|| flag_finger == 2) {
//    Serial.println("finger2");
    type_key();
    if (flag_finger != 0) {
      flag_finger = 0;
    }
    else {
      flag_finger = 2;
    }
  } else Serial.println("10");
}

void type_key() {

  thumb = analogRead(thumbPin);    
  // 上下
  up = touchRead(upPin);
  down = touchRead(downPin); 
  /*
  Serial.print("thumb: ");
  Serial.println(thumb);
  Serial.print("type: ");
  */
  // 指のどの関節にいるか検知
  if (thumb < 1900) {
    // い
    Serial.println("0");
  }
  else if (thumb < 2500) {
    // あ
    Serial.println("1");
  }
  else if (thumb < 3200) {
    // か
    Serial.println("2");
  }
  else if (thumb < 4000) {
    // さ
    Serial.println("3");
  }
   else {
    // せ
    Serial.println("4");
  }

}

