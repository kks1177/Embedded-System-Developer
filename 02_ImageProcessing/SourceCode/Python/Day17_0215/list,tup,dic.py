Python 3.10.2 (tags/v3.10.2:a58ebcc, Jan 17 2022, 14:12:15) [MSC v.1929 64 bit (AMD64)] on win32
Type "help", "copyright", "credits" or "license()" for more information.
ary = [10, 20, 30]
ary = [10, 3.14, "안녕"]
ary.append(True)
ary
[10, 3.14, '안녕', True]

tup = (10, 20, 30)
tup
(10, 20, 30)

tup[0]
10
tup[1] + tup[2]
50

tup.append(40)
Traceback (most recent call last):
  File "<pyshell#11>", line 1, in <module>
    tup.append(40)
AttributeError: 'tuple' object has no attribute 'append'

dic = {1:'하나', 2:'둘', 3:'셋'}
dic[1]
'하나'
dic[3]
'셋'
dic[0]
Traceback (most recent call last):
  File "<pyshell#16>", line 1, in <module>
    dic[0]
KeyError: 0

dic = {'기차':'빨라', '바나나':'맛있어', '비행기':'높아'}
dic['기차']
'빨라'
dic['비행기']
'높아'
 dic['자동차']
 
SyntaxError: unexpected indent
