import pygame
import sys
from game_entity import GameEntity
from keyboard_move_effect import KeyboardMoveEffect
from wind_effect import WindEffect

def main():
    pygame.init()
    screen = pygame.display.set_mode((800, 600))
    pygame.display.set_caption("Game Actions Demo")
    clock = pygame.time.Clock()
    
    player = GameEntity(400, 300)
    
    effects = [
        KeyboardMoveEffect(),
        WindEffect()
    ]
    
    running = True
    while running:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False
        
        for effect in effects:
            effect.perform(player)
        
        screen.fill((0, 0, 0))
        player.draw(screen)
        pygame.display.flip()
        clock.tick(60)
    
    pygame.quit()
    sys.exit()

if __name__ == "__main__":
    main()