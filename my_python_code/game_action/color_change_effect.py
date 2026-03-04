import pygame
import random
from entity_effect import EntityEffect

class ColorChangeEffect(EntityEffect):
    def __init__(self, change_interval=60):
        self.change_interval = change_interval
        self.counter = 0
    
    def perform(self, entity):
        self.counter += 1
        if self.counter >= self.change_interval:
            entity.color = (random.randint(100, 255), random.randint(100, 255), random.randint(100, 255))
            self.counter = 0