from .I2C_ADC import I2C_ADC
import time

class I2C_Battery(I2C_ADC):
    def __init__(self, i2c_device, i2c_addr = 0x48, battery_adr = 0x40, minimum_Battery=177, maximum_Battery=249, array_length = 50):
        super(I2C_Battery, self).__init__(i2c_device, i2c_addr)
        self.battery_Check_adr = battery_adr
        self.minimum_Battery = minimum_Battery
        self.maximum_Battery = maximum_Battery
        self.max_Array_Length = array_length
        self.battery_list = []
        self.current_Battery = 100
        self.current_raw_Battery = maximum_Battery
        self.__initialize_start_time__ = time.time()
        self.__initialize_wait_time__ = 30 # Seconds
        self.__initialize_done__ = False

    def read_raw(self):
        # byte_adr = bytes([self.battery_Check_adr])
        # self.i2c.writeto(self.addr, byte_adr)
        # readbuf = [0]
        # self.i2c.readfrom_into(self.addr, readbuf)
        # return int(raw_Value)
        return self.current_raw_Battery
        # return len(self.battery_list)
    def get_Battery(self):
        garbageData = self.read(self.battery_Check_adr)
        raw_Value = self.read(self.battery_Check_adr)

        # print("Len : " + str(len(self.battery_list)))
        if(self.__initialize_done__):
            if(len(self.battery_list) == self.max_Array_Length):
                if(abs(self.current_raw_Battery - int(raw_Value)) < ((self.maximum_Battery - self.minimum_Battery)/10)):
                    del self.battery_list[0]
                    self.battery_list.append(int(raw_Value))
                self.current_raw_Battery = round(max(min(sum(self.battery_list)/len(self.battery_list), self.current_raw_Battery), 0))
            else:
                self.battery_list.append(int(raw_Value))
                self.current_raw_Battery = max(self.battery_list)
        else:
            if((time.time() - self.__initialize_start_time__) < self.__initialize_wait_time__):
                if(int(raw_Value) > self.minimum_Battery):
                    self.__initialize_done__ = True
            else:
                self.__initialize_done__ = True
            return -99

        temp = self.byte2Battery(self.current_raw_Battery)

        self.current_Battery = min(temp, self.current_Battery)

        return self.current_Battery

    def byte2Battery(self, data):
        if(data < self.minimum_Battery):
            data = self.minimum_Battery
        if(data > self.maximum_Battery):
            data = self.maximum_Battery
        return round(float(100/(self.maximum_Battery - self.minimum_Battery)) * (data - self.minimum_Battery))
