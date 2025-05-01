# Day16-02.py
# 300, 200을 더하기/빼기/곱하기/나누기/나머지/몫/제곱 시키는 함수 만들고 출력

# 함수부
def calcValue(n1, n2):
    res1 = n1 + n2
    res2 = n1 - n2
    res3 = n1 ** n2
    return res1, res2, res3


# 전역 변수부
num1, num2, ret1, ret2, ret3 = [0] * 5

# 메인 코드부
num1 = int(input("숫자 1 입력 : "))
num2 = int(input("숫자 2 입력 : "))
ret1, ret2, ret3 = calcValue(num1, num2)

print(num1, '+', num2, '=', ret1)
print(num1, '-', num2, '=', ret2)
print(num1, '**', num2, '=', ret3)

'''
## 함수 선언부
def addNumber(n1, n2):
    result = 0
    result = n1 + n2
    return result


def subNumber(n1, n2):
    result = 0
    result = n1 - n2
    return result


def mulNumber(n1, n2):
    result = 0
    result = n1 * n2
    return result


def divNumber(n1, n2):
    result = 0
    result = n1 / n2
    return result


def namugiNumber(n1, n2):
    result = 0
    result = n1 % n2
    return result


def mokNumber(n1, n2):
    result = 0
    result = n1 // n2
    return result


def jegobNumber(n1, n2):
    result = 0
    result = n1 ^ n2
    return result


## 전역 변수부
num1 = 0
num2 = 0

hap = 0
sub = 0
mul = 0
div = 0
remainder = 0
quotient = 0
square = 0

## 메인 코드부
if __name__ == "__main__":
    num1 = 300
    num2 = 200
    hap = addNumber(num1, num2)
    sub = subNumber(num1, num2)
    mul = mulNumber(num1, num2)
    div = divNumber(num1, num2)
    remainder = namugiNumber(num1, num2)  # 나머지
    quotient = mokNumber(num1, num2)  # 몫
    square = jegobNumber(num1, num2)  # 제곱

    print(num1, '+', num2, '=', hap)
    print(num1, '-', num2, '=', sub)
    print(num1, '*', num2, '=', mul)
    print(num1, '/', num2, '=', div)
    print(num1, '%', num2, '=', remainder)
    print(num1, '//', num2, '=', quotient)
    print(num1, '^', num2, '=', square)
'''
