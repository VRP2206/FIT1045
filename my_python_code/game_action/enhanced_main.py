import pygame
import sys
from enhanced_game_entity import EnhancedGameEntity
from keyboard_move_effect import KeyboardMoveEffect
from wind_effect import WindEffect
from color_change_effect import ColorChangeEffect

def main():
    pygame.init()
    screen = pygame.display.set_mode((800, 600))
    pygame.display.set_caption("Enhanced Game Actions Demo")
    clock = pygame.time.Clock()
    
    player = EnhancedGameEntity(400, 300)
    player.add_effect(KeyboardMoveEffect())
    player.add_effect(WindEffect(0.3, 0.1))
    player.add_effect(ColorChangeEffect())
    
    running = True
    while running:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False
        
        player.update()
        
        screen.fill((0, 0, 0))
        player.draw(screen)
        pygame.display.flip()
        clock.tick(60)
    
    pygame.quit()
    sys.exit()

if __name__ == "__main__":
    main()