# coding: UTF-8
import numpy as np
from time import sleep
import os
import pyautogui as pgui  # pythonからキーボードを操作
from twelite_read import get_num
from twelite_read import parseTWELite

######### 入力 #########
# あ:0　か:1　さ:2
# た:3　な:4　は:5
# ま:6　や:7　ら:8
# 濁点、半濁点、小文字:9　わ:10　:11
# space:12 backspace:13 enter:14
# 何もなし:15
########################
count = 0
op_count = 0
pre_location = None
consonant_words = ['', 'k', 's', 't', 'n', 'h', 'm', 'y','r','','w','']
voiced_consonant_words = ['', 'g', 'z', 'd', '', 'b']
vowel_words = ['a','i','u','e','o']
yayuyo_words = ['ya','yu','yo']
waon_words = ['wa','wo','nn']
pre_num = 15

print('start')

pgui.press('kana')
# pgui.press('kana') # Windowsでは2回必要
while True:
    # location = int(input())
    location = get_num(pre_num)
    if location == None:
        location = 15
    # read = ser.readline()
    # location = int(read.strip().decode('utf-8')) # stripで余分な文字列を排除
    count = count % 5
    print(count, op_count, location)

    if location != 15 and location != 9 and location != 7 and location != 10 and location < 11: #入力なし、濁点、11,以外入力された場合
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

    elif location == 7:
        if pre_location != location:
            count = 0
            pgui.typewrite(consonant_words[location]+vowel_words[count])
            # print(consonant_words[location]+vowel_words[count])
            pre_location = location
        else:
            pgui.press('backspace')
            pgui.typewrite(yayuyo_words[count])

        count += 1
        if count==3:
            count=0

    elif location == 10:
        if pre_location != location:
            count = 0
            pgui.typewrite(consonant_words[location]+vowel_words[count])
            # print(consonant_words[location]+vowel_words[count])
            pre_location = location
        else:
            pgui.press('backspace')
            pgui.typewrite(waon_words[count])
        count += 1
        if count==3:
            count=0

    elif location == 9: #濁点
        # print('option')
        if op_count == 0 and pre_location in [1,2,3,5]:
            pgui.press('backspace')
            pgui.typewrite(voiced_consonant_words[pre_location]+vowel_words[count-1])
            # print('濁点')
            # print(voiced_consonant_words[pre_location]+vowel_words[count-1])
            if pre_location == 5 or (pre_location==3 and count==3): #
                op_count+=1

        elif op_count == 1 and pre_location == 5:
            pgui.press('backspace')
            pgui.typewrite('p'+vowel_words[count-1])
            # print('半濁点')
            # print('p'+vowel_words[count-1])
            op_count=0

        elif (pre_location in [0,7]) or (pre_location==3 and count==3):
            pgui.press('backspace')
            pgui.typewrite('x'+consonant_words[pre_location]+vowel_words[count-1])
            op_count=0
            # print('小文字')
            # print('x'+consonant_words[pre_location]+vowel_words[count-1])

    elif location ==12:
        pgui.press('space')
        # print('space')
    elif location ==13:
        pgui.press('backspace')
        # print('backspace')
    elif location ==14:
        pgui.press('enter')
        # print('enter')
