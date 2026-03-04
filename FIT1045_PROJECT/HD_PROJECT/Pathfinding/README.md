# 🎯 2D Pathfinding Visualizer

An interactive web application for visualizing and comparing pathfinding algorithms in 2D grids. Built with Streamlit and Plotly for real-time visualization and algorithm performance analysis.

## Features

- **Multiple Algorithms**: A*, Dijkstra, and RRT (Rapidly-exploring Random Tree)
- **Interactive Grid Editor**: Create custom obstacles or generate random grids
- **Real-time Visualization**: Watch algorithms explore the grid step by step
- **Performance Comparison**: Compare execution time, nodes explored, and path length
- **Responsive Interface**: Clean, intuitive controls with live metrics

## Algorithms Implemented

### A* (A-Star)
- Heuristic-based pathfinding using Manhattan distance
- Optimal and complete for admissible heuristics
- Best performance for most grid layouts

### Dijkstra's Algorithm
- Guaranteed shortest path algorithm
- Explores nodes uniformly in all directions
- More thorough but slower than A*

### RRT (Rapidly-exploring Random Tree)
- Probabilistic pathfinding algorithm
- Good for complex environments with many obstacles
- Fast but may not find optimal paths

## Installation

1. Clone or download the project files
2. Install required dependencies:
```bash
pip install streamlit plotly numpy
```

## Usage

1. Run the application:
```bash
streamlit run app.py
```

2. Configure your pathfinding scenario:
   - Select algorithm (A*, Dijkstra, or RRT)
   - Choose grid type (Random or Custom)
   - Set grid size and obstacle density
   - Define start and end points

3. For custom grids:
   - Click on grid cells to toggle obstacles
   - Use the sidebar to add obstacles by coordinates
   - Clear all obstacles with the "Clear All" button

4. Click "Find Path" to run the selected algorithm

5. Enable "Show Comparison" to compare all algorithms simultaneously

## Project Structure

```
trial6/
├── app.py           # Main Streamlit application
├── pathfinding.py   # Algorithm implementations
├── grid2d.py        # Grid data structure and utilities
├── comparison.py    # Performance comparison dashboard
└── README.md        # This file
```

## File Descriptions

- **app.py**: Main application interface with Streamlit UI components
- **pathfinding.py**: Contains AStar, Dijkstra, and RRT algorithm classes
- **grid2d.py**: Grid2D class for managing the 2D grid and obstacles
- **comparison.py**: ComparisonDashboard for algorithm performance analysis

## Controls

- **Algorithm Selection**: Choose between A*, Dijkstra, or RRT
- **Grid Type**: Random generation or custom obstacle placement
- **Grid Size**: Adjustable from 5x5 to 50x50
- **Start/End Points**: Configurable coordinates
- **Obstacle Density**: For random grids (0-40%)

## Visualization

- **White cells**: Free space
- **Black cells**: Obstacles
- **Green diamond**: Start point
- **Red diamond**: End point
- **Light blue dots**: Visited nodes
- **Yellow line**: Found path

## Performance Metrics

The application displays real-time metrics:
- **Execution Time**: Algorithm runtime in seconds
- **Nodes Explored**: Number of cells visited
- **Path Length**: Number of steps in the solution
- **Algorithm Used**: Currently selected pathfinding method

## Requirements

- Python 3.7+
- streamlit
- plotly
- numpy

## License

This project is for educational purposes as part of FIT1045 coursework.