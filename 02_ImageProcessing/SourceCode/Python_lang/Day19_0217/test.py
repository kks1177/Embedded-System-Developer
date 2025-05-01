import cv2

inPhoto = cv2.imread("c:/images/opencv/crow.jpg")
outPhoto = cv2.cvtColor(inPhoto, cv2.COLOR_BGR2HSV)

cv2.imshow("inphoto", inPhoto)
cv2.imshow("outphoto", outPhoto)
cv2.watiKey(0)
cv2.destoryAllWindows()     # 메모리 해제
