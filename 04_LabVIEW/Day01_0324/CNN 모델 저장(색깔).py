# CNN 모델 저장(색깔).py

import os
from tensorflow.keras.preprocessing.image import ImageDataGenerator

# 위노그라드 알고리즘 설정
os.environ['TF_ENABLE_WINOGRAD_NONFUSED'] = '1'N

rootPath = 'C:/Embedded_System/04_LabVIEW/Programming_SourceCode/Color_Dataset'

imageGenerator = ImageDataGenerator(
    rescale=1. / 255,
    rotation_range=20,
    width_shift_range=0.1,
    height_shift_range=0.1,
    brightness_range=[.2, .2],
    horizontal_flip=True,
    validation_split=.1     # 0.3 이상으로 설정하지 않는 것이 좋음
)

trainGen = imageGenerator.flow_from_directory(
    os.path.join(rootPath, 'Train'),
    target_size=(64, 64),
    subset='training'
)

validationGen = imageGenerator.flow_from_directory(
    os.path.join(rootPath, 'Train'),
    target_size=(64, 64),
    subset='validation'
)

from tensorflow.keras.applications import ResNet50  # ResNet50 -> CNN 알고리즘
from tensorflow.keras.models import Sequential
from tensorflow.keras import layers

model = Sequential()
model.add(ResNet50(include_top=True, weights=None, input_shape=(64, 64, 3),
                   classes=6))  # 64,64: 이미지 크기 64x64, 3: (R,G,B), 6: 6개의 클래스(색깔 6가지)

model.summary()

model.compile(
    optimizer='adam',
    loss='binary_crossentropy',
    metrics=['acc'],
)

epochs = 150
# history = model.fit_generator(
history = model.fit(
    trainGen,
    epochs=epochs,
    steps_per_epoch=trainGen.samples / epochs,
    validation_data=validationGen,
    validation_steps=trainGen.samples / epochs,
)

# 그래프 출력 코드
import matplotlib.pyplot as plt


def show_graph(history_dict):
    accuracy = history_dict['acc']
    val_accuracy = history_dict['val_acc']
    loss = history_dict['loss']
    val_loss = history_dict['val_loss']

    epochs = range(1, len(loss) + 1)

    plt.figure(figsize=(16, 1))

    plt.subplot(121)
    plt.subplots_adjust(top=2)
    plt.plot(epochs, accuracy, 'ro', label='Training accuracy')
    plt.plot(epochs, val_accuracy, 'r', label='Validation accuracy')
    plt.title('Trainging and validation accuracy and loss')
    plt.xlabel('Epochs')
    plt.ylabel('Accuracy and Loss')

    plt.legend(loc='upper center', bbox_to_anchor=(0.5, -0.1),
               fancybox=True, shadow=True, ncol=5)
    #     plt.legend(bbox_to_anchor=(1, -0.1))

    plt.subplot(122)
    plt.plot(epochs, loss, 'bo', label='Training loss')
    plt.plot(epochs, val_loss, 'b', label='Validation loss')
    plt.title('Training and validation loss')
    plt.xlabel('Epochs')
    plt.ylabel('Loss')
    plt.legend(loc='upper center', bbox_to_anchor=(0.5, -0.1),
               fancybox=True, shadow=True, ncol=5)
    #     plt.legend(bbox_to_anchor=(1, 0))

    plt.show()


# show_graph(history.history)

# testGenerator = ImageDataGenerator(
#    rescale=1./255
# )

# testGen = imageGenerator.flow_from_directory(
#    os.path.join(rootPath, 'Test'),
#    target_size=(64, 64),
# )

# model.evaluate_generator(testGen)
# 학습에 사용된 가중치와 모델 저장 경로
model.save('C:/Embedded_System/04_LabVIEW/Programming_SourceCode/Test/DataSet/RSP.h5')
