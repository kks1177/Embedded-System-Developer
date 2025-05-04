from .I2C_ADC import I2C_ADC
import time

class I2C_PSD(I2C_ADC):
    def __init__(self, i2c_device, i2c_addr = 0x48, psd_adr = 0x41, minimum_value=0, maximum_value=250, minimum_len = 0, maximum_len = 100):
        super(I2C_PSD, self).__init__(i2c_device, i2c_addr)
        self.psd_Sensor_adr = psd_adr
        self.raw_Value = 0
        self.length_Value = 0
        self.minimum_Value = minimum_value
        self.maximum_Value = maximum_value
        self.minimum_Length = minimum_len
        self.maximum_Length = maximum_len
        self.PSD_Threshold = 100

    def set_Threshold(self, thres):
        self.PSD_Threshold = thres

    def measure(self):
        # threading.Timer(1, self.measure).start()
        # read once -> the First Response is not Available
        garbageData = self.read(self.psd_Sensor_adr)

        self.raw_Value = self.read(self.psd_Sensor_adr)

    def read_raw(self):
        # byte_adr = bytes([self.psd_Sensor_adr])
        # self.i2c.writeto(self.addr, byte_adr)
        # readbuf = [-99]
        # self.i2c.readfrom_into(self.addr, readbuf)

        # return int(readbuf[0])
        return self.raw_Value

    def read_Detect(self):

        if(self.raw_Value > self.PSD_Threshold):
            return True
        return False

    def byte2Length(self, data):
        if(data < self.minimum_Value):
            data = self.minimum_Value
        if(data > self.maximum_Value):
            data = self.maximum_Value

        return self.minimum_Length + round(float((self.maximum_Length - self.minimum_Length)/(self.maximum_Value - self.minimum_Value)) * (self.maximum_Value - data))
