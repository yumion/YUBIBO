int divideRegion(int thumb) {
  // 読み値から区分けする
  int num = 0;
  if (thumb > 1000)
  {
    // 濁点
    num = 21;
  }
  else if (thumb > 950)
  {
    // わ
    num = 10;
  }
  else if (thumb > 900)
  {
    // 記号
    num = 20;
  }
  else if (thumb > 720)
  {
    // は
    num = 7;
  }
  else if (thumb > 690)
  {
    // や
    num = 8;
  }
  else if (thumb > 600)
  {
    // ら
    num = 9;
  }
  else if (thumb > 560)
  {
    // た
    num = 4;
  }
  else if (thumb > 551)
  {
    // な
    num = 5;
  }
  else if (thumb > 520)
  {
    // は
    num = 6;
  }
  else if (thumb > 481)
  {
    // あ
    num = 1;
  }
    else if (thumb > 472)
  {
    // か
    num = 2;
  }
    else if (thumb > 460)
  {
    // さ
    num = 3;
  }
    else if (thumb > 449)
  {
    // Enter
    num = 24;
  }
    else if (thumb > 440)
  {
    // Backspace
    num = 23;
  }
    else if (thumb > 400)
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