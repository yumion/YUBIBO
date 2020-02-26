# YUBIBO
これは東京大学Spring Founder Program(SFP)で作製されたものです．

## コンペ参加履歴
- GUGEN2019エントリー
- ヒーローズリーグ2019・XUIリーグ XinSuzuki賞（個人賞）受賞

## 旧Yubiboの使用方法（ `finger_keyboard_arduino.py` ）
Python環境をインストールしたPCとUSBケーブルでYubiboを接続する必要があります．

### 環境（動作確認済み）
- Windows 10 / MacOS Mojave
- Python 3.6
    - numpy==1.14.2
    - pyautogui==0.9.38
- Arduino SDK 1.8.5

### 実行方法
1. PCとArduinoをUSBで接続する．
2. Arduino SDKを起動(ただし，シリアルモニタは開かない)．Arduinoのポート番号を記録しておく．
3. ターミナル(コマンドプロンプト等Pythonが実行できる端末)を起動し ```finger_keyboard_arduino.py``` を実行する．optionでportを指定．
```
$ python finger_keyboard_arduino.py --port COM4
```
4. ターミナル上に ```start``` と表示されたら起動成功．
5. 任意のテキストエディタを起動しデバイスを使用してください．

### 終了方法
1. ターミナルに戻り `ctrl+C` でプログラムを終了する．
2. Arduino SDKを終了し，PCからArduinoを外す．


## 新YUBIBOの使用方法（`Arduino/pythonConvert/pythonConvert.ino`）
新YUBIBOではBLuetoothを用いた無線化を行い，python環境も不要になりました．
1. 使用するデバイスのBluetoothをオンにする．
2. YUBIBO#とペアリングする．(#には数字が入ります）
3. 任意のテキストエディタでデバイスを使用してください．

iPhone SEで動作を確認しました．

## キーボード入力方法
<!--
<img width="319" alt="yubibo" src="https://user-images.githubusercontent.com/38414956/57672240-3e87e500-7652-11e9-86b9-0eb394ba1795.png">
-->
![スクリーンショット 2020-02-26 17 31 28](https://user-images.githubusercontent.com/38414956/75326380-d7c07900-58bd-11ea-9052-d441e209e2bc.png)


一昔前のガラケーと同じキーボードです（トグルキーボードと言います）．

親指で4指の各関節をタッチしてキー入力をします．

例えば，あ行の節を1回タッチすると `あ` ，2回タッチすると `い` ，6回タッチすると `あ` に戻ってきます．

`りんご` と打ちたい場合，ら行の節を2回，わ行の節を3回，か行の節を5回，濁点の節を1回タッチします．


## キーボードのソフトウェア調整方法
`yubibo#.h` を編集します（#には数字が入ります）．

```
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
...
```
となっているif文の条件式の数値（`thumb > ここ`）を適切な閾値に変更します．

`thumb` はArduinoで読んだ電圧で，3.3Vを1023，0Vを0と変換した値です．

各ボタンの電圧をArduino IDEのシリアルモニタで確認し，隣のボタンと電圧が被らないように閾値を定めます．
