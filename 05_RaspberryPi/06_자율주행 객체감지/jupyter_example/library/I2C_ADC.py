import time
import board
import busio

class I2C_ADC:
    def __init__(self, i2c_device, addr = 0x48):
        self.addr = addr
        self.i2c = i2c_device

    def read(self, adr, byteIndex=0):
        byte_adr = bytes([adr])
        self.i2c.writeto(self.addr, byte_adr)
        readbuf = [0]
        self.i2c.readfrom_into(self.addr, readbuf)
        result = int(readbuf[byteIndex])
        return result
