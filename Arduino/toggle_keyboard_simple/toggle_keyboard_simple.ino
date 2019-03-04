int thumbPin = 4;   // analogPin
int split_num = 12; // 分割数
int pre_num = 0;    // 1つ前のキーを覚えておく（グローバル変数）

void setup()
{
  Serial.begin(115200);
  pinMode(thumbPin, OUTPUT);
}

void loop()
{
  int thumb = 0; // 親指の読み値
  read_key(thumb);
  type_key(thumb);
}

int read_key()
// どの位置を触れたか検出
{
  int count[split_num] = {};
  // 10点サンプリング
  for (int i = 0; i < 10; i++)
  {
    thumb = analogRead(thumbPin);
    region = map(thumb, 0, 4095, 0, split_num); // 0-4095をsplit_num個の離散値へ変換
    count[region] += 1;
    delay(10)
  }
  return argmax(count, split_num);
}

void type_key(int num)
// pythonへキーを送信
{
  if (pre_num != num) // 同じキーが押されなかったら
  {
    Serial.println(num); // pythonへ送信
    pre_num = num;       // 1つ前の入力を記憶
    // Serial.println(num);
  }
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