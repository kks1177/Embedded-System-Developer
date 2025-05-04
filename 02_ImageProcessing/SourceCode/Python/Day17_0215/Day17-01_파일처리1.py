# Day17-01_파일처리1.py

## 함수부

## 전역

## 메인 함수부
# 1단계 : 파일 열기
rfp = open('c:\\windows\\win.ini', 'r')
wfp = open('win.txt', 'w')      # 경로 지정 안하면 현재 소스코드 있는 곳에 생성

# 2단계 : 파일 활용
num = 1
while True:
    line = rfp.readline()
    if line == "" or line is None:      # None == NULL
        break
    wfp.writelines(str(num) + "행 :" + line)
    num += 1

# 3단계 : 파일 닫기
rfp.close()
wfp.close()
