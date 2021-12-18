import pynput.mouse
import pynput.keyboard
from os import system
from time import sleep
m=pynput.mouse.Controller()
k=pynput.keyboard.Controller()

k.press(pynput.keyboard.Key.cmd)
k.press(pynput.keyboard.Key.ctrl)
k.press('e')
k.release(pynput.keyboard.Key.cmd)
k.release(pynput.keyboard.Key.ctrl)
sleep(0.2)
system('osascript -e \'tell application "System Events" to tell process "Пункт управления" to tell menu bar item "пункт управления" of menu bar 1 to click\'')