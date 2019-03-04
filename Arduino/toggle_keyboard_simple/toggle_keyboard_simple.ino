int thumbPin = 4;   // analogPin
int split_num = 13; // 分割数
int pre_num = 0;    // 1つ前のキーを覚えておく（グローバル変数）

void setup()
{
  Serial.begin(115200);
  pinMode(thumbPin, OUTPUT);
}

void loop()
{
  int region = 0;
  region = read_key(); // 親指の位置
  type_key(region);
}

int read_key()
// どの位置を触れたか検出
{
  int thumb, region;
  int count[split_num] = {};
  // 10点サンプリング
  for (int i = 0; i < 10; i++)
  {
    thumb = analogRead(thumbPin);
    // Serial.println(thumb);
    region = convert_to_region(thumb); // 0-4095を離散値へ変換
    // Serial.println(region);
    count[region] += 1;
    delay(10);
  }
  return argmax(count, split_num);
//  return region;
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
  if (thumb > 4000)
  {
    // 接触なし
    num = 12;
  }
  else if (thumb > 3700)
  {
    // あ
    num = 0;
  }
  else if (thumb > 3400)
  {
    // か
    num = 1;
  }
  else if (thumb > 3200)
  {
    // さ
    num = 2;
  }
  else if (thumb > 3000)
  {
    // た
    num = 3;
  }
  else if (thumb > 2900)
  {
    // な
    num = 4;
  }
  else if (thumb > 2700)
  {
    // は
    num = 5;
  }
  else if (thumb > 2500)
  {
    // ま
    num = 6;
  }
  else if (thumb > 2200)
  {
    // や
    num = 7;
  }
  else if (thumb > 1800)
  {
    // ら
    num = 8;
  }
  else if (thumb > 1200)
  {
    // Space
    num = 9;
  }
  else if (thumb > 500)
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

int argmax(int array[], int n)
// 要素が最大となる引数を求める
{
  int i, max_idx;
  max_idx = 0;
  for (i = 1; i < n; i++)
  {
    if (array[max_idx] < array[i])
      max_idx = i;
  }
  return max_idx;
}
