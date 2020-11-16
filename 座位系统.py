'''
Description: 
Version: 1.0
Autor: Alouette
Date: 2020-11-15 16:09:23
LastEditors: Alouette
LastEditTime: 2020-11-15 16:39:29
'''

# -*- coding: utf-8 -*-
import serial
import time
import requests
import json
ser = serial.Serial("/dev/ttyUSB0", 115200)
puturl = 'https://api.heclouds.com/devices/'+'647644886'+'/datapoints'
get_mult_url = 'https://api.heclouds.com/devices/'+'647644886'+'/datapoints'

data1 = {
    'datastreams': [{'id': 'state1', 'datapoints': [{'value': '无人'}]}]
}
data2 = {
    'datastreams': [{'id': 'state1', 'datapoints': [{'value': '有人'}]}]
}
data3 = {
    'datastreams': [{'id': 'state1', 'datapoints': [{'value': '正在离开'}]}]
}


def http_post(jdata):
    r = requests.post(url=puturl, headers=headers, data=jdata)
    print(r.text)


def main():
    while True:
        count = ser.inWaiting()
        temp = 'a'
        if count != 0:
            recv = ser.read(count)
            if(temp != recv):
                if(recv == 'b'):
                    jdata = json.dumps(data1)
                    http_post(jdata)
                elif(recv == 'c'):
                    jdata = json.dumps(data2)
                    http_post(jdata)
                else:
                    jdata = json.dumps(data3)
                    http_post(jdata)
            temp = recv
            print(recv)
            # ser.write(recv)
        ser.flushInput()
        time.sleep(0.1)


if __name__ == '__main__':
    try:
        main()
    except KeyboardInterrupt:
        if ser != None:
            ser.close()
