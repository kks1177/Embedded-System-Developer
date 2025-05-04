import os
from tensorflow.keras.preprocessing.image import ImageDataGenerator
import matplotlib.pyplot as plt
import gc
from tensorflow import keras
from tensorflow.keras.preprocessing.image import array_to_img
import tensorflow.compat.v1 as tf
import numpy as np
import socket
tf.disable_v2_behavior()


rootPath = r'C:\Users\유현재\Desktop\2021.10.20~2021.10.22 Final Project\Shape_Dataset'

imageGenerator = ImageDataGenerator(
    rescale=1./255,
    rotation_range=20,
    width_shift_range=0.1,
    height_shift_range=0.1,
    brightness_range=[.2, .2],
    horizontal_flip=True,
    validation_split=.2
)

model = keras.models.load_model(r'C:\Users\유현재\Desktop\유현재\랩뷰 교육\대한 상공회의소(2022상반기)\2022.04.13~2022.04.15 Final Project\Python\Shape_R.h5')

testGen = imageGenerator.flow_from_directory(
    os.path.join(rootPath, 'Test'),
    target_size=(64, 64),
)

rootPath2 = r'C:\Users\유현재\Desktop\2021.10.20~2021.10.22 Final Project\Color_Dataset'

imageGenerator2 = ImageDataGenerator(
    rescale=1./255,
    rotation_range=20,
    width_shift_range=0.1,
    height_shift_range=0.1,
    brightness_range=[.2, .2],
    horizontal_flip=True,
    validation_split=.1
)

model2 = keras.models.load_model(r'C:\Users\유현재\Desktop\유현재\랩뷰 교육\대한 상공회의소(2022상반기)\2022.04.13~2022.04.15 Final Project\Python\Color.h5')

testGen2 = imageGenerator2.flow_from_directory(
    os.path.join(rootPath2, 'Test'),
    target_size=(64, 64),
)

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
server.bind(('localhost', 8103))
server.listen(1)
print("Setting OK")

while True:
    conn, addr = server.accept()
    cmnd = conn.recv(9)  # The default size of the command packet is 4 bytes
    #print(cmnd)

    if 'COLOR' in str(cmnd):

        # Do the initialization action
        cls_index = ['Blue', 'Green', 'Orange', 'Purple', 'Red', 'Yellow']
        imgs = testGen2.next()
        arr = imgs[0][0]
        img = array_to_img(arr).resize((128, 128))
        plt.imshow(img)
        result = np.argmax(model.predict(arr.reshape(1, 64, 64, 3)), axis=-1)
        #result = model2.predict_classes(arr2.reshape(1, 64, 64, 3))
        #print('예측: {}'.format(cls_index[result[0]]))
        data = '{}'.format(cls_index[result[0]])
        conn.sendall(data.encode())
        gc.collect()

    elif 'SHAPE' in str(cmnd):

        # Do the initialization action
        cls_index = ['Circle', 'Rectangle', 'Square']
        imgs = testGen.next()
        arr = imgs[0][0]
        img = array_to_img(arr).resize((128, 128))
        plt.imshow(img)
        result = np.argmax(model.predict(arr.reshape(1, 64, 64, 3)), axis=-1)
        #result = model.predict_classes(arr1.reshape(1, 64, 64, 3))
        #print('예측: {}'.format(cls_index[result[0]]))
        data = '{}'.format(cls_index[result[0]])
        conn.sendall(data.encode())
        gc.collect()
        
    elif 'QUIT'in str(cmnd):
        # Do the quiting action
        conn.sendall(b'QUIT-DONE')
        gc.collect()
        break

server.close()