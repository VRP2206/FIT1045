import numpy as np
import random

class Grid2D:
    def __init__(self, size, obstacle_density=0.2):
        self.size = size
        self.obstacles = set()
        self._generate_obstacles(obstacle_density)
    
    def _generate_obstacles(self, density):
        total_cells = self.size ** 2
        num_obstacles = int(total_cells * density)
        
        for _ in range(num_obstacles):
            x = random.randint(0, self.size - 1)
            y = random.randint(0, self.size - 1)
            if (x, y) not in [(0, 0), (self.size-1, self.size-1)]:
                self.obstacles.add((x, y))
    
    @classmethod
    def create_blank(cls, size):
        grid = cls.__new__(cls)
        grid.size = size
        grid.obstacles = set()
        return grid
    
    def add_obstacle(self, pos):
        x, y = pos
        if 0 <= x < self.size and 0 <= y < self.size and pos not in [(0, 0), (self.size-1, self.size-1)]:
            self.obstacles.add(pos)
    
    def is_valid(self, pos):
        x, y = pos
        return 0 <= x < self.size and 0 <= y < self.size and pos not in self.obstacles
    
    def get_neighbors(self, pos):
        x, y = pos
        neighbors = []
        for dx, dy in [(-1,0), (1,0), (0,-1), (0,1), (-1,-1), (-1,1), (1,-1), (1,1)]:
            new_pos = (x + dx, y + dy)
            if self.is_valid(new_pos):
                neighbors.append(new_pos)
        return neighbors
    
    def distance(self, pos1, pos2):
        return np.sqrt(sum((a - b) ** 2 for a, b in zip(pos1, pos2)))