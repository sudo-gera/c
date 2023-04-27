from __future__ import annotations
import random
import pygame
from Window import Window
import _Snake

green = (0, 255, 0)


class Food:
    def __init__(self, w: Window, s: Snake.Snake):
        self.foodx = round(random.randrange(0, w.size_x - s.block_size) / 10.0) * 10.0
        self.foody = round(random.randrange(0, w.size_y - s.block_size) / 10.0) * 10.0
        self.size = s.block_size

    def draw(self, w: Window):
        pygame.draw.rect(w.dis, green, [self.foodx, self.foody, self.size, self.size])

    def update(self, w: Window):
        self.foodx = round(random.randrange(0, w.size_x - self.size) / 10.0) * 10.0
        self.foody = round(random.randrange(0, w.size_y - self.size) / 10.0) * 10.0
        # self.draw(w)
