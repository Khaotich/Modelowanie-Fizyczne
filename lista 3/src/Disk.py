import pygame
import random
import math
from CONSTS import WIDTH, HEIGHT, CENTER, GRAVITY


class Disk:
    def __init__(self, size):
        self.grav = 0
        self.r = 0
        self.f_vec = pygame.math.Vector2(0, 0)
        self.f = 0

        # random position
        self.position = pygame.math.Vector2(random.randint(0 + size, WIDTH - size),
                                            random.randint(0 + size, HEIGHT - size))

        # random velocity ( x-axis and y-axis )
        self.velocity = pygame.math.Vector2(random.randint(-50, 50) / 5, random.randint(-50, 50) / 5)

        # random drag
        self.drag = random.randint(970, 990) / 1000

        # force vector
        self.force = pygame.math.Vector2(0, 0)

        # randomize
        self.random_color = [random.randint(0, 255), random.randint(0, 255), random.randint(0, 255)]

        # init acceleration
        self.acceleration = pygame.math.Vector2(0, 0)

        # random mass
        self.mass = random.randint(20, 200)

    def update(self, mode, delta_time, size):
        if mode == 'gravity':
            # y = y + v * dt
            self.position.y += self.velocity.y * delta_time + 1/2 * GRAVITY * delta_time**2
            self.position.x += self.velocity.x

            # v(y) = v(y) + g * dt
            self.velocity.y += 0.9 * delta_time

        elif mode == 'attract':
            # vector of mouse position
            # mouse_pos = pygame.math.Vector2(pygame.mouse.get_pos())
            # r^2 = (x_2-x1)^2 + (y_2 - y1)^2
            # r = (mouse_pos.x - self.position.x)**2 + (mouse_pos.y - self.position.y)**2
            # F = G * m * M / r^2
            # self.grav = 6.67 * 10e-11 * self.mass * other_mass / r
            # result vector of gravity force
            self.force = pygame.math.Vector2(pygame.mouse.get_pos()) - self.position
            self.force = self.force.normalize()

            # apply drag
            self.velocity *= self.drag

            # apply force
            self.velocity += self.force * 0.6

            # update position
            self.position += self.velocity

        elif mode == 'point':
            # wektor w ktora strone ma byc sila
            self.force = CENTER - self.position
            # normalizacja czyli wersor
            self.force = self.force.normalize()

            # mianownik
            # r = sqrt((x1-x2)^2 + (y1-y2)^2)
            self.r = math.sqrt(pow(CENTER.x - self.position.x, 2) + pow(CENTER.y - self.position.y, 2))
            # sila grawitacji F = G * M * m / r ^ 2
            self.f = (self.mass * 1000) / (pow(self.r + size, 2))

            # nadanie wersorowi wartości siły F
            self.f_vec = self.f * self.force

            # przyspieszenie a = F / m
            self.acceleration += self.f_vec / self.mass

            if self.acceleration.x > 2 or self.acceleration.y > 2 or \
               self.acceleration.x < -2 or self.acceleration.y < -2:
                self.acceleration.x = 0
                self.acceleration.y = 0

            if self.r > 300:
                self.r = -self.r

            # -a - sila oporu
            self.acceleration += -6 * math.pi * self.velocity * 0.00001 * size

            if self.velocity.x > 10 or self.velocity.x < -10:
                self.velocity.x = 0
            elif self.velocity.y > 10 or self.velocity.y < -10:
                self.velocity.y = 0

        self.velocity += self.acceleration * delta_time
        self.position += self.velocity * delta_time

        # screen borders
        if self.position.x >= WIDTH - size:
            self.position.x = WIDTH - size
            self.velocity.x *= -1.0
        elif self.position.x <= 0 + size:
            self.position.x = 0 + size
            self.velocity.x *= -1.0

        if self.position.y >= HEIGHT - size:
            self.position.y = HEIGHT - size
            self.velocity.y *= -1.0
        elif self.position.y <= 0 + size:
            self.position.y = 0 + size
            self.velocity.y *= -1.0

    def draw(self, display, color, size):
        pygame.draw.circle(display, color, self.position, size)
