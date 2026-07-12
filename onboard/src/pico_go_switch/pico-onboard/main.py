from machine import Pin
import sys
import time

goPin = Pin(15, mode=Pin.IN, pull=Pin.PULL_UP)

def sendGoMessageFn():
    sys.stdout.write("True")
    led = Pin("LED", Pin.OUT)
    led.toggle()
    time.sleep_ms(20)
    led.toggle()

def sendGoMessageCallback(pin):
    sendGoMessageFn()

goPin.irq(trigger=Pin.IRQ_RISING, handler=sendGoMessageCallback)
while True:
    pass # wait for interrupt