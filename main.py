from h import *
from Window import Window
from _Snake import Snake
from Food import Food
import pygame

def game_loop(w: Window, f: Food, s: Snake):
    clock = pygame.time.Clock()#
    while True:
        clock.tick(s.speed)  #
        w.fill()
        f.draw(w)
        s.draw(w)
        s.move()
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_LEFT:
                    s.change_direction('left')
                elif event.key == pygame.K_RIGHT:
                    s.change_direction('right')
                elif event.key == pygame.K_UP:
                    s.change_direction('up')
                elif event.key == pygame.K_DOWN:
                    s.change_direction('down')
        if s.check_callaps(w):
            pygame.quit() #
            exit()
        s.check_eat(f, w)
        w.update_window()


def main():
    pygame.init()
    w = Window()
    s = Snake(w)
    f = Food(w,s)
    game_loop(w, f, s)


if __name__ == '__main__':
    main()
