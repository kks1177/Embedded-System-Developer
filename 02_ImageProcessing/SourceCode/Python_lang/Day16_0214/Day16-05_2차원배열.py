# Day16-05_2차원 배열.py

# 함수부


# 전역변수
image = [ [0, 0, 0, 0],
          [0, 0, 0, 0],
          [0, 0, 0, 0]]

# 메인함수부
image[0][0] = 3
image[2][3] = 9
for i in range(3):
    for k in range(4):
        image[i][k] += 1

for i in range(3):
    for k in range(4):
        print("%03d" % image[i][k], end=' ')
    print()

