import pygame
from abc import ABC, abstractmethod


class GameEntity:
    def __init__(self, x=100, y=100, size=20, color=(0, 255, 0)):
        """Initialize game entity with position, size, and color."""
        self.x = x
        self.y = y
        self.size = size
        self.color = color
        self.effects = []  # optional extension: store effects inside the entity

    def draw(self, screen):
        """Draw the entity as a circle on the screen."""
        pygame.draw.circle(screen, self.color, (int(self.x), int(self.y)), self.size)

    def update(self):
        """Perform all effects attached to this entity."""
        for effect in self.effects:
            effect.perform(self)



class EntityEffect(ABC):
    @abstractmethod
    def perform(self, entity: GameEntity):
        """Apply effect to the given entity."""
        pass



class KeyboardMoveEffect(EntityEffect):
    def __init__(self, left_key, right_key, up_key, down_key, delta=5):
        """Initialize keyboard movement effect with key bindings and movement speed."""
        self.left_key = left_key
        self.right_key = right_key
        self.up_key = up_key
        self.down_key = down_key
        self.delta = delta

    def perform(self, entity: GameEntity):
        """Move entity based on pressed keys."""
        keys = pygame.key.get_pressed()
        if keys[self.left_key]:
            entity.x -= self.delta
        if keys[self.right_key]:
            entity.x += self.delta
        if keys[self.up_key]:
            entity.y -= self.delta
        if keys[self.down_key]:
            entity.y += self.delta



class WindEffect(EntityEffect):
    def __init__(self, dx=1, dy=0):
        """Initialize wind effect with horizontal and vertical drift values."""
        self.dx = dx
        self.dy = dy

    def perform(self, entity: GameEntity):
        """Apply constant wind drift to entity position."""
        entity.x += self.dx
        entity.y += self.dy



class MouseClickMoveEffect(EntityEffect):
    def perform(self, entity: GameEntity):
        """Move entity to mouse position when left button is clicked."""
        if pygame.mouse.get_pressed()[0]:  # left click
            mouse_x, mouse_y = pygame.mouse.get_pos()
            entity.x, entity.y = mouse_x, mouse_y



def main():
    """Main game loop that initializes pygame and runs the game."""
    pygame.init()
    screen = pygame.display.set_mode((800, 600))
    pygame.display.set_caption("Game Entity Effects Example")

    clock = pygame.time.Clock()
    running = True

    # Create player in the center
    player = GameEntity(400, 300)

    # Create effects
    move_effect = KeyboardMoveEffect(
        pygame.K_a, pygame.K_d, pygame.K_w, pygame.K_s, delta=5
    )
    wind_effect = WindEffect(dx=0.2, dy=0)  # gentle push to the right
    mouse_effect = MouseClickMoveEffect()

    # Attach effects to player
    player.effects.append(move_effect)
    player.effects.append(wind_effect)
    player.effects.append(mouse_effect)

    # Game Loop
    while running:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False

        # Update player (apply effects)
        player.update()

        # Draw
        screen.fill((0, 0, 0))
        player.draw(screen)
        pygame.display.flip()

        clock.tick(60)

    pygame.quit()


if __name__ == "__main__":
    main()
