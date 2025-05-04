# Day21-02_Quiz2.py
# *********************** < 모든 인공지능 처리 과정 절차 > *************************
# 0. 데이터 준비 --> 150건
# 1. (중요!) 학습용 데이터와 테스트(=모의고사)용 데이터를 분리
# 2. 학습 방법을 결정 (=머신 러닝 알고리즘을 선택) --> 다양함, Knn, SVM, SVC .....
# 3. 학습(=훈련) 시키기 --> 오래 걸림 --> 모델(=인공지능) 생성       # 모델 : 빈 머리
# 4. 모델의 정답률 구하기 (모의고사 시험)
# (5. 정답을 모르는 데이터를 가지고 예측! 해보기)
# *****************************************************************************
# 붓꽃 구별하기. 머신러닝 프로젝트
# Decision Tree 알고리즘

# 퀴즈2. 아이리스 머신러닝 프로젝트 2  ---> 2시 50분까지
# - iris.csv의 label을 맨 앞으로 변경 ---> 엑셀 사용
# - 비율 -> 7:3 으로
# - 변수 이름 변경 : train -> study, test -> exam, dlf -> ai
# 알고리즘 변경
# 주석 달기 (자신이 이해하기 쉽게)


from sklearn.tree import DecisionTreeClassifier      # Decision Tree 알고리즘

from sklearn import metrics, utils
import pandas as pd         # .csv 또는 엑셀 파일 처리가 편리

# 0. 데이터(=문제집) 준비 --> 150건
df = pd.read_csv('iris2.csv')    # DataFrame == 2차원 배열 == 워크시트
df = utils.shuffle(df)          # (중요!) .csv에 있는 데이터를 섞어줌

# 1. (중요!) 학습용 데이터와 테스트(=모의고사)용 데이터를 분리
dataLen = df.shape[0]       # 데이터 개수 (150)
studySize = int(dataLen * 0.7)      # 70%는 훈련용      # 0.8 은 조절 가능, But, 8:2 정도가 적당
examSize = dataLen - studySize      # 30%는 테스트용

study_label = df.iloc[0:studySize, [0]]    # 학습용 정답지       # 0:trainSize  -->  세로(150개 중에 100개 정도만 학습용 정답), [0]  -->  가로(처음 label 1개)
study_data = df.iloc[0:studySize, 1:]     # 학습용 문제집       # 0:trainSize  -->  세로(150개 중에 100개 정도만 학습용 문제), 1:  -->  가로(마지막 data 4개)
exam_label = df.iloc[studySize:, [0]]      # 테스트용 정답지
exam_data = df.iloc[studySize:, 1:]       # 테스트용 문제집

# 2. 학습 방법을 결정 (=머신 러닝 알고리즘을 선택) --> 다양함, Knn, SVM, SVC .....
print(" < Decision Tree 알고리즘 > ")
ai = DecisionTreeClassifier(random_state=32)       # clf : 인공지능, 가장 가까운 비교할 데이터 -> 3개

# 3. 학습(=훈련) 시키기 --> 오래 걸림 --> 모델(=인공지능) 생성       # 모델 : 빈 머리
ai.fit(study_data, study_label)        # 학습 (=훈련)

# 4. 모델의 정답률 구하기 (모의고사 시험)
results = ai.predict(exam_data)      # 테스트 문제만 제공
score = metrics.accuracy_score(results, exam_label)      # 테스트 문제 푼 것에 대한 점수 리턴
print("정답률 : %5.2f" % score)

# (5. 정답을 모르는 데이터를 가지고 예측! 해보기)
myIris = [5.2,3,3.4,2.1]        # 길에서 우연히 발견한 붓꽃을 발견하고 측정       # 데이터 값 임의로 변경해보기
result = ai.predict([myIris])
print("이 꽃은 -->", result, "입니다. 단,", score*100, "%의 확률입니다.")     # 퍼센트를 알려주어야 함

