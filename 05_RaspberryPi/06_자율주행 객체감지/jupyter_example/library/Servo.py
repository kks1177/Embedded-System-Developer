from .PCA9685_Module import *

class Servo(PCA9685_MODULE):
    def __init__(self, index):
        self.index = index
        self.module = super().PCA9685_Module.channels[index]
        self.min_pulse = 1297 # 상수값.  변경 금지
        self.max_pulse = 8247 # 상수값.  변경 금지
        self.Frequency_Rate = super().PCA9685_Module.frequency / 50
        self.range_pulse = self.max_pulse - self.min_pulse
        self.module.duty_cycle = round(int((self.min_pulse+self.max_pulse)/2) * self.Frequency_Rate)

    def update_Frequency_Rate(self):
        self.Frequency_Rate = super().PCA9685_Module.frequency / 50

    def write(self, degree):
        self.update_Frequency_Rate()
        self.module.duty_cycle = round((self.min_pulse + int((self.range_pulse/180) * max(min(180, degree), 0)))*self.Frequency_Rate)

    def __del__(self):
        self.update_Frequency_Rate()
        self.module.duty_cycle = round((int((self.min_pulse+self.max_pulse)/2))*self.Frequency_Rate)
