# coding: UTF-8
import serial
import argparse
from time import sleep
import pyautogui as pgui  # pythonからキーボードを操作

# 起動時の引数
parser = argparse.ArgumentParser()
parser.add_argument('--baudrate', type=int, default=9600, help='Baudrate.')
parser.add_argument('--port', type=str, default='COM4', help='Number of port.')
args = parser.parse_args()

# Arduinoに信号を送信
# Arduino SDKを起動し，シリアルモニタは開かない
ser = serial.Serial()
ser.baudrate = args.baudrate  # データ転送レート
ser.port = args.port  # ポート番号
ser.open()  # シリアルモニタを開く
sleep(2)  # シリアルモニタを開いてから2秒待ってから通信する必要あり

######### 入力 #########
# あ:0　か:1　さ:2
# た:3　な:4　は:5
# ま:6　や:7　ら:8
# 濁点、半濁点、小文字:11　わ:10　何もなし:9
# space:12 backspace:13 enter:14
# 何もなし:15
########################

count = 0
op_count = 0
pre_location = None
consonant_words = ['', 'k', 's', 't', 'n',
                   'h', 'm', 'y', 'r', '', 'w', '']  # 子音
voiced_consonant_words = ['', 'g', 'z', 'd', '', 'b']  # 濁点
vowel_words = ['a', 'i', 'u', 'e', 'o']  # 母音
yayuyo_words = ['ya', 'yu', 'yo']  # や行
waon_words = ['wa', 'wo', 'nn']  # わ行
pre_num = 15  # 接触なし

print('start')
pgui.press('kana')
pgui.press('kana')  # Windowsでは2回必要
while True:
    read = ser.readline()
    location = int(read.strip().decode('utf-8'))  # stripで余分な文字列を排除
    print('num: ', location)
    if location is None:
        location = 15
    count = count % 5

    '''入力なし、濁点、11,以外入力された場合'''
    if location != 15 and location != 9 and location != 7 and location != 10 and location < 11:
        if pre_location != location:
            count = 0
            pgui.typewrite(consonant_words[location] + vowel_words[count])
            pre_location = location
        else:
            pgui.press('backspace')
            pgui.typewrite(consonant_words[location] + vowel_words[count])
        count += 1

    # や行
    elif location == 7:
        if pre_location != location:
            count = 0
            pgui.typewrite(consonant_words[location] + vowel_words[count])
            pre_location = location
        else:
            pgui.press('backspace')
            pgui.typewrite(yayuyo_words[count])

        count += 1
        if count == 3:
            count = 0

    # わ行
    elif location == 10:
        if pre_location != location:
            count = 0
            pgui.typewrite(consonant_words[location] + vowel_words[count])
            pre_location = location
        else:
            pgui.press('backspace')
            pgui.typewrite(waon_words[count])
        count += 1
        if count == 3:
            count = 0

    # 濁点
    elif location == 11:
        if op_count == 0 and pre_location in [1, 2, 3, 5]:
            pgui.press('backspace')
            pgui.typewrite(
                voiced_consonant_words[pre_location] + vowel_words[count - 1])
            if pre_location == 5 or (pre_location == 3 and count == 3):
                op_count += 1

        # 半濁音(ぱ行)
        elif op_count == 1 and pre_location == 5:
            pgui.press('backspace')
            pgui.typewrite('p' + vowel_words[count - 1])
            op_count = 0

        # 小文字
        elif (pre_location in [0, 7]) or (pre_location == 3 and count == 3):
            pgui.press('backspace')
            pgui.typewrite(
                'x' + consonant_words[pre_location] + vowel_words[count - 1])
            op_count = 0

    # 変換(space)
    elif location == 12:
        pgui.press('space')
    # delete
    elif location == 13:
        pgui.press('backspace')
    # enter
    elif location == 14:
        pgui.press('enter')
        count = 0  # Enterすると文字確定するのでリセット
