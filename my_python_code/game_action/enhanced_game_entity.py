import pygame

class EnhancedGameEntity:
    def __init__(self, x=400, y=300, size=20, color=(255, 255, 255)):
        self.x = x
        self.y = y
        self.size = size
        self.color = color
        self.effects = []
    
    def add_effect(self, effect):
        self.effects.append(effect)
    
    def update(self):
        for effect in self.effects:
            effect.perform(self)
    
    def draw(self, screen):
        pygame.draw.circle(screen, self.color, (int(self.x), int(self.y)), self.size)