import Jetson.GPIO as GPIO
import time as t

#GPIO.setmode(GPIO.BOARD)    # 물리적 핀번호
GPIO.setmode(GPIO.TEGRA_SOC)
GPIO.setwarnings(False)
#led_pin = 33

led_pin = "GPIO_PE6"

GPIO.setup(led_pin, GPIO.OUT)

my_pwm = GPIO.PWM(led_pin, 100)
my_pwm.start(0)

try:
    while True:
        for dc in range(0, 100, 5):
            my_pwm.ChangeDutyCycle(dc)  # 퍼센트
            t.sleep(0.1)
            
        for dc in range(100, 0, -5):
            my_pwm.ChangeDutyCycle(dc)
            t.sleep(0.1)

except KeyboardInterrupt:
    print('CTL stop')
    my_pwm.stop()
    GPIO.cleanup()
