/* 左手用 */
int divideRegion(int thumb) {
  // 読み値から区分けする
  int num = 0;
  if (thumb > 1000)
  {
    // 濁点
    num = 21;
  }
  else if (thumb > 930)
  {
    // わ
    num = 10;
  }
  else if (thumb > 850)
  {
    // 記号
    num = 20;
  }
  else if (thumb > 740)
  {
    // は
    num = 7;
  }
  else if (thumb > 700)
  {
    // や
    num = 8;
  }
  else if (thumb > 650)
  {
    // ら
    num = 9;
  }
  else if (thumb > 550)
  {
    // た
    num = 4;
  }
  else if (thumb > 540)
  {
    // な
    num = 5;
  }
  else if (thumb > 500)
  {
    // は
    num = 6;
  }
  else if (thumb > 465)
  {
    // あ
    num = 1;
  }
    else if (thumb > 430)
  {
    // か
    num = 2;
  }
    else if (thumb > 410)
  {
    // さ
    num = 3;
  }
    else if (thumb > 400)
  {
    // Enter
    num = 24;
  }
    else if (thumb > 400)
  {
    // Backspace
    num = 23;
  }
    else if (thumb > 370)
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
