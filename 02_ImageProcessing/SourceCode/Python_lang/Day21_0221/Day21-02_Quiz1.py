# Day21-02_Quiz1.py
# *********************** < 모든 인공지능 처리 과정 절차 > *************************
# 0. 데이터 준비 --> 150건
# 1. (중요!) 학습용 데이터와 테스트(=모의고사)용 데이터를 분리
# 2. 학습 방법을 결정 (=머신 러닝 알고리즘을 선택) --> 다양함, Knn, SVM, SVC .....
# 3. 학습(=훈련) 시키기 --> 오래 걸림 --> 모델(=인공지능) 생성       # 모델 : 빈 머리
# 4. 모델의 정답률 구하기 (모의고사 시험)
# (5. 정답을 모르는 데이터를 가지고 예측! 해보기)
# *****************************************************************************
# 붓꽃 구별하기. 머신러닝 프로젝트
# Support Vector Machine (SVM 알고리즘)

# 퀴즈1. 학습용 : 테스트용 ---> 6:4, 다른 알고리즘 사용(검색)


from sklearn import svm      # SVM 알고리즘

from sklearn import metrics, utils
import pandas as pd         # .csv 또는 엑셀 파일 처리가 편리

# 0. 데이터(=문제집) 준비 --> 150건
df = pd.read_csv('iris.csv')    # DataFrame == 2차원 배열 == 워크시트
df = utils.shuffle(df)          # (중요!) .csv에 있는 데이터를 섞어줌

# 1. (중요!) 학습용 데이터와 테스트(=모의고사)용 데이터를 분리
dataLen = df.shape[0]       # 데이터 개수 (150)
trainSize = int(dataLen * 0.6)      # 60%는 훈련용      # 0.8 은 조절 가능, But, 8:2 정도가 적당
testSize = dataLen - trainSize      # 40%는 테스트용

train_data = df.iloc[0:trainSize, 0:-1]     # 학습용 문제집       # 0:trainSize  -->  세로(150개 중에 100개 정도만 학습용 문제),  0:-1  --> 가로(data 4개)
train_label = df.iloc[0:trainSize, [-1]]    # 학습용 정답지       # 0:trainSize  -->  세로(150개 중에 100개 정도만 학습용 정답), [-1]  -->  가로(마지막 label 1개)
test_data = df.iloc[trainSize:, 0:-1]       # 테스트용 문제집
test_label = df.iloc[trainSize:, [-1]]      # 테스트용 정답지

# 2. 학습 방법을 결정 (=머신 러닝 알고리즘을 선택) --> 다양함, Knn, SVM, SVC .....
print(" < SVM 알고리즘 > ")
svm_model = svm.SVC()       # svm_model : 인공지능, 가장 가까운 비교할 데이터 -> 3개

# 3. 학습(=훈련) 시키기 --> 오래 걸림 --> 모델(=인공지능) 생성       # 모델 : 빈 머리
svm_model.fit(train_data, train_label)        # 학습 (=훈련)

# 4. 모델의 정답률 구하기 (모의고사 시험)
results = svm_model.predict(test_data)      # 테스트 문제만 제공
score = metrics.accuracy_score(results, test_label)      # 테스트 문제 푼 것에 대한 점수 리턴
print("정답률 : %5.2f" % score)

# (5. 정답을 모르는 데이터를 가지고 예측! 해보기)
myIris = [5.2,3,3.4,2.1]        # 길에서 우연히 발견한 붓꽃을 발견하고 측정       # 데이터 값 임의로 변경해보기
result = svm_model.predict([myIris])
print("이 꽃은 -->", result, "입니다. 단,", score*100, "%의 확률입니다.")     # 퍼센트를 알려주어야 함

