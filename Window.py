import pygame


blue = (50, 153, 213)

 
class Window:
    def __init__(self, size_x=600, size_y=600):
        self.size_x = size_x
        self.size_y = size_y
        self.dis = pygame.display.set_mode((self.size_x, self.size_y))
        pygame.display.set_caption('Snake Game by DiGarOn')

    def update_window(self):
        pygame.display.update()

    def fill(self):
        self.dis.fill(blue)
