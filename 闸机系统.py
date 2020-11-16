#!/usr/bin/python
# -*- coding: utf-8 -*-
'''
Description: 
Version: 1.0
Autor: Alouette
Date: 2020-11-11 16:22:26
LastEditors: Alouette
LastEditTime: 2020-11-15 16:26:00
'''
from aip import AipFace
import serial
import requests
import cv2 as cv
import base64
import time
import json
# 百度人脸识别API账号信息
APP_ID = '22952914'
API_KEY = 'NCmftF9wV7f7BqCW4F7GRKrE'
SECRET_KEY = 'BzRrQvR2Bn75zvDucofDZHals9zsFB1i'
client = AipFace(APP_ID, API_KEY, SECRET_KEY)  # 创建一个客户端用以访问百度云
# 图像编码方式
IMAGE_TYPE = 'BASE64'
camera = cv.VideoCapture(0)  # 定义一个摄像头对象
camera.set(3, 240)
camera.set(4, 160)
# 用户组
GROUP = 'admin'
# 串口设置
serialPort = "/dev/ttyUSB0"  # 串口
baudRate = 115200  # 波特率
ser = serial.Serial(serialPort, baudRate, timeout=0.5)
# 照相函数
headers = {'api-key': 'Gd4KJf9kOF4Tjsv6Pk6bMO4s=D8='}
data = {
    'datastreams': [{'id': 'temperature', 'datapoints': [{'value': '--'}]}, {'id': 'name', 'datapoints': [{'value': "--"}]}, {'id': 'state', 'datapoints': [{'value': "--"}]}]
}
jdata = json.dumps(data)

puturl = 'https://api.heclouds.com/devices/' + '647644886' + '/datapoints'
get_mult_url = 'https://api.heclouds.com/devices/' + '647644886' + '/datapoints'
k = 1


def http_post(jdata):
    r = requests.post(url=puturl, headers=headers, data=jdata)
    print(r.text)


def http_get():
    r = requests.get(url=get_mult_url, headers=headers)
    print(r.text)


def getimage():
    if(camera.isOpened()):
        Vshow = camera.read()
        cv.imshow("camera", Vshow[1])
        cv.imwrite("faceimage.jpg", Vshow[1])
        cv.waitKey(700)
        # cv.destroyAllWindows()
# 对图片的格式进行转换
        # camera.release()


def transimage():
    f = open('faceimage.jpg', 'rb')
    img = base64.b64encode(f.read())
    return img
# 上传到百度api进行人脸检测


def go_api(image):
    result = client.search(str(image), IMAGE_TYPE,
                           GROUP)  # 在百度云人脸库中寻找有没有匹配的人脸
    if result['error_msg'] == 'SUCCESS':  # 如果成功了
        name = result['result']['user_list'][0]['user_id']  # 获取名字
        user_num = result['result']['user_list'][0]['user_num']  # 获取学号
        score = result['result']['user_list'][0]['score']  # 获取相似度
        if score > 80:  # 如果相似度大于80
            if name != NULL:
                print("欢迎%s!", name)
                http_post()
                s1 = str("number")
                ser.write((s1).encode())
                s3 = ser.read()
                if(int(s3) > 40):
                    s4 = "打卡异常"
                else:
                    s4 = "打卡成功"
                data = {
                    'datastreams': [
                        {'id': 'temperature',
                         'datapoints': [{'value': s3}]},
                        {'id': 'name', 'datapoints': [{'value': name}]},
                        {'id': 'state', 'datapoints': [{'value': s4}]}]
                }
                jdata = json.dumps(data)
                http_post(jdata)
                time.sleep(5)
        else:
            s2 = str("0000000000b")
            ser.write((s2).encode())
            print("对不起，我不认识你！")
            name = 'Unknow'
            return 0
        curren_time = time.asctime(time.localtime(time.time()))  # 获取当前时间

        # 将人员出入的记录保存到Log.txt中
        f = open('Log.txt', 'a')
        f.write("Person: " + name + "     " + "Time:" + str(curren_time)+'\n')
        f.close()
        return 1
    if result['error_msg'] == 'pic not has face':
        print('检测不到人脸')
        s2 = str("0000000000b")
        ser.write((s2).encode())
        time.sleep(1)
        return 0
    else:
        print(result['error_code']+' ' + result['error_code'])
        return 0


# 主函数
if __name__ == '__main__':
    while True:
        print('准备')
        if True:
            getimage()  # 拍照
            img = transimage()  # 转换照片格式
            res = go_api(img)  # 将转换了格式的图片上传到百度云
            if(res == 1):  # 是人脸库中的人
                print("开门")
            else:
                print("关门")
            cv.destroyAllWindows()
            print('稍等5秒进入下一个')
            time.sleep(5)
camera.release()
ser.close()
