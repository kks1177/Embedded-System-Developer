import Jetson.GPIO as GPIO

class Switch:
    def __init__(self, pin):
        self.s_pin = pin
        GPIO.setup(self.s_pin, GPIO.IN)

    def read(self):
        return GPIO.input(self.s_pin)

    def addEvent(self, func, edge):
        GPIO.add_event_detect(self.s_pin, edge, callback = func, bouncetime = 10)
