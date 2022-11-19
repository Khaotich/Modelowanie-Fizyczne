import thorpy
from Disk import Disk
from Point import Point
from CONSTS import *


def main():
    pygame.init()
    screen = pygame.display.set_mode([WIDTH, HEIGHT])
    clock = pygame.time.Clock()
    pygame.display.set_caption('Euler\'s disks')
    pygame.display.flip()

    slider1 = thorpy.SliderX(100, (1, 1000), "ELEMENTS", type_=int, initial_value=100)
    slider1.set_font_color(WHITE)
    slider2 = thorpy.SliderX(120, (1, 10), "SIZE", type_=int)
    slider2.set_font_color(WHITE)

    box = thorpy.Box(elements=[slider1, slider2])
    menu = thorpy.Menu(box)

    circles_list = [Disk(slider2.get_value()) for _ in range(1000)]
    points_list = []
    points_pos_list = []
    running = True
    coloring = False
    current_mode = 'gravity'
    color = PINK
    fps = 30

    while running:
        dt = clock.tick(fps) * .001 * fps
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False

            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_1:
                    color = PINK
                    fps = 30
                    current_mode = 'gravity'

                if event.key == pygame.K_2:
                    color = LIME
                    fps = 60
                    current_mode = 'attract'

                if event.key == pygame.K_3:
                    color = BLUE
                    fps = 30
                    current_mode = 'point'

                if event.key == pygame.K_SPACE:
                    circles_list.clear()
                    circles_list = [Disk(slider2.get_value()) for _ in range(0, 1000)]

                if event.key == pygame.K_r:
                    if not coloring:
                        coloring = True
                    else:
                        coloring = False

            if event.type == pygame.MOUSEBUTTONDOWN:
                if event.button == 1 and current_mode == 'point':
                    mouse_pos = pygame.math.Vector2(pygame.mouse.get_pos())
                    points_pos_list.append(mouse_pos)
                    point = Point()
                    points_list.append(point)

            menu.react(event)

        screen.blit(BACKGROUND, (0, 0))
        for i in range(len(points_list)):
            points_list[i].draw(screen, points_pos_list[i])

        for i in range(slider1.get_value()):
            if coloring:
                circles_list[i].draw(screen, circles_list[i].random_color, slider2.get_value())
            else:
                circles_list[i].draw(screen, color, slider2.get_value())

            if len(points_list) > 0:
                circles_list[i].update(current_mode, dt, slider2.get_value())
            else:
                circles_list[i].update(current_mode, dt, slider2.get_value())

        box.blit()
        box.update()
        pygame.display.update()


if __name__ == '__main__':
    main()
