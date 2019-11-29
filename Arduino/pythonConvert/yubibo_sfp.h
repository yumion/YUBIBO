/* 右手用 */
int divideRegion(int thumb) {
  // 読み値から区分けする
  int num = 0;
  if (thumb > 1000)
  {
    // 記号
    num = 20;
  }
  else if (thumb > 324)
  {
    // わ
    num = 10;
  }
  else if (thumb > 191)
  {
    // 濁点
    num = 21;
  }
  else if (thumb > 133)
  {
    // ら
    num = 9;
  }
  else if (thumb > 93)
  {
    // や
    num = 8;
  }
  else if (thumb > 81)
  {    
    // は
    num = 7;
  }
  else if (thumb > 68)
  {
    // は
    num = 6;
  }
  else if (thumb > 59)
  {
    // な
    num = 5;
  }
  else if (thumb > 50)
  {    
    // た
    num = 4;
  }
  else if (thumb > 46)
  {
    // さ
    num = 3;
  }
    else if (thumb > 40)
  {
    // か
    num = 2;
  }
    else if (thumb > 36)
  {    
    // あ
    num = 1;
  }
    else if (thumb > 34)
  {
    // Space
    num = 22;
  }
    else if (thumb > 31)
  {
    // Backspace
    num = 23;
  }
    else if (thumb > 1)
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
