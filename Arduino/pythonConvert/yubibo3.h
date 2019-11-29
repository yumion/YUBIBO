/* 右手用 */
int divideRegion(int thumb) {
  // 読み値から区分けする
  int num = 0;
  if (thumb > 1000)
  {
    // 記号
    num = 20;
  }
  else if (thumb > 970)
  {
    // わ
    num = 10;
  }
  else if (thumb > 900)
  {
    // 濁点
    num = 21;
  }
  else if (thumb > 770)
  {
    // ら
    num = 9;
  }
  else if (thumb > 740)
  {
    // や
    num = 8;
  }
  else if (thumb > 700)
  {    
    // は
    num = 7;
  }
  else if (thumb > 620)
  {
    // は
    num = 6;
  }
  else if (thumb > 600)
  {
    // な
    num = 5;
  }
  else if (thumb > 580)
  {    
    // た
    num = 4;
  }
  else if (thumb > 535)
  {
    // さ
    num = 3;
  }
    else if (thumb > 520)
  {
    // か
    num = 2;
  }
    else if (thumb > 500)
  {    
    // あ
    num = 1;
  }
    else if (thumb > 480)
  {
    // Space
    num = 22;
  }
    else if (thumb > 470)
  {
    // Backspace
    num = 23;
  }
    else if (thumb > 400)
  {    
    // Enter
    num = 24;
  }
  else
  {
    // 接触なし
    num = 0;
  }
  return num;
}
