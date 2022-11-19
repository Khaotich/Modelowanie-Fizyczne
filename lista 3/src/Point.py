import pygame
from CONSTS import WHITE


class Point:
    def __init__(self):
        self.position = pygame.math.Vector2(0, 0)
        self.size = 20
        self.color = WHITE

    def draw(self, display, position):
        pygame.draw.circle(display, self.color, position, self.size)
