import heapq
import random
import numpy as np

class AStar:
    def __init__(self, grid):
        self.grid = grid
    
    def find_path(self, start, goal):
        open_set = [(0, start)]
        came_from = {}
        g_score = {start: 0}
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
                    f_score = tentative_g + self.grid.distance(neighbor, goal)
                    heapq.heappush(open_set, (f_score, neighbor))
        
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
                if neighbor not in visited:
                    distance = current_dist + self.grid.distance(current, neighbor)
                    if neighbor not in distances or distance < distances[neighbor]:
                        distances[neighbor] = distance
                        previous[neighbor] = current
                        heapq.heappush(unvisited, (distance, neighbor))
        
        return None, list(visited)

class RRT:
    def __init__(self, grid, max_iterations=500):
        self.grid = grid
        self.max_iterations = max_iterations
    
    def find_path(self, start, goal):
        tree = {start: None}
        visited = [start]
        
        for _ in range(self.max_iterations):
            random_point = (random.randint(0, self.grid.size-1), random.randint(0, self.grid.size-1))
            nearest = min(tree.keys(), key=lambda x: self.grid.distance(x, random_point))
            
            direction = np.array(random_point) - np.array(nearest)
            if np.linalg.norm(direction) > 0:
                new_point = tuple(np.array(nearest) + np.clip(direction, -1, 1).astype(int))
                
                if self.grid.is_valid(new_point) and new_point not in tree:
                    tree[new_point] = nearest
                    visited.append(new_point)
                    
                    if self.grid.distance(new_point, goal) < 2:
                        tree[goal] = new_point
                        visited.append(goal)
                        
                        path = []
                        current = goal
                        while current is not None:
                            path.append(current)
                            current = tree[current]
                        return path[::-1], visited
        
        return None, visited