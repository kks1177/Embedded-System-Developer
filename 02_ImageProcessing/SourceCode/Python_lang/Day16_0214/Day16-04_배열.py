# Day16-04_배열.py

## 함수부


## 전역 변수부
ary1 = []
hap = 0

## 메인 함수
# 빈배열 준비
ary1 = [0 for _ in range(5)]    # Python Style
# for _ in range(5):      # for i in range(5) 에서 i를 사용하지 않으므로 _를 사용
#     ary1.append(0)

# 배열에 값 대입
for i in range(len(ary1)):  # == (0, 3, 1)
    ary1[i] = 100

# 배열을 처리
for i in range(len(ary1)):
    hap += ary1[i]

print(hap)
