from .PCA9685_Module import *
import Jetson.GPIO as GPIO

STOP = 0
CW = 1
CCW = 2

class Motor(PWM):
    def __init__(self, index, pinA, pinB, *, reverse=False, ratio = 1.0):
        self.reverse = reverse
        self.index = index
        self.Ratio = ratio
        super(Motor,self).__init__(self.index)
        self.module.duty_cycle = 0

        self.pinA = pinA
        self.pinB = pinB

        GPIO.setup(self.pinA, GPIO.OUT)
        GPIO.setup(self.pinB, GPIO.OUT)

        self.setDirection(STOP)
        self.curr_Value = 0

    def setDirection(self, dir):
        if(dir == STOP):
            GPIO.output(self.pinA, GPIO.LOW)
            GPIO.output(self.pinB, GPIO.LOW)
        elif(self.reverse == False):
            if(dir == CW):
                GPIO.output(self.pinA, GPIO.HIGH)
                GPIO.output(self.pinB, GPIO.LOW)
            elif(dir == CCW):
                GPIO.output(self.pinA, GPIO.LOW)
                GPIO.output(self.pinB, GPIO.HIGH)
        elif(self.reverse == True):
            if(dir == CCW):
                GPIO.output(self.pinA, GPIO.HIGH)
                GPIO.output(self.pinB, GPIO.LOW)
            elif(dir == CW):
                GPIO.output(self.pinA, GPIO.LOW)
                GPIO.output(self.pinB, GPIO.HIGH)
    def read(self):
        return self.curr_Value

    def read_per(self):
        return (100/256) * self.curr_Value

    def write(self, pwm):
        self.curr_Value = pwm
        if(pwm < 0):
            pwm = abs(pwm)
            self.setDirection(CCW)
        else:
            self.setDirection(CW)
        self.module.duty_cycle = int(int((0x7FFF/self.MaxPWM) * max(min(self.MaxPWM, pwm), 0)) * self.Ratio)
