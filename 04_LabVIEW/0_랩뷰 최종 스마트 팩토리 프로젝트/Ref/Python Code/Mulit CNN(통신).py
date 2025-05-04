import os
from tensorflow.keras.preprocessing.image import ImageDataGenerator
import tensorflow as tf
import matplotlib.pyplot as plt
import gc
from tensorflow.python.keras.models import load_model
from tensorflow.keras.preprocessing.image import array_to_img
import numpy as np
import socket
from tensorflow import keras

rootPath = r'C:\Users\User\Desktop\이덕규\LabVIEW\교육\2022\2022.03.24~2022.03.25, 2022.04.21~2022.04.22 대한상공회의소\2022.04.21~2022.04.22 Final Project\프로젝트(대한상공회의소)\프로젝트\Data\CNN\Dataset\Color'

imageGenerator = ImageDataGenerator(
    rescale=1./255,
    rotation_range=20,
    width_shift_range=0.1,
    height_shift_range=0.1,
    brightness_range=[.2, .2],
    horizontal_flip=True,
    validation_split=.1
)

model = keras.models.load_model(r'C:\Users\User\Desktop\이덕규\LabVIEW\교육\2022\2022.03.24~2022.03.25, 2022.04.21~2022.04.22 대한상공회의소\2022.04.21~2022.04.22 Final Project\프로젝트(대한상공회의소)\프로젝트\Data\CNN\Test\COLOR.h5')

testGen = imageGenerator.flow_from_directory(
    os.path.join(rootPath, 'Test'),
    target_size=(64, 64),
)

rootPath2 = r'C:\Users\User\Desktop\이덕규\LabVIEW\교육\2022\2022.03.24~2022.03.25, 2022.04.21~2022.04.22 대한상공회의소\2022.04.21~2022.04.22 Final Project\프로젝트(대한상공회의소)\프로젝트\Data\CNN\Dataset\Color'

imageGenerator2 = ImageDataGenerator(
    rescale=1./255,
    rotation_range=20,
    width_shift_range=0.1,
    height_shift_range=0.1,
    brightness_range=[.2, .2],
    horizontal_flip=True,
    validation_split=.1
)

model2 = keras.models.load_model(r'C:\Users\User\Desktop\이덕규\LabVIEW\교육\2022\2022.03.24~2022.03.25, 2022.04.21~2022.04.22 대한상공회의소\2022.04.21~2022.04.22 Final Project\프로젝트(대한상공회의소)\프로젝트\Data\CNN\Test\SHAPE.h5')

testGen2 = imageGenerator2.flow_from_directory(
    os.path.join(rootPath2, 'Test'),
    target_size=(64, 64),
)


server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
server.bind(('localhost', 8087))
server.listen(1)
print("Setting OK")

while True:
    conn, addr = server.accept()
    cmnd = conn.recv(5)
    

    if 'COLOR' in str(cmnd):
        cls_index = ['Blue', 'Green', 'Orange', 'Purple', 'Red', 'Yellow']
        imgs = testGen.next()
        arr = imgs[0][0]
        result = np.argmax(model.predict(arr.reshape(1, 64, 64, 3)), axis=-1)
        data = '{}'.format(cls_index[result[0]])
        conn.sendall(data.encode())
        
    if 'SHAPE' in str(cmnd):
        cls_index = ['Circle', 'Rectangle', 'Square']
        imgs = testGen2.next()
        arr = imgs[0][0]
        result = np.argmax(model2.predict(arr.reshape(1, 64, 64, 3)), axis=-1)
        data = '{}'.format(cls_index[result[0]])
        conn.sendall(data.encode())
        
    elif 'QUIT'in str(cmnd):
        conn.sendall(b'QUIT-DONE')
        break

server.close()