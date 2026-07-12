from machine import Pin, Timer
import sys
import time

goPin = Pin(15, mode=Pin.IN, pull=Pin.PULL_DOWN)
pinCount = 0
pinTimerCount = 0
hardwareTimer = Timer()

def sendGoMessageFn():
    sys.stdout.write("True")
    hardwareTimer.deinit()
    led = Pin("LED", Pin.OUT)
    led.toggle()
    time.sleep_ms(20)
    led.toggle()

def checkGoSignal(timer):
    global pinTimerCount
    global pinCount
    pinTimerCount += 1
    if goPin.value() == 1:
        pinCount+=1
    if pinTimerCount >= 10:
        pinTimerCount = 0
        if pinCount >= 5:
            sendGoMessageFn()
        pinCount = 0

def sendGoMessageCallback(pin):
    global pinCount
    global hardwareTimer
    pinCount = 0
    hardwareTimer.init(mode=Timer.PERIODIC, period=1, callback=checkGoSignal)

goPin.irq(trigger=Pin.IRQ_RISING, handler=sendGoMessageCallback)
while True:
    pass # wait for interrupt
