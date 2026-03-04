import heapq
import random
import numpy as np
from collections import deque

class AStar:
    def __init__(self, grid):
        self.grid = grid
    
    def heuristic(self, pos, goal):
        return self.grid.distance(pos, goal)
    
    def find_path(self, start, goal):
        open_set = [(0, start)]
        came_from = {}
        g_score = {start: 0}
        f_score = {start: self.heuristic(start, goal)}
        visited = set()
        
        while open_set:
            current = heapq.heappop(open_set)[1]
            visited.add(current)
            
            if current == goal:
                path = []
                while current in came_from:
                    path.append(current)
                    current = came_from[current]
                path.append(start)
                return path[::-1], list(visited)
            
            for neighbor in self.grid.get_neighbors(current):
                tentative_g = g_score[current] + self.grid.distance(current, neighbor)
                
                if neighbor not in g_score or tentative_g < g_score[neighbor]:
                    came_from[neighbor] = current
                    g_score[neighbor] = tentative_g
                    f_score[neighbor] = tentative_g + self.heuristic(neighbor, goal)
                    heapq.heappush(open_set, (f_score[neighbor], neighbor))
        
        return None, list(visited)

class Dijkstra:
    def __init__(self, grid):
        self.grid = grid
    
    def find_path(self, start, goal):
        distances = {start: 0}
        previous = {}
        unvisited = [(0, start)]
        visited = set()
        
        while unvisited:
            current_dist, current = heapq.heappop(unvisited)
            
            if current in visited:
                continue
            
            visited.add(current)
            
            if current == goal:
                path = []
                while current in previous:
                    path.append(current)
                    current = previous[current]
                path.append(start)
                return path[::-1], list(visited)
            
            for neighbor in self.grid.get_neighbors(current):
                if neighbor in visited:
                    continue
                
                distance = current_dist + self.grid.distance(current, neighbor)
                
                if neighbor not in distances or distance < distances[neighbor]:
                    distances[neighbor] = distance
                    previous[neighbor] = current
                    heapq.heappush(unvisited, (distance, neighbor))
        
        return None, list(visited)

class RRT:
    def __init__(self, grid, max_iterations=1000, step_size=2):
        self.grid = grid
        self.max_iterations = max_iterations
        self.step_size = step_size
    
    def find_path(self, start, goal):
        tree = {start: None}
        visited = [start]
        
        for _ in range(self.max_iterations):
            # Random sampling
            if random.random() < 0.1:  # 10% chance to sample goal
                random_point = goal
            else:
                random_point = (
                    random.randint(0, self.grid.size - 1),
                    random.randint(0, self.grid.size - 1),
                    random.randint(0, self.grid.size - 1)
                )
            
            # Find nearest node in tree
            nearest = min(tree.keys(), 
                         key=lambda x: self.grid.distance(x, random_point))
            
            # Step towards random point
            new_point = self._step_towards(nearest, random_point)
            
            if new_point and self.grid.is_valid(new_point) and new_point not in tree:
                tree[new_point] = nearest
                visited.append(new_point)
                
                # Check if we reached the goal
                if self.grid.distance(new_point, goal) < self.step_size:
                    tree[goal] = new_point
                    visited.append(goal)
                    
                    # Reconstruct path
                    path = []
                    current = goal
                    while current is not None:
                        path.append(current)
                        current = tree[current]
                    
                    return path[::-1], visited
        
        return None, visited
    
    def _step_towards(self, from_point, to_point):
        """Take a step from from_point towards to_point"""
        direction = np.array(to_point) - np.array(from_point)
        distance = np.linalg.norm(direction)
        
        if distance == 0:
            return None
        
        # Normalize and scale by step size
        step = direction / distance * min(self.step_size, distance)
        new_point = np.array(from_point) + step
        
        # Round to integer coordinates
        return tuple(map(int, np.round(new_point)))