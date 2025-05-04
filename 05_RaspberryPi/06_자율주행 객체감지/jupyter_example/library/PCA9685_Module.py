from adafruit_pca9685 import PCA9685
import Jetson.GPIO as GPIO
import board
import busio

class PCA9685_MODULE:
    print("Create PWM Module...\nit may be takes few seconds...")
    GPIO.setmode(1000)
    GPIO.setup(board.D22.id, GPIO.OUT)
    GPIO.output(board.D22.id, GPIO.LOW)
    i2c_device = busio.I2C(board.SCL_1.id, board.SDA_1.id)
    PCA9685_Module = PCA9685(i2c_device)
    # PCA9685_Module.frequency = 50
    PCA9685_Module.frequency = 200
    print("Create Done!")

class PWM(PCA9685_MODULE):
    def __init__(self, index):
        self.index = index
        self.module = super().PCA9685_Module.channels[self.index]
        self.module.duty_cycle = 0
        self.MaxPWM = 255

    def set_pwm_max(self, max_pwm):
        self.MaxPWM = max_pwm

    def digitalWrite(self, state):
        self.module.duty_cycle = 0xFFFF * state

    def write(self, pwm):
        self.module.duty_cycle = int((0xFFFF/self.MaxPWM) * max(min(self.MaxPWM, pwm), 0))

    def __del__(self):
        self.module.duty_cycle = 0
