import sys, os, importlib

sys.path.append('/Users/gera/Library/Python/3.9/lib/python/site-packages/')
mname = os.path.splitext('pynput')[0]
pynput = importlib.import_module(mname)                       
sys.path.pop()

a=pynput.keyboard.Controller()
a.press(pynput.keyboard.Key.alt)