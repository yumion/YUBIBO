import serial
import numpy as np
import os
import time
import struct, binascii
import sys
from analog_to_num import convert_to_region

# MACを使う場合
# s = serial.Serial('/dev/cu.usbserial-MW2UQ1WS', 115200)
# Winを使う場合
s = serial.Serial('COM4', 115200)


def parseTWELite(data):
    data = data[1:]

    ss = struct.Struct('>BBBBBIBHBHBBBBBBBBB')
    data = binascii.unhexlify(data.rstrip())
    parsed = ss.unpack(data)

    digital = [0] * 4
    digitalchanged = [0] * 4
    analog = [0xffff] * 4

    for i in range(4):
        if parsed[11] & (1 << i):
            digital[i] = 1
        else:
            digital[i] = 0
        if parsed[12] & 1<< i:
            digitalchanged[i] = 1
        else:
            digitalchanged[i] = 0

        if parsed[13+i] == 0xff:
            analog[i] = 0xffff
        else:
            analog[i] = (parsed[13+i] * 4 + ((parsed[17] >> (2<<i)) & 3 )) * 4

    result = {'from': parsed[0],
              'lqi': parsed[4],
              'fromid': parsed[5],
              'to': parsed[6],
              'timestamp': parsed[7],
              'isrelay': parsed[8],
              'battery': parsed[9],
              'digital': digital,
              'digitalchanged': digitalchanged,
              'analog': analog}

    return result

def get_num(pre_num):
    data = s.readline()
    parsed = parseTWELite(data)

    data = s.readline()
    parsed  =parseTWELite(data)
    print('vol:', parsed['analog'][0])
    analog_v = parsed['analog'][0]
    num = convert_to_region(analog_v)
    if pre_num != num:
        pre_num = num
        return num
