import Jetson.GPIO as GPIO
import time
import threading

usleep = lambda x: time.sleep(x/1000000.0)



class UltrasonicSensor:
    def __init__(self, trig, echo):
        GPIO.setwarnings(False)
        self.startTime = time.time()
        self.endTime = time.time()
        self.trig = trig
        self.echo = echo
        self.distance = 0
        self.filter_size = 9
        self.sens_list = []
        GPIO.setup(self.trig, GPIO.OUT)
        GPIO.output(self.trig, GPIO.LOW)
        GPIO.setup(self.echo, GPIO.IN, pull_up_down = GPIO.PUD_DOWN)
        GPIO.add_event_detect(self.echo, GPIO.RISING, callback=self.startTimer, bouncetime=0)
        # GPIO.add_event_detect(self.echo, GPIO.FALLING, callback=self.endTimer, bouncetime = 0)
        self.tr = threading.Thread(target=self.measure, args=())
        self.tr.setDaemon(True)
        self.tr.start()

    def startTimer(self, channel):
        self.startTime = time.time()
        while(GPIO.input(self.echo) == True):
            pass
        self.endTimer()

    def median_Filter(self, list):
        res = list[0:self.filter_size]
        res.sort()
        return res[int(self.filter_size/2)]

    def endTimer(self):
        self.endTime = time.time()
        self.calcDistance()

    def calcDistance(self):
        dist = (self.endTime-self.startTime)*17000
        dist = round(dist, 2)
        if(len(self.sens_list) == self.filter_size):
            del self.sens_list[0]
            self.sens_list.append(dist)
            self.distance = self.median_Filter(self.sens_list)
        else:
            self.sens_list.append(dist)

    def measure(self):
        # GPIO.remove_event_detect(self.echo)
        # threading.Timer(0.5, self.measure).start()
        # while True:
        #     GPIO.output(self.trig, GPIO.HIGH)
        #     time.sleep(1)
        #     GPIO.output(self.trig, GPIO.LOW)
        #     time.sleep(1)
        while True:
            start_time = time.time()
            GPIO.output(self.trig, GPIO.LOW)
            GPIO.output(self.trig, GPIO.HIGH)
            time.sleep(0.00001)
            # usleep(10) #sleep during 100μs
            GPIO.output(self.trig, GPIO.LOW)
            while(GPIO.input(self.echo) == 0):
                if(time.time() - start_time > 0.3):
                    break
                self.startTime = time.time()
            while(GPIO.input(self.echo) == 1):
                if(time.time() - start_time > 0.3):
                    break
                self.endTime = time.time()

            if(time.time() - start_time > 0.3):
                print("Timeout")
                pass
            else:
                self.calcDistance()
                slp_time = time.time() - start_time
                if(slp_time < 0.3):
                    time.sleep(0.3 - slp_time)
        # GPIO.add_event_detect(self.echo, GPIO.RISING, callback=self.startTimer, bouncetime=0)

    def read(self):
        return self.distance

if __name__ == "__main__":
    try:
        GPIO.setmode(1000)
        us = UltrasonicSensor(board.D10, board.D24)
        while(True):
            GPIO.output(us.trig, GPIO.HIGH)
            time.sleep(0.00001)
            GPIO.output(us.trig, GPIO.LOW)
            print(us.read())
            time.sleep(1.0)
    except Exception as e:
        print(e)
        GPIO.cleanup()
