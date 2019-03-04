# coding: UTF-8
import numpy as np
from time import sleep
import os
import pyautogui as pgui  #pythonからキーボードを操作

# pgui.KEYBOARD_KEYS

# Arduinoに信号を送信
# Arduino SDKを起動し，シリアルモニタは開かない
import serial
ser = serial.Serial()
ser.baudrate = 115200

## MACを使う場合
# for file in os.listdir('/dev'):
#     if "cu.usbserial-" in file:

# winを使う場合
ser.port = 'COM3'
ser.open() # シリアルモニタを開く

######### 入力 #########
# あ:0　か:1　さ:2
# た:3　な:4　は:5
# ま:6　や:7　ら:8
# Space:9　わ:10　Enter:11
# 何もなし:12
########################
count = 0
pre_location = None
consonant_words = ['', 'k', 's', 't', 'n', 'h', 'm', 'y','r','','w','']
vowel_words = ['a','i','u','e','o']

print('start')

while True:
    # location = int(input())

    read = ser.readline()
    location = int(read.strip().decode('utf-8')) # stripで余分な文字列を排除

    count = count % 5

    # print(count, location)

    pgui.press('kana')
    pgui.press('kana') # Windowsでは2回必要

    if location != 12 and location != 9 and location != 11:
        if pre_location != location:
            count = 0
            pgui.typewrite(consonant_words[location]+vowel_words[count])
            # print(consonant_words[location]+vowel_words[count])
            pre_location = location

        else:
            pgui.press('backspace')
            pgui.typewrite(consonant_words[location]+vowel_words[count])
            # print(consonant_words[location]+vowel_words[count])

        count += 1

    elif location == 9:
        pgui.press('space')
        # print('space')
    elif location ==11:
        pgui.press('enter')
        # print('enter')


ser.close()
