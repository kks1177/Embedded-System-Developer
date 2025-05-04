import time
import board
import busio
from .LiquidCrystal_I2C import *

# LCD Address
ADDRESS = 0x27 # PCF8574T
#ADDRESS = 0x3F  # PCF8574AT

class I2C_Device:
    def __init__(self, addr, i2c_device):
        self.addr = addr
        self.i2c = i2c_device

    def write_cmd(self, cmd):
        self.i2c.writeto(self.addr, bytes([cmd]))
        time.sleep(0.0001)

class LCD:
    def __init__(self, i2c_device, addr=ADDRESS, rows = 16, cols = 2):
        self.i2c = I2C_Device(addr, i2c_device)
        self.addr = addr
        self.rows = rows
        self.cols = cols
        self.backlight_state = 1
        self.write(0x03)
        self.write(0x03)
        self.write(0x03)
        self.write(0x02)

        self.write(LCD_FUNCTIONSET | LCD_2LINE | LCD_5x8DOTS | LCD_4BITMODE)
        self.write(LCD_DISPLAYCONTROL | LCD_DISPLAYON)
        self.write(LCD_CLEARDISPLAY)
        self.write(LCD_ENTRYMODESET | LCD_ENTRYLEFT)

        time.sleep(0.2)

    def strobe(self, data):
        if(self.backlight_state == 1):
            self.i2c.write_cmd(data | En | LCD_BACKLIGHT)
        else:
            self.i2c.write_cmd(data | En | LCD_NOBACKLIGHT)
        time.sleep(0.0005)
        if(self.backlight_state == 1):
            self.i2c.write_cmd(((data & ~En) | LCD_BACKLIGHT))
        else:
            self.i2c.write_cmd(((data & ~En) | LCD_NOBACKLIGHT))
        time.sleep(0.0001)

    def write_four_bits(self, data):
        if(self.backlight_state == 1):
            self.i2c.write_cmd(data | LCD_BACKLIGHT)
        else:
            self.i2c.write_cmd(data | LCD_NOBACKLIGHT)

        self.strobe(data)

    def write(self, cmd, mode = 0):
        self.write_four_bits(mode | (cmd & 0xF0))
        self.write_four_bits(mode | ((cmd << 4) & 0xF0))

    def write_char(self, charvalue, mode = 1):
        self.write_four_bits(mode | (charvalue & 0xF0))
        self.write_four_bits(mode | ((charvalue << 4)&0xF0))

    def setCursor(self, line, pos):
        if line == 0:
            pos_new = pos
        elif line == 1:
            pos_new = 0x40 + pos
        elif line == 2:
            pos_new = 0x14 + pos
        elif line == 3:
            pos_new = 0x54 + pos

        self.write(0x80 + pos_new)

    def display_string(self, string):

        for char in string:
            self.write(ord(char), Rs)

    def clear(self):
        self.write(LCD_CLEARDISPLAY)
        self.write(LCD_RETURNHOME)

    def backlight(self, state): # for state, 1 = on, 0 = off
        self.backlight_state = state
        if state == 1:
            self.i2c.write_cmd(LCD_BACKLIGHT)
        elif state == 0:
            self.i2c.write_cmd(LCD_NOBACKLIGHT)
