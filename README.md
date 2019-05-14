# Ubibo
これは東京大学Spring Founder Program(SFP)で作製されたものです．

## 環境（動作確認済み）
- Windows 10 / MacOS Mojave
- Python 3.6
    - numpy==1.14.2
    - pyautogui==0.9.38
- Arduino SDK 1.8.5

## 実行方法
1. PCとArduinoをUSBで接続する．
2. Arduino SDKを起動(ただし，シリアルモニタは開かない)
3. ターミナル(コマンドプロンプト等Pythonが実行できる端末)を起動し ```finger_keyboard_arduino.py``` を実行する．optionでportを指定．
```
$ python finger_keyboard_arduino.py --port COM4
```
4. ターミナル上に ```start``` と表示されたら起動成功．
5. 任意のテキストエディタを起動しデバイスを使用してください．

## 終了方法
1. ターミナルに戻り `ctrl+C` でプログラムを終了する．
2. Arduino SDKを終了し，PCからArduinoを外す．