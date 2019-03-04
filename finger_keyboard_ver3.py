# coding: UTF-8
import numpy as np
from time import sleep
import os
import pyautogui as pgui  #pythonからキーボードを操作

# pgui.KEYBOARD_KEYS

# Arduinoに信号を送信
# Arduino SDKを起動し，シリアルモニタは開かない
# import serial
# ser = serial.Serial()
# ser.baudrate = 115200

## MACを使う場合
# for file in os.listdir('/dev'):
#     if "cu.usbserial-" in file:

# winを使う場合
# ser.port = 'COM3'
# ser.open() # シリアルモニタを開く

######### 入力 #########
# あ:0　か:1　さ:2
# た:3　な:4　は:5
# ま:6　や:7　ら:8
# Space:9　わ:10　Enter:11
# 何もなし:12
########################
count = 0
op_count = 0
pre_location = None
consonant_words = ['', 'k', 's', 't', 'n', 'h', 'm', 'y','r','','w','']
voiced_consonant_words = ['', 'g', 'z', 'd', '', 'b']
vowel_words = ['a','i','u','e','o']

print('start')

while True:
    location = int(input())

    # read = ser.readline()
    # location = int(read.strip().decode('utf-8')) # stripで余分な文字列を排除

    count = count % 5

    print(count, op_count, location)

    # pgui.press('kana')
    # pgui.press('kana') # Windowsでは2回必要

    if location != 12 and location != 9 and location != 11:
        if pre_location != location:
            count = 0
            # pgui.typewrite(consonant_words[location]+vowel_words[count])
            print(consonant_words[location]+vowel_words[count])
            pre_location = location

        else:
            # pgui.press('backspace')
            # pgui.typewrite(consonant_words[location]+vowel_words[count])
            print(consonant_words[location]+vowel_words[count])

        count += 1

    elif location == 9:
        if op_count == 0 and pre_location in [1,2,3,5]:
            # pgui.press('backspace')
            # pgui.typewrite(voiced_consonant_words[pre_location]+vowel_words[count])
            print('濁点')
            print(voiced_consonant_words[pre_location]+vowel_words[count])
            op_count+=1
        elif op_count == 1 and pre_location in 5:
            # pgui.press('backspace')
            # pgui.typewrite('p'+vowel_words[count])
            print('半濁点')
            print('p'+vowel_words[count])
            op_count+=1
        elif (op_count == 2 and pre_location in [1,7]) or (pre_location==3 and count==2):
            # pgui.press('backspace')
            # pgui.typewrite('x'+consonant_words[location]+vowel_words[count])
            print('小文字')
            print('x'+consonant_words[location]+vowel_words[count])
            op_count=0
    elif location ==11:
        pgui.press('enter')
        # print('enter')


ser.close()
