import streamlit as st
import plotly.graph_objects as go
import numpy as np
import time
from pathfinding import AStar, Dijkstra, RRT
from grid2d import Grid2D
from comparison import ComparisonDashboard

st.set_page_config(page_title="2D Pathfinding Visualizer", layout="wide")

def main():
    st.title("🎯 2D Pathfinding Visualizer")
    st.sidebar.title("Controls")
    
    algorithm = st.sidebar.selectbox("Algorithm", ["A*", "Dijkstra", "RRT"])
    grid_type = st.sidebar.radio("Grid Type", ["Random", "Custom"])
    grid_size = st.sidebar.slider("Grid Size", 5, 50, 15)
    
    if grid_type == "Random":
        obstacle_density = st.sidebar.slider("Obstacle Density", 0.0, 0.4, 0.2)
    
    start_x = st.sidebar.number_input("Start X", 0, grid_size-1, 0)
    start_y = st.sidebar.number_input("Start Y", 0, grid_size-1, 0)
    end_x = st.sidebar.number_input("End X", 0, grid_size-1, grid_size-1)
    end_y = st.sidebar.number_input("End Y", 0, grid_size-1, grid_size-1)
    
    if 'grid' not in st.session_state or st.sidebar.button("Generate New Grid"):
        if grid_type == "Random":
            st.session_state.grid = Grid2D(grid_size, obstacle_density)
        else:
            st.session_state.grid = Grid2D.create_blank(grid_size)
    
    if grid_type == "Custom":
        st.sidebar.write("**Custom Grid Editor**")
        obstacle_input = st.sidebar.text_input("Add obstacle (x,y):", placeholder="5,10")
        
        col_add, col_clear = st.sidebar.columns(2)
        with col_add:
            if st.button("Add") and obstacle_input:
                try:
                    x, y = map(int, obstacle_input.split(','))
                    st.session_state.grid.add_obstacle((x, y))
                    st.rerun()
                except ValueError:
                    st.error("Invalid format")
        
        with col_clear:
            if st.button("Clear All"):
                st.session_state.grid = Grid2D.create_blank(grid_size)
                st.rerun()
        
        st.sidebar.write(f"Obstacles: {len(st.session_state.grid.obstacles)}")
    
    grid = st.session_state.grid
    start = (start_x, start_y)
    end = (end_x, end_y)
    
    col1, col2 = st.columns([3, 1])
    
    with col1:
        if grid_type == "Custom":
            st.write("**Click to toggle obstacles**")
        
        if st.button("Find Path", type="primary"):
            pathfinder = AStar(grid) if algorithm == "A*" else Dijkstra(grid) if algorithm == "Dijkstra" else RRT(grid)
            
            start_time = time.time()
            path, visited = pathfinder.find_path(start, end)
            end_time = time.time()
            
            st.session_state.path = path
            st.session_state.visited = visited
            st.session_state.algorithm = algorithm
            st.session_state.execution_time = end_time - start_time
            st.session_state.nodes_explored = len(visited)
        
        fig = create_2d_plot(grid, start, end, st.session_state.get('path'), st.session_state.get('visited'))
        
        if grid_type == "Custom":
            clicked_data = st.plotly_chart(fig, use_container_width=True, on_select="rerun", selection_mode="points")
            if clicked_data and clicked_data.selection and clicked_data.selection.points:
                point = clicked_data.selection.points[0]
                x, y = int(point['x']), grid.size - 1 - int(point['y'])
                pos = (x, y)
                if pos != start and pos != end:
                    if pos in grid.obstacles:
                        grid.obstacles.remove(pos)
                    else:
                        grid.add_obstacle(pos)
                    st.rerun()
        else:
            st.plotly_chart(fig, use_container_width=True)
    
    with col2:
        if 'path' in st.session_state:
            st.metric("Algorithm", st.session_state.algorithm)
            st.metric("Time", f"{st.session_state.execution_time:.4f}s")
            st.metric("Nodes", st.session_state.nodes_explored)
            st.metric("Path Length", len(st.session_state.path) if st.session_state.path else "No path")
    
    if st.checkbox("Show Comparison"):
        dashboard = ComparisonDashboard()
        dashboard.run_comparison(grid, start, end)

def create_2d_plot(grid, start, end, path=None, visited=None):
    fig = go.Figure()
    
    # Fix inverted y-axis by reversing the grid array
    grid_array = np.array([[1 if (x, grid.size-1-y) in grid.obstacles else 0 for x in range(grid.size)] for y in range(grid.size)])
    fig.add_trace(go.Heatmap(z=grid_array, colorscale=[[0, 'white'], [1, 'black']], showscale=False))
    
    if visited:
        vis_x, vis_y = zip(*visited)
        # Invert y coordinates for display
        vis_y = [grid.size-1-y for y in vis_y]
        fig.add_trace(go.Scatter(x=vis_x, y=vis_y, mode='markers', marker=dict(size=8, color='lightblue', opacity=0.6), name='Visited'))
    
    if path:
        path_x, path_y = zip(*path)
        # Invert y coordinates for display
        path_y = [grid.size-1-y for y in path_y]
        fig.add_trace(go.Scatter(x=path_x, y=path_y, mode='lines+markers', line=dict(color='yellow', width=4), marker=dict(size=8, color='orange'), name='Path'))
    
    # Invert y coordinates for start and end points
    fig.add_trace(go.Scatter(x=[start[0]], y=[grid.size-1-start[1]], mode='markers', marker=dict(size=15, color='green', symbol='diamond'), name='Start'))
    fig.add_trace(go.Scatter(x=[end[0]], y=[grid.size-1-end[1]], mode='markers', marker=dict(size=15, color='red', symbol='diamond'), name='End'))
    
    fig.update_layout(height=600, xaxis_title='X', yaxis_title='Y', yaxis=dict(scaleanchor="x", scaleratio=1, autorange="reversed"))
    return fig



if __name__ == "__main__":
    main()