# Day21-04_머신러닝1 (붓꽃) 활용.py

import joblib

clf = joblib.load("iris_knn_96.dmp")

# (5. 정답을 모르는 데이터를 가지고 예측! 해보기)
myIris = [5.2,3,3.4,2.1]        # 길에서 우연히 발견한 붓꽃을 발견하고 측정       # 데이터 값 임의로 변경해보기
result = clf.predict([myIris])
print("이 꽃은 -->", result, "입니다.")
