import pygame

class GameEntity:
    def __init__(self, x=400, y=300):
        self.x = x
        self.y = y
    
    def draw(self, screen):
        pygame.draw.circle(screen, (255, 255, 255), (int(self.x), int(self.y)), 20)