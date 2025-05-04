# Day22-05_딥러닝 동영상 인식.py

## 동영상 인식 딥러닝 (SSD) ##
import cv2
import random
import numpy as np


### 전역 변수 ###

### 함수 ###
# 딥러닝 기반의 사물인식 --> DNN
# - DNN 방식으로 학습시킨 Pre-Trained Data 를 가져다가 활용하기
# - OpenCV에서 위 데이터를 사용할 수 있음 --> MobileNet SSD
# - 21가지 : "background", "aeroplane", "bicycle", "bird", "boat",
#                "bottle", "bus", "car", "cat", "chair", "cow", "diningtable",
#                "dog", "horse", "motorbike", "person", "pottedplant", "sheep",
#                "sofa", "train", "tvmonitor"
def ssdNet(image, confPara):
    CONF_VALUE = confPara
    CLASSES = ["background", "aeroplane", "bicycle", "bird", "boat",
               "bottle", "bus", "car", "cat", "chair", "cow", "diningtable",
               "dog", "horse", "motorbike", "person", "pottedplant", "sheep",
               "sofa", "train", "tvmonitor"]
    COLORS = np.random.uniform(0, 255, size=(len(CLASSES), 3))
    # 아래 코드가 핵심! OpenCV
    net = cv2.dnn.readNetFromCaffe("./MobileNetSSD/MobileNetSSD_deploy.prototxt.txt",
                                   "./MobileNetSSD/MobileNetSSD_deploy.caffemodel")
    (h, w) = image.shape[:2]
    blob = cv2.dnn.blobFromImage(cv2.resize(image, (300, 300)), 0.007843, (300, 300), 127.5)
    net.setInput(blob)
    detections = net.forward()

    for i in np.arange(0, detections.shape[2]):
        confidence = detections[0, 0, i, 2]
        if confidence > CONF_VALUE:
            idx = int(detections[0, 0, i, 1])
            box = detections[0, 0, i, 3:7] * np.array([w, h, w, h])
            (startX, startY, endX, endY) = box.astype("int")
            label = "{}: {:.2f}%".format(CLASSES[idx], confidence * 100)
            cv2.rectangle(image, (startX, startY), (endX, endY),
                          COLORS[idx], 2)
            y = startY - 15 if startY - 15 > 15 else startY + 15
            cv2.putText(image, label, (startX, y),
                        cv2.FONT_HERSHEY_SIMPLEX, 0.5, COLORS[idx], 2)
    return image


### 메인 함수 ###
filename = 'C:/images/images(Deep Learning)/traffic.mp4'
capture = cv2.VideoCapture(filename)
scale_factor = 0.5      # 화면 크기 비율 (조절 가능)

frameCount = 0
while True:
    ret, frame = capture.read()

    if not ret:
        break

    # 동영상 딥러닝
    frameCount += 1
    if frameCount % 5 == 0:
        frame = cv2.resize(frame, None, fx=scale_factor, fy=scale_factor,
                           interpolation=cv2.INTER_AREA)
        frame = ssdNet(frame, 0.5)
        cv2.imshow('', frame)

    # 동영상 중간에 중단할 때 --> esc키 입력
    key = cv2.waitKey(20)
    if key == 27:       # esc
        break
    # 캡쳐 --> C키 입력
    elif key == ord('c') or key == ord('C'):
        cv2.imwrite('save' + str(random.randint(111111, 999999)) + '.png', frame)

capture.release()
cv2.destroyAllWindows()

