import pygame
from entity_effect import EntityEffect

class KeyboardMoveEffect(EntityEffect):
    def __init__(self, left_key=pygame.K_LEFT, right_key=pygame.K_RIGHT, delta=5.0):
        self.left_key = left_key
        self.right_key = right_key
        self.delta = delta
    
    def perform(self, entity):
        keys = pygame.key.get_pressed()
        if keys[self.left_key]:
            entity.x -= self.delta
        if keys[self.right_key]:
            entity.x += self.delta