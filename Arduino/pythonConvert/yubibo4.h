/* 左手用 */
int divideRegion(int thumb) {
  // 読み値から区分けする
  int num = 0;
  if (thumb > 1000)
  {
    // 濁点
    num = 21;
  }
  else if (thumb > 935)
  {
    // わ
    num = 10;
  }
  else if (thumb > 900)
  {
    // 記号
    num = 20;
  }
  else if (thumb > 740)
  {
    // は
    num = 7;
  }
  else if (thumb > 710)
  {
    // や
    num = 8;
  }
  else if (thumb > 650)
  {
    // ら
    num = 9;
  }
  else if (thumb > 600)
  {
    // た
    num = 4;
  }
  else if (thumb > 575)
  {
    // な
    num = 5;
  }
  else if (thumb > 520)
  {
    // は
    num = 6;
  }
  else if (thumb > 470)
  {
    // あ
    num = 1;
  }
    else if (thumb > 450)
  {
    // か
    num = 2;
  }
    else if (thumb > 420)
  {
    // さ
    num = 3;
  }
    else if (thumb > 410)
  {
    // Enter
    num = 24;
  }
    else if (thumb > 399)
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
