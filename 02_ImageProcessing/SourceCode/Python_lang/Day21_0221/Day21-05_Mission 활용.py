# Day21-05_Mission 저장.py

import joblib

clf = joblib.load("bmi_knn_95.dmp")
print("95% 확률")
# (5. 정답을 모르는 데이터를 가지고 예측! 해보기)
myIris = [1, 170, 75]        # 길에서 우연히 발견한 붓꽃을 발견하고 측정       # 데이터 값 임의로 변경해보기
result = clf.predict([myIris])
print("비만도(1:심각한 저체중, 2:저체중, 3:보통, 4:과체중, 5:비만)")
print("BMI 지수 -->", result, "입니다.")     # 퍼센트를 알려주어야 함
