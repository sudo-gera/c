q='''
Непобедимый, негодующе, недоумевающе, неизбежно, небрежно, нелепо, неожиданно, невесть,
неведомо, невиданно, непременно, недосуг, неохота, нехотя, незачем, невдалеке,
неподалеку, невмоготу, невмочь, невдомек,
невзначай, невпопад, невпроворот, невтерпеж,
недаром, ненароком, небезнадежный, неблагоразумие, неверие, нежели, незадолго, некстати, нелюбый, немало, немного, ненамного, нечисто, неслыханно, неспроста,
не вполне, не иначе, не после, не время, не
жаль, не надо, не надобно, не пора, не против, не
полностью, не сразу, не скоро, не совсем, не
нарочно, не видно, не очень, не без причины, не
всерьез, не в счет, не готов, не должен, не жалко,
не любо, не худо, не страшно, не слишком, не
случайно, не согласен, не спеша
'''.replace('\n',' ').split(',')
from random import choice
s=0
while 1:
 d=choice(q)
 print(''.join(d.split()))
 e=-1
 r='не ' in d
 while e != int(r):
  e=int(bool(int(input())))