import numpy as np
import random

class Grid3D:
    def __init__(self, size, obstacle_density=0.2):
        self.size = size
        self.grid = np.zeros((size, size, size), dtype=int)
        self.obstacles = set()
        self._generate_obstacles(obstacle_density)
    
    def _generate_obstacles(self, density):
        """Generate random obstacles in the grid"""
        total_cells = self.size ** 3
        num_obstacles = int(total_cells * density)
        
        for _ in range(num_obstacles):
            x = random.randint(0, self.size - 1)
            y = random.randint(0, self.size - 1)
            z = random.randint(0, self.size - 1)
            
            # Avoid placing obstacles at corners (common start/end points)
            if (x, y, z) not in [(0, 0, 0), (self.size-1, self.size-1, self.size-1)]:
                self.grid[x, y, z] = 1
                self.obstacles.add((x, y, z))
    
    def is_valid(self, pos):
        """Check if position is valid and not an obstacle"""
        x, y, z = pos
        return (0 <= x < self.size and 
                0 <= y < self.size and 
                0 <= z < self.size and 
                self.grid[x, y, z] == 0)
    
    def get_neighbors(self, pos):
        """Get valid neighboring positions (26-connectivity)"""
        x, y, z = pos
        neighbors = []
        
        for dx in [-1, 0, 1]:
            for dy in [-1, 0, 1]:
                for dz in [-1, 0, 1]:
                    if dx == dy == dz == 0:
                        continue
                    
                    new_pos = (x + dx, y + dy, z + dz)
                    if self.is_valid(new_pos):
                        neighbors.append(new_pos)
        
        return neighbors
    
    def get_obstacles(self):
        """Return list of obstacle positions"""
        return list(self.obstacles)
    
    def distance(self, pos1, pos2):
        """Calculate Euclidean distance between two positions"""
        return np.sqrt(sum((a - b) ** 2 for a, b in zip(pos1, pos2)))
    
    def manhattan_distance(self, pos1, pos2):
        """Calculate Manhattan distance between two positions"""
        return sum(abs(a - b) for a, b in zip(pos1, pos2))