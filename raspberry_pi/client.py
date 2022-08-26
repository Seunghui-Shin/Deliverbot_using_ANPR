import socket
import videoTest
import cv2
import imutils
import numpy as np
import pytesseract
from PIL import Image
from picamera.array import PiRGBArray
from picamera import PiCamera
import smtplib
import schedule
from time import sleep

IP = "192.168.0.145"
PORT = 4455
ADDR = (IP, PORT)
SIZE = 1024
FORMAT = "utf-8"
ROOMS_NUMBER = ["101", "112", "123"]


## '123abc' 같이 int, string이 섞여 들어오는 경우 return '0' 으로 반환시켜줌
def msg_type_checker(msg):
    msg = msg.replace("","")
    msg = msg.replace("\n","")
    msg = msg.replace(";","")
    msg = msg.replace(",","")
    msg = msg.replace("}","")
    msg = msg.replace(")","")
    try:
        type(int(msg))
        for room in ROOMS_NUMBER:
            if(room==msg):
                return msg
        return "0"
    except: 
        return "0"

def main():
    """ TCP Socket """
    client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client.connect(ADDR)

    """ Recv data 
    data = client.recv(SIZE).decode(FORMAT)
    print(f"[SERVER] {data}")"""

    """ Send data """
    while True:
        camera = PiCamera()
        camera.resolution = (640, 480)
        camera.framerate = 30
        rawCapture = PiRGBArray(camera, size=(640, 480))
        msg = videoTest.cam(camera,rawCapture)
        msg = msg_type_checker(msg)
        client.sendall(msg.encode(FORMAT))
        data = client.recv(SIZE).decode(FORMAT)
        print(f"[SERVER] {data}")
        camera.close()

    """ Close connection """
    client.close()

if __name__ == "__main__":
    main()