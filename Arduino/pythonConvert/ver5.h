int divideRegion(int thumb) {
  // 読み値から区分けする
  int num = 0;
  if (thumb > 780)
  {
    // 濁点
    num = 21;
  }
  else if (thumb > 770)
  {
    // わ
    num = 10;
  }
  else if (thumb > 750)
  {
    // 記号
    num = 20;
  }
  else if (thumb > 700)
  {
    // は
    num = 7;
  }
  else if (thumb > 685)
  {
    // や
    num = 8;
  }
  else if (thumb > 655)
  {
    // ら
    num = 9;
  }
  else if (thumb > 627)
  {
    // た
    num = 4;
  }
  else if (thumb > 610)
  {
    // な
    num = 5;
  }
  else if (thumb > 580)
  {
    // は
    num = 6;
  }
  else if (thumb > 547)
  {
    // あ
    num = 1;
  }
    else if (thumb > 531)
  {
    // か
    num = 2;
  }
    else if (thumb > 515)
  {
    // さ
    num = 3;
  }
    else if (thumb > 501)
  {
    // Enter
    num = 24;
  }
    else if (thumb > 494)
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
