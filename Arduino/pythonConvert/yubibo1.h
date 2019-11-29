/* 左手用 */
int divideRegion(int thumb) {
  // 読み値から区分けする
  int num = 0;
  if (thumb > 965)
  {
    // 濁点
    num = 21;
  }
  else if (thumb > 925)
  {
    // わ
    num = 10;
  }
  else if (thumb > 840)
  {
    // 記号
    num = 20;
  }
  else if (thumb > 770)
  {
    // ま
    num = 7;
  }
  else if (thumb > 724)
  {
    // や
    num = 8;
  }
  else if (thumb > 670)
  {
    // ら
    num = 9;
  }
  else if (thumb > 612)
  {
    // た
    num = 4;
  }
  else if (thumb > 589)
  {
    // な
    num = 5;
  }
  else if (thumb > 570)
  {
    // は
    num = 6;
  }
  else if (thumb > 495)
  {
    // あ
    num = 1;
  }
    else if (thumb > 486)
  {
    // か
    num = 2;
  }
    else if (thumb > 472)
  {
    // さ
    num = 3;
  }
    else if (thumb > 465)
  {
    // Enter
    num = 24;
  }
    else if (thumb > 447)
  {
    // Backspace
    num = 23;
  }
    else if (thumb > 300)
  {
    // Space
    num = 22;
  }
  else
  {
    // 接触なし
    num = 0;
  }
  return num;
}
