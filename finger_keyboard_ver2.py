# coding: UTF-8
import numpy as np
from time import sleep
import os
import pyautogui as pgui  #pythonからキーボードを操作

# # pgui.KEYBOARD_KEYS
#
# ## Arduinoに信号を送信
# '''Arduino SDKを起動し，シリアルモニタは開かない'''
# import serial
# ser = serial.Serial()
# ser.baudrate = 115200
#
# ## MACを使う場合
# # for file in os.listdir('/dev'):
# #     if "cu.usbserial-" in file:
# #         ser.port = 'COM3'
# #         ser.open() # シリアルモニタを開く
#
# # winを使う場合
# ser.port = 'COM3'
# ser.open() # シリアルモニタを開く
# sleep(2) # 開いてから信号を送信するまで2秒待つ必要がある

######### 入力 #########
# あ:0　か:1　さ:2
# た:3　な:4　は:5
# ま:5　や:6　ら:7
# :7　わ:8　:9
# 何もなし:10
########################
word_dict = [['あ','']]
consonant = 0 # 子音
count = 0
consonant_words = ['', 'k', 's', 't', 'n', 'h', 'm', 'y', 'w']
vowel_words = ['a','i','u','e','o']
c = 0
print('start')

while True:
    location = int(input())
    # read = ser.readline()
    # location = int(read.strip().decode('utf-8')) # stripで余分な文字列を排除
    count = count % 5


    print(count, location)

    pgui.press('kana')
    pgui.press('kana') # Windowsでは2回必要
    if location != 10:
        if c == 0:
            pgui.typewrite(consonant_words[location]+vowel_words[count])
            pre_location = location
        elif pre_location == location:
            pgui.press('backspace')
            pgui.typewrite(consonant_words[location]+vowel_words[count])
        count += 1
    c += 1

# ser.close()
