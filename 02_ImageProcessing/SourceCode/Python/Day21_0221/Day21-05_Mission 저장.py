# Day21-05_Mission 저장.py
# *********************** < 모든 인공지능 처리 과정 절차 > *************************
# 0. 데이터 준비 --> 150건
# 1. (중요!) 학습용 데이터와 테스트(=모의고사)용 데이터를 분리
# 2. 학습 방법을 결정 (=머신 러닝 알고리즘을 선택) --> 다양함, Knn, SVM, SVC .....
# 3. 학습(=훈련) 시키기 --> 오래 걸림 --> 모델(=인공지능) 생성       # 모델 : 빈 머리
# 4. 모델의 정답률 구하기 (모의고사 시험)
# (5. 정답을 모르는 데이터를 가지고 예측! 해보기)
# *****************************************************************************
# BMI. 머신러닝 프로젝트
# KNN 알고리즘


from sklearn.neighbors import KNeighborsClassifier      # KNN 알고리즘

from sklearn import metrics, utils
import pandas as pd         # .csv 또는 엑셀 파일 처리가 편리

# 0. 데이터(=문제집) 준비 --> 500건
df = pd.read_csv('bmi.csv')    # DataFrame == 2차원 배열 == 워크시트
df = utils.shuffle(df)          # (중요!) .csv에 있는 데이터를 섞어줌

# 1. (중요!) 학습용 데이터와 테스트(=모의고사)용 데이터를 분리
dataLen = df.shape[0]       # 데이터 개수 (500)
trainSize = int(dataLen * 0.8)      # 80%는 훈련용      # 0.8 은 조절 가능, But, 8:2 정도가 적당
testSize = dataLen - trainSize      # 20%는 테스트용

train_label = df.iloc[0:trainSize, [0]]    # 학습용 정답지       # 0:trainSize  -->  세로(150개 중에 100개 정도만 학습용 정답), [0]  -->  가로(처음 label 1개)
train_data = df.iloc[0:trainSize, 1:]     # 학습용 문제집       # 0:trainSize  -->  세로(150개 중에 100개 정도만 학습용 문제), 1:  -->  가로(마지막 data 4개)
test_label = df.iloc[trainSize:, [0]]      # 테스트용 정답지
test_data = df.iloc[trainSize:, 1:]       # 테스트용 문제집

# 2. 학습 방법을 결정 (=머신 러닝 알고리즘을 선택) --> 다양함, Knn, SVM, SVC .....
print(" < KNN 알고리즘 > ")
clf = KNeighborsClassifier(n_neighbors=3)       # clf : 인공지능, 가장 가까운 비교할 데이터 -> 3개

# 3. 학습(=훈련) 시키기 --> 오래 걸림 --> 모델(=인공지능) 생성       # 모델 : 빈 머리
clf.fit(train_data, train_label)        # 학습 (=훈련)

# 4. 모델의 정답률 구하기 (모의고사 시험)
results = clf.predict(test_data)      # 테스트 문제만 제공
score = int(metrics.accuracy_score(results, test_label) * 100)      # 테스트 문제 푼 것에 대한 점수 리턴
print("정답률 : %5.2f" % score)

# # (5. 정답을 모르는 데이터를 가지고 예측! 해보기)
# myIris = [1,180,70]        # 길에서 우연히 발견한 붓꽃을 발견하고 측정       # 데이터 값 임의로 변경해보기
# result = clf.predict([myIris])
# print("비만도(1:심각한 저체중, 2:저체중, 3:보통, 4:과체중, 5:비만)")
# print("BMI 지수 -->", result, "입니다. 단,", score*100, "%의 확률입니다.")     # 퍼센트를 알려주어야 함

# 5. 모델(=인공지능)을 파일로 저장하기
import joblib
filename = "bmi_knn_" + str(score) + ".dmp"
joblib.dump(clf, filename)

print("OK~")
