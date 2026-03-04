import streamlit as st
import plotly.graph_objects as go
import numpy as np
import time
from pathfinding import AStar, Dijkstra, RRT
from grid3d import Grid3D
from comparison import ComparisonDashboard

st.set_page_config(page_title="3D Pathfinding Visualizer", layout="wide")

def main():
    st.title("🎯 3D Pathfinding Visualizer")
    st.sidebar.title("Controls")
    
    # Algorithm selection
    algorithm = st.sidebar.selectbox("Algorithm", ["A*", "Dijkstra", "RRT"])
    
    # Grid parameters
    st.sidebar.subheader("Grid Settings")
    grid_size = st.sidebar.slider("Grid Size", 10, 30, 20)
    obstacle_density = st.sidebar.slider("Obstacle Density", 0.0, 0.4, 0.2)
    
    # Start/End points
    st.sidebar.subheader("Path Points")
    start_x = st.sidebar.number_input("Start X", 0, grid_size-1, 0)
    start_y = st.sidebar.number_input("Start Y", 0, grid_size-1, 0)
    start_z = st.sidebar.number_input("Start Z", 0, grid_size-1, 0)
    
    end_x = st.sidebar.number_input("End X", 0, grid_size-1, grid_size-1)
    end_y = st.sidebar.number_input("End Y", 0, grid_size-1, grid_size-1)
    end_z = st.sidebar.number_input("End Z", 0, grid_size-1, grid_size-1)
    
    # Initialize grid
    if 'grid' not in st.session_state or st.sidebar.button("Generate New Grid"):
        st.session_state.grid = Grid3D(grid_size, obstacle_density)
    
    grid = st.session_state.grid
    start = (start_x, start_y, start_z)
    end = (end_x, end_y, end_z)
    
    col1, col2 = st.columns([2, 1])
    
    with col1:
        st.subheader("3D Visualization")
        
        if st.button("Find Path"):
            with st.spinner(f"Running {algorithm}..."):
                # Select algorithm
                if algorithm == "A*":
                    pathfinder = AStar(grid)
                elif algorithm == "Dijkstra":
                    pathfinder = Dijkstra(grid)
                else:
                    pathfinder = RRT(grid)
                
                # Find path and measure performance
                start_time = time.time()
                path, visited = pathfinder.find_path(start, end)
                end_time = time.time()
                
                # Store results
                st.session_state.path = path
                st.session_state.visited = visited
                st.session_state.algorithm = algorithm
                st.session_state.execution_time = end_time - start_time
                st.session_state.nodes_explored = len(visited)
        
        # Create 3D plot
        fig = create_3d_plot(grid, start, end, 
                           st.session_state.get('path'), 
                           st.session_state.get('visited'))
        st.plotly_chart(fig, use_container_width=True)
    
    with col2:
        st.subheader("Statistics")
        if 'path' in st.session_state:
            st.metric("Algorithm", st.session_state.algorithm)
            st.metric("Execution Time", f"{st.session_state.execution_time:.4f}s")
            st.metric("Nodes Explored", st.session_state.nodes_explored)
            st.metric("Path Length", len(st.session_state.path) if st.session_state.path else "No path found")
        
        st.subheader("Legend")
        st.markdown("""
        - 🟢 **Start Point**
        - 🔴 **End Point**
        - ⚫ **Obstacles**
        - 🔵 **Visited Nodes**
        - 🟡 **Path**
        """)
    
    # Comparison Dashboard
    if st.checkbox("Show Comparison Dashboard"):
        st.subheader("Algorithm Comparison")
        dashboard = ComparisonDashboard()
        dashboard.run_comparison(grid, start, end)

def create_3d_plot(grid, start, end, path=None, visited=None):
    fig = go.Figure()
    
    # Add obstacles
    obstacles = grid.get_obstacles()
    if obstacles:
        obs_x, obs_y, obs_z = zip(*obstacles)
        fig.add_trace(go.Scatter3d(
            x=obs_x, y=obs_y, z=obs_z,
            mode='markers',
            marker=dict(size=8, color='black', symbol='square'),
            name='Obstacles'
        ))
    
    # Add visited nodes
    if visited:
        vis_x, vis_y, vis_z = zip(*visited)
        fig.add_trace(go.Scatter3d(
            x=vis_x, y=vis_y, z=vis_z,
            mode='markers',
            marker=dict(size=4, color='lightblue', opacity=0.6),
            name='Visited'
        ))
    
    # Add path
    if path:
        path_x, path_y, path_z = zip(*path)
        fig.add_trace(go.Scatter3d(
            x=path_x, y=path_y, z=path_z,
            mode='lines+markers',
            line=dict(color='yellow', width=6),
            marker=dict(size=6, color='orange'),
            name='Path'
        ))
    
    # Add start and end points
    fig.add_trace(go.Scatter3d(
        x=[start[0]], y=[start[1]], z=[start[2]],
        mode='markers',
        marker=dict(size=12, color='green', symbol='diamond'),
        name='Start'
    ))
    
    fig.add_trace(go.Scatter3d(
        x=[end[0]], y=[end[1]], z=[end[2]],
        mode='markers',
        marker=dict(size=12, color='red', symbol='diamond'),
        name='End'
    ))
    
    fig.update_layout(
        scene=dict(
            xaxis_title='X',
            yaxis_title='Y',
            zaxis_title='Z',
            aspectmode='cube'
        ),
        height=600,
        showlegend=True
    )
    
    return fig

if __name__ == "__main__":
    main()