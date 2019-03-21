int thumbPin = 2;   // analogPin
int pre_num = 0;    // 1つ前のキーを覚えておく（グローバル変数）

void setup()
{
  Serial.begin(9600);
  pinMode(thumbPin, OUTPUT);
}

void loop()
{
  int region = 15;
  region = read_key(); // 親指の位置
  type_key(region);
  delay(100);
}

int read_key()
// どの位置を触れたか検出
{
  int thumb, region;
  thumb = analogRead(thumbPin);
//  Serial.println(thumb);
  region = convert_to_region(thumb); // 0-1023を離散値へ変換
  return region;
}

void type_key(int num)
// pythonへキーを送信
{
  if (pre_num != num) // 同じキーが押されなかったら
  {
    Serial.println(num); // pythonへ送信
    pre_num = num;       // 1つ前の入力を記憶
  }
}

int convert_to_region(int thumb)
{
  int num = 0;
  // 指のどの関節にいるか検知
  if (thumb > 500)
  {
    // 接触なし
    num = 15;
  }
  else if (thumb > 460)
  {
    // Space
    num = 12;
  }
  else if (thumb > 440)
  {
    // Delete
    num = 13;
  }
  else if (thumb > 420)
  {
    // Enter
    num = 14;
  }
  else if (thumb > 390)
  {
    // あ
    num = 0;
  }
  else if (thumb > 370)
  {
    // か
    num = 1;
  }
  else if (thumb > 340)
  {
    // さ
    num = 2;
  }
  else if (thumb > 320)
  {
    // た
    num = 3;
  }
  else if (thumb > 290)
  {
    // な
    num = 4;
  }
  else if (thumb > 260)
  {
    // は
    num = 5;
  }
  else if (thumb > 220)
  {
    // ま
    num = 6;
  }
  else if (thumb > 180)
  {
    // や
    num = 7;
  }
  else if (thumb > 140)
  {
    // ら
    num = 8;
  }
  else if (thumb > 80)
  {
    // 濁点、半濁点、小文字
    num = 9;
  }
  else if (thumb > 40)
  {
    // わ
    num = 10;
  }
  else
  {
    // Enter
    num = 11;
  }
  return num;
}

