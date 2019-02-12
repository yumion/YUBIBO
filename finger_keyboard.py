# coding: UTF-8
import numpy as np
from time import sleep
import os
import pyautogui as pgui  #pythonからキーボードを操作

## Arduinoに信号を送信
'''Arduino SDKは起動し，シリアルモニタは開かない'''
import serial
ser = serial.Serial()
ser.baudrate = 115200
for file in os.listdir('/dev'):
    if "cu.usbserial-" in file:
        ser.port = '/dev/'+file
        ser.open() # シリアルモニタを開く
sleep(2) # 開いてから信号を送信するまで2秒待つ必要がある

######### 入力 #########
# UP:0 DOWN:1
# i:2 a:3 ka:4 sa:5 se:6
# 何もなし:7
########################

consonant = 0
count = 0
consonant_words = ['', 'k', 's']

while True:
    read = ser.readline()
    location = int(read.strip().decode('utf-8')) # stripで余分な文字列を排除
    count += 1
    if consonant == 0:
        if location in np.arange(3,6):
            consonant = location
            consonant_word = consonant_words[consonant-3]

    else:
        pgui.press('kana')
        pgui.press('kana') # Windowsでは2回必要
        if location == consonant - 1:
            pgui.typewrite(consonant_word+'i')
        elif location == 0:
            pgui.typewrite(consonant_word+'u')
        elif location == consonant + 1:
            pgui.typewrite(consonant_word+'e')
        elif location == 1:
            pgui.typewrite(consonant_word+'o')
        elif count == 5:
            pgui.typewrite(consonant_word+'a')
            count = 0
        sleep(0.1)
        consonant = 0

ser.close()
