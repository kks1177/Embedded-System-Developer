# 가중치 저장 코드.py

import tensorflow.compat.v1 as tf
import numpy as np
import pandas as pd

tf.disable_v2_behavior()

## xy = np.loadtxt('C:\\Embedded_System\\04_LabVIEW\\Programming_SourceCode\\Test\\data-04-zoo.csv', delimiter=',',
##                 dtype=np.float32)
xy = np.loadtxt('C:\\Embedded_System\\04_LabVIEW\\Programming_SourceCode\\Test\\test2.csv', delimiter=',',
                dtype=np.float32)
x_data = xy[:, 0:-1]
y_data = xy[:, [-1]]

## nb_classes = 7  # Class 수치로 변경해놓을 것
nb_classes = 6  # Class 수치로 변경해놓을 것

## X = tf.placeholder(tf.float32, shape=[None, 16])  # 16부분은 특징 값의 노드 수
X = tf.placeholder(tf.float32, shape=[None, 3])  # 16부분은 특징 값의 노드 수
Y = tf.placeholder(tf.int32, shape=[None, 1])  # shape = (?, 1)

Y_one_hot = tf.one_hot(Y, nb_classes)

Y_one_hot = tf.reshape(Y_one_hot, [-1, nb_classes])

## W = tf.Variable(tf.random_normal([16, nb_classes]), name="weight")  # 행렬 연산을 하기 위해 특징 값 노드 수와 동일
W = tf.Variable(tf.random_normal([3, nb_classes]), name="weight")  # 행렬 연산을 하기 위해 특징 값 노드 수와 동일
# b = tf.Variable(tf.random_normal([nb_classes]), name="bias")

logits = tf.matmul(X, W)
# + b
hypothesis = tf.nn.softmax(logits)

cost_i = tf.nn.softmax_cross_entropy_with_logits(logits=logits, labels=Y_one_hot)
cost = tf.reduce_mean(cost_i)

train = tf.train.GradientDescentOptimizer(learning_rate=0.001).minimize(cost)       # Learning_Rate : 0.001 -> (0.1 or 0.01) 변경 해보기

prediction = tf.argmax(hypothesis, 1)
correct_prediction = tf.equal(prediction, tf.argmax(Y_one_hot, 1))
accuracy = tf.reduce_mean(tf.cast(correct_prediction, tf.float32))

# 세션 시작
with tf.Session() as sess:
    sess.run(tf.global_variables_initializer())

    # 학습량
    for step in range(10000):       # 10000 -> (100 or 1000) 으로 변경 해보기
        sess.run(train, feed_dict={X: x_data, Y: y_data})
        if step % 100 == 0:
            loss, acc = sess.run([cost, accuracy], feed_dict={X: x_data, Y: y_data})
            print(step, sess.run([cost, accuracy], feed_dict={X: x_data, Y: y_data}))
    print(sess.run([W]))
    wt = np.array(sess.run([W]))

print(wt)
wtt = wt.reshape(-1, wt.shape[-1])
print(wtt)

data = wtt
dataframe = pd.DataFrame(data)
# 가중치 경로
## dataframe.to_csv('C:\\Embedded_System\\04_LabVIEW\\Programming_SourceCode\\Test\\weight.csv', header=False, index=False)
dataframe.to_csv('C:\\Embedded_System\\04_LabVIEW\\Programming_SourceCode\\Test\\weight2.csv', header=False, index=False)
