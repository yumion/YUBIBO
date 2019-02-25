// analog read
int thumbPin = 4;
int touchPin = T4; // 13pin

int thumb = 0;

void setup() {
  Serial.begin(115200);
  pinMode(thumbPin, OUTPUT);
}

void loop() {
  delay(500);
}
void type_key() {
  thumb = analogRead(thumbPin);

  Serial.print("thumb: ");
  Serial.println(thumb);
  Serial.print("type: ");

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
