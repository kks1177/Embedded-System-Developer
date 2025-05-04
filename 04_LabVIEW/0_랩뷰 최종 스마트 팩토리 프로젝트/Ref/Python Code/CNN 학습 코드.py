import os
from tensorflow.keras.preprocessing.image import ImageDataGenerator
from tensorflow.keras.applications import ResNet50
from tensorflow.keras.models import Sequential
from tensorflow.keras import layers
import matplotlib.pyplot as plt



os.environ['TF_ENABLE_WINOGRAD_NONFUSED'] = '1'

rootPath = r'C:\Users\User\Desktop\이덕규\LabVIEW\교육\2022\2022.03.24~2022.03.25, 2022.04.21~2022.04.22 대한상공회의소\2022.04.21~2022.04.22 Final Project\프로젝트(대한상공회의소)\프로젝트\Data\CNN\Dataset\Color'

imageGenerator = ImageDataGenerator(
    rescale=1./255,
    rotation_range=20,
    width_shift_range=0.1,
    height_shift_range=0.1,
    brightness_range=[.2, .2],
    horizontal_flip=True,
    validation_split=.2
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

model = Sequential()
model.add(ResNet50(include_top=True, weights=None, input_shape=(64, 64, 3), classes=6))

model.summary()

model.compile(
    optimizer='adam',
    loss='categorical_crossentropy', 
    metrics=['acc'],
)

history = model.fit(
    x=trainGen,
    validation_data=validationGen,
    steps_per_epoch=16,
    epochs=70
    )

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

    plt.subplot(122)
    plt.plot(epochs, loss, 'bo', label='Training loss')
    plt.plot(epochs, val_loss, 'b', label='Validation loss')
    plt.title('Training and validation loss')
    plt.xlabel('Epochs')
    plt.ylabel('Loss')
    plt.legend(loc='upper center', bbox_to_anchor=(0.5, -0.1),
          fancybox=True, shadow=True, ncol=5)

    plt.show()
    
show_graph(history.history)
    
model.save(r'C:\Users\User\Desktop\이덕규\LabVIEW\교육\2022\2022.03.24~2022.03.25, 2022.04.21~2022.04.22 대한상공회의소\2022.04.21~2022.04.22 Final Project\프로젝트(대한상공회의소)\프로젝트\Data\CNN\Test\COLOR.h5')