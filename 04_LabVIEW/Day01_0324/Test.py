# Test.py

import gc
import os
import matplotlib.pyplot as plt
from tensorflow.keras.preprocessing.image import ImageDataGenerator
import tensorflow as tf
from tensorflow import keras

rootPath ='C:/Embedded_System/04_LabVIEW/Programming_SourceCode/Color_Dataset'

imageGenerator = ImageDataGenerator(
    rescale=1. / 255,
    rotation_range=20,
    width_shift_range=0.1,
    height_shift_range=0.1,
    brightness_range=[.2, .2],
    horizontal_flip=True,
    validation_split=.1
)

imageGenerator2 = ImageDataGenerator(
    rescale=1. / 255,
    rotation_range=20,
    width_shift_range=0.1,
    height_shift_range=0.1,
    brightness_range=[.2, .2],
    horizontal_flip=True,
    validation_split=.2
)

from tensorflow import keras

# h5 파일을 불러오는 코드
model = keras.models.load_model('C:/Embedded_System/04_LabVIEW/Programming_SourceCode/Test/DataSet/COLOR.h5')

model.summary()


testGenerator = ImageDataGenerator(
    rescale=1. / 255
)



testGen = imageGenerator.flow_from_directory(
    os.path.join(rootPath, 'Test'),
    target_size=(64, 64)
)


from tensorflow.keras.preprocessing.image import array_to_img
import socket
import numpy as np


# Class_index, 클래스 종류의 이름을 써넣어야 함 (반드시 폴더에 있는 순으로)
cls_index = ['blue     ', 'green    ', 'orange   ', 'purple   ', 'red      ', 'yellow   ']
imgs = testGen.next()
arr = imgs[0][0]
result = np.argmax(model.predict(arr.reshape(1, 64, 64, 3)), axis=-1)
data = '{}'.format(cls_index[result[0]])
print(data)

gc.collect()


