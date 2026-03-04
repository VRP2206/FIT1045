import numpy as np
import random
try:
    import matplotlib.pyplot as plt
    import matplotlib.patches as patches
    HAS_MATPLOTLIB = True
except ImportError:
    HAS_MATPLOTLIB = False

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
    
    def interactive_editor(self):
        if HAS_MATPLOTLIB:
            self._matplotlib_editor()
        else:
            self._text_editor()
    
    def _matplotlib_editor(self):
        fig, ax = plt.subplots(figsize=(8, 8))
        ax.set_xlim(-0.5, self.size-0.5)
        ax.set_ylim(-0.5, self.size-0.5)
        ax.set_aspect('equal')
        ax.invert_yaxis()
        
        for i in range(self.size + 1):
            ax.axhline(i - 0.5, color='gray', linewidth=0.5)
            ax.axvline(i - 0.5, color='gray', linewidth=0.5)
        
        ax.add_patch(patches.Rectangle((0-0.4, 0-0.4), 0.8, 0.8, facecolor='green', alpha=0.7))
        ax.add_patch(patches.Rectangle((self.size-1-0.4, self.size-1-0.4), 0.8, 0.8, facecolor='red', alpha=0.7))
        
        obstacle_patches = {}
        
        def on_click(event):
            if event.inaxes != ax:
                return
            x, y = int(round(event.xdata)), int(round(event.ydata))
            pos = (x, y)
            
            if pos in [(0, 0), (self.size-1, self.size-1)]:
                return
            
            if pos in self.obstacles:
                self.obstacles.remove(pos)
                obstacle_patches[pos].remove()
                del obstacle_patches[pos]
            else:
                self.obstacles.add(pos)
                patch = patches.Rectangle((x-0.4, y-0.4), 0.8, 0.8, facecolor='black')
                ax.add_patch(patch)
                obstacle_patches[pos] = patch
            
            plt.draw()
        
        fig.canvas.mpl_connect('button_press_event', on_click)
        plt.title('Click to add/remove obstacles. Close window when done.')
        plt.show()
    
    def _text_editor(self):
        print(f"Text-based obstacle editor for {self.size}x{self.size} grid")
        print("Enter coordinates as 'x,y' to toggle obstacles. Type 'done' to finish.")
        print(f"Start: (0,0), Goal: ({self.size-1},{self.size-1})")
        
        while True:
            self._display_grid()
            user_input = input("Enter coordinates (x,y) or 'done': ").strip()
            
            if user_input.lower() == 'done':
                break
            
            try:
                x, y = map(int, user_input.split(','))
                pos = (x, y)
                
                if pos in [(0, 0), (self.size-1, self.size-1)]:
                    print("Cannot place obstacle on start or goal position.")
                    continue
                
                if 0 <= x < self.size and 0 <= y < self.size:
                    if pos in self.obstacles:
                        self.obstacles.remove(pos)
                        print(f"Removed obstacle at {pos}")
                    else:
                        self.obstacles.add(pos)
                        print(f"Added obstacle at {pos}")
                else:
                    print("Coordinates out of bounds.")
            except ValueError:
                print("Invalid input. Use format 'x,y' or 'done'.")
    
    def _display_grid(self):
        print("\nCurrent grid (S=Start, G=Goal, #=Obstacle, .=Empty):")
        for y in range(self.size):
            row = ""
            for x in range(self.size):
                if (x, y) == (0, 0):
                    row += "S "
                elif (x, y) == (self.size-1, self.size-1):
                    row += "G "
                elif (x, y) in self.obstacles:
                    row += "# "
                else:
                    row += ". "
            print(row)
        print()
    
    def distance(self, pos1, pos2):
        return np.sqrt(sum((a - b) ** 2 for a, b in zip(pos1, pos2)))