# coding: UTF-8
import numpy as np
from time import sleep
import os
import pyautogui as pgui  #pythonからキーボードを操作

## Arduinoに信号を送信
'''Arduino SDKを起動し，シリアルモニタは開かない'''
import serial
ser = serial.Serial()
ser.baudrate = 115200
# for file in os.listdir('/dev'):
#     if "cu.usbserial-" in file:
ser.port = 'COM3'
ser.open() # シリアルモニタを開く
sleep(2) # 開いてから信号を送信するまで2秒待つ必要がある

######### 入力 #########
# UP:0 DOWN:1
# i:2 a:3 ka:4 sa:5 se:6
# f2:7 f3:8 f4:9 f5:10
# 何もなし:11
########################

consonant = 0 # 子音
count = 0
consonant_words = ['', 'k', 's']
# consonant_words = [['', 'k', 's'],['t','n','h'],['m','y','r'],['','y','r']]
# consonant_words = [['あ', 'い', 'う', 'え', 'お'],
#                 ['か', 'き', 'く', 'け', 'こ'],
#                 ['さ', 'し', 'す', 'せ', 'そ'],
#                 ['た', 'ち', 'つ', 'て', 'と'],
#                 ['な', 'に', 'ぬ', 'ね', 'の'],
#                 ['は', 'ま', 'や', 'ら', 'わ'],
#                 ['ま', 'み', 'む', 'め', 'も'],
#                 ['や', '', 'ゆ', '', 'よ'],
#                 ['ら', 'り', 'る', 'れ', 'ろ'],
#                 ['わ', 'を', 'ん', '', '']]


print('start')
while True:
    read = ser.readline()
    location = int(read.strip().decode('utf-8'))
     # = int(read.strip().decode('utf-8')) # stripで余分な文字列を排除
    print(count, location)
    if consonant == 0:
        if location in np.arange(3,6): # 真ん中3つのボタンをタッチ
            consonant = location # 子音を決定
            consonant_word = consonant_words[consonant-3]

    else:
        pgui.press('kana')
        pgui.press('kana') # Windowsでは2回必要
        if location == consonant - 1:
            pgui.typewrite(consonant_word+'i')
            count = 0
            consonant = 0
        elif location == 0:
            pgui.typewrite(consonant_word+'u')
            count = 0
            consonant = 0
        elif location == consonant + 1:
            pgui.typewrite(consonant_word+'e')
            count = 0
            consonant = 0
        elif location == 1:
            pgui.typewrite(consonant_word+'o')
            count = 0
            consonant = 0
        elif count == 10:
            pgui.typewrite(consonant_word+'a')
            count = 0
            consonant = 0
        sleep(1)
        count += 1

ser.close()
