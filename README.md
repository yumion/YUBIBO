# Yubibo
これは東京大学Spring Founder Program(SFP)で作製されたものです．

## 環境（動作確認済み）
- Windows 10 / MacOS Mojave
- Python 3.6
    - numpy==1.14.2
    - pyautogui==0.9.38
- Arduino SDK 1.8.5

## 実行方法
1. PCとArduinoをUSBで接続する．
2. Arduino SDKを起動(ただし，シリアルモニタは開かない)．Arduinoのポート番号を記録しておく．
3. ターミナル(コマンドプロンプト等Pythonが実行できる端末)を起動し ```finger_keyboard_arduino.py``` を実行する．optionでportを指定．
```
$ python finger_keyboard_arduino.py --port COM4
```
4. ターミナル上に ```start``` と表示されたら起動成功．
5. 任意のテキストエディタを起動しデバイスを使用してください．

## 使用方法
<img width="319" alt="yubibo" src="https://user-images.githubusercontent.com/38414956/57672240-3e87e500-7652-11e9-86b9-0eb394ba1795.png">
一昔前のガラケーと同じキーボードです（トグルキーボードと言います）．

親指で4指の各関節をタッチしてキー入力をします．

例えば，あ行の節を1回タッチすると `あ` ，2回タッチすると `い` ，6回タッチすると `あ` に戻ってきます．

```りんご``` と打ちたい場合，ら行の節を2回，わ行の節を3回，か行の節を5回，濁点の節を1回タッチします．

## 終了方法
1. ターミナルに戻り `ctrl+C` でプログラムを終了する．
2. Arduino SDKを終了し，PCからArduinoを外す．
