# Day16-01.기본문법.py

## 함수 선언부
def addNumber(n1, n2):      # 파라미터는 변수명과 다르게
    # pass                  # 함수를 바로 사용하지 않고 정의만 해놓을 경우 pass를 넣으면 함수가 실행 되지 않음
    retVal = 0
    retVal = n1 + n2
    return retVal

## 전역 변수부
num1 = 0
num2 = 0
hap = 0

## 메인 코드부
if __name__ == "__main__":
    num1 = 100
    num2 = 200
    hap = addNumber(num1, num2)         # 함수 호출
    print(num1, '+', num2, '=', hap)
