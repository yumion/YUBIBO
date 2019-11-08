int thumbPin = 3;   // analogPin
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
  delay(500);
}

int read_key()
// どの位置を触れたか検出
{
  int thumb, region;
  thumb = analogRead(thumbPin);
  Serial.print("read: ");
  Serial.println(thumb);
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
  int num = 15;
  // 指のどの関節にいるか検知
  if (thumb > 650)
  {
    // 接触なし
    num = 15;
  }
  else if (thumb > 394)
  {
    // Space
    num = 12;
  }
  else if (thumb > 380)
  {
    // Delete
    num = 13;
  }
  else if (thumb > 360)
  {
    // Enter
    num = 14;
  }
  else if (thumb > 340)
  {
    // あ
    num = 0;
  }
  else if (thumb > 318)
  {
    // か
    num = 1;
  }
  else if (thumb > 300)
  {
    // さ
    num = 2;
  }
  else if (thumb > 270)
  {
    // た
    num = 3;
  }
  else if (thumb > 245)
  {
    // な
    num = 4;
  }
  else if (thumb > 225)
  {
    // は
    num = 5;
  }
  else if (thumb > 200)
  {
    // ま
    num = 6;
  }
  else if (thumb > 160)
  {
    // や
    num = 7;
  }
  else if (thumb > 120)
  {
    // ら
    num = 8;
  }
  else if (thumb > 70)
  {
    // 濁点、半濁点、小文字
    num = 9;
  }
  else if (thumb > 10)
  {
    // わ
    num = 10;
  }
  else
  {
    // 
    num = 11;
  }
  return num;
}
