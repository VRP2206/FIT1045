# 🎯 3D Pathfinding Visualizer

Interactive 3D application for visualizing pathfinding algorithms in three-dimensional space.

## Features

- **3D Visualization**: Interactive 3D grid with obstacles and pathfinding
- **Multiple Algorithms**: A*, Dijkstra, and RRT implementations
- **Real-time Computation**: Live pathfinding with performance metrics
- **Comparison Dashboard**: Side-by-side algorithm performance analysis
- **Customizable Environment**: Adjustable grid size and obstacle density

## Algorithms Implemented

### A* (A-Star)
- Uses heuristic function for optimal pathfinding
- Guarantees shortest path
- Efficient for known goal locations

### Dijkstra's Algorithm
- Explores all possible paths systematically
- Guarantees shortest path
- No heuristic needed

### RRT (Rapidly-exploring Random Tree)
- Probabilistic pathfinding approach
- Good for complex environments
- Fast exploration of space

## Quick Start

1. Run `start.bat` to launch the application
2. Adjust grid settings in the sidebar
3. Set start and end points
4. Select an algorithm and click "Find Path"
5. Enable comparison dashboard for performance analysis

## Performance Metrics

- **Execution Time**: Algorithm runtime
- **Nodes Explored**: Number of nodes visited
- **Path Length**: Total path distance
- **Memory Usage**: Approximate memory consumption

## Controls

- **Grid Size**: 10-30 nodes per dimension
- **Obstacle Density**: 0-40% of grid filled with obstacles
- **Start/End Points**: Customizable 3D coordinates
- **Algorithm Selection**: Choose between A*, Dijkstra, or RRT

## Visualization Legend

- 🟢 Start Point
- 🔴 End Point  
- ⚫ Obstacles
- 🔵 Visited Nodes
- 🟡 Optimal Path