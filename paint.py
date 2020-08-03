from kivy.app import App
from kivy.uix.widget import Widget
from kivy.uix.button import Button
from kivy.graphics import Color, Ellipse, Line
from random import random

class paintwidget(Widget):
 def on_touch_down(self,touch):
  with self.canvas:
   Color(random(),1,1,mode='hsv')
   d=30
   Ellipse(pos=(touch.x-d/2,touch.y-d/2),size=(d,d))
   touch.ud['line']=Line(points=(touch.x,touch.y))

 def on_touch_move(self,touch):
  touch.ud['line'].points += [touch.x,touch.y]

class paint(App):
 def build(self):
  par=Widget()
  self.paint=paintwidget()
  clear=Button(text='clear')
  clear.bind(on_release=self.clear_canvas)
  par.add_widget(self.paint)
  par.add_widget(clear)
  return par
 def clear_canvas(self,obj):
  self.paint.canvas.clear()

paint().run()
