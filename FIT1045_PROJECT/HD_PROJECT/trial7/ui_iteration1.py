import streamlit as st
import plotly.graph_objects as go
import numpy as np

st.set_page_config(page_title="2D Pathfinding Visualizer", layout="wide")

def main():
    st.title("🎯 2D Pathfinding Visualizer")
    st.sidebar.title("Controls")
    
    # Algorithm selection
    algorithm = st.sidebar.selectbox("Algorithm", ["A*", "Dijkstra", "RRT"])
    
    # Grid configuration
    grid_type = st.sidebar.radio("Grid Type", ["Random", "Custom"])
    grid_size = st.sidebar.slider("Grid Size", 5, 50, 15)
    
    if grid_type == "Random":
        obstacle_density = st.sidebar.slider("Obstacle Density", 0.0, 0.4, 0.2)
    
    # Start and end points
    start_x = st.sidebar.number_input("Start X", 0, grid_size-1, 0)
    start_y = st.sidebar.number_input("Start Y", 0, grid_size-1, 0)
    end_x = st.sidebar.number_input("End X", 0, grid_size-1, grid_size-1)
    end_y = st.sidebar.number_input("End Y", 0, grid_size-1, grid_size-1)
    
    # Grid generation
    if st.sidebar.button("Generate New Grid"):
        st.success("Grid generated!")
    
    # Custom grid editor
    if grid_type == "Custom":
        st.sidebar.write("**Map Editor**")
        
        coord_input = st.sidebar.text_input("Toggle obstacle (x,y):", placeholder="5,10")
        if st.sidebar.button("Toggle"):
            if coord_input:
                st.success(f"Toggled obstacle at {coord_input}")
            else:
                st.error("Please enter coordinates")
        
        if grid_size <= 12:
            st.sidebar.write("**Click Grid Editor**")
            create_mini_grid_ui(grid_size, (start_x, start_y), (end_x, end_y))
        
        if st.sidebar.button("Clear All"):
            st.success("All obstacles cleared!")
        
        st.sidebar.write("Obstacles: 0")
    
    # Main layout
    col1, col2 = st.columns([3, 1])
    
    with col1:
        if st.button("Find Path", type="primary"):
            st.success(f"Finding path using {algorithm}...")
        
        # Create mock visualization
        fig = create_mock_plot(grid_size, (start_x, start_y), (end_x, end_y))
        st.plotly_chart(fig, use_container_width=True)
    
    with col2:
        st.metric("Algorithm", algorithm)
        st.metric("Time", "0.0000s")
        st.metric("Nodes", "0")
        st.metric("Path Length", "No path")
    
    if st.checkbox("Show Comparison"):
        st.write("**Algorithm Comparison**")
        st.write("Comparison dashboard would appear here")

def create_mini_grid_ui(grid_size, start, end):
    """Create a mini grid UI for small grids"""
    for y in range(min(grid_size, 8)):  # Limit display for UI demo
        cols = st.sidebar.columns(min(grid_size, 8))
        for x in range(min(grid_size, 8)):
            with cols[x]:
                pos = (x, y)
                if pos == start:
                    st.button("🟢", key=f"mini_{x}_{y}", disabled=True)
                elif pos == end:
                    st.button("🔴", key=f"mini_{x}_{y}", disabled=True)
                else:
                    if st.button("⬜", key=f"mini_{x}_{y}"):
                        st.success(f"Toggled ({x},{y})")

def create_mock_plot(grid_size, start, end):
    """Create a mock visualization plot"""
    fig = go.Figure()
    
    # Create empty grid
    grid_array = np.zeros((grid_size, grid_size))
    
    fig.add_trace(go.Heatmap(
        z=grid_array,
        colorscale=[[0, 'white'], [1, 'black']],
        showscale=False
    ))
    
    # Add start point
    fig.add_trace(go.Scatter(
        x=[start[0]], y=[start[1]],
        mode='markers',
        marker=dict(size=15, color='green', symbol='diamond'),
        name='Start'
    ))
    
    # Add end point
    fig.add_trace(go.Scatter(
        x=[end[0]], y=[end[1]],
        mode='markers',
        marker=dict(size=15, color='red', symbol='diamond'),
        name='End'
    ))
    
    fig.update_layout(
        height=600,
        xaxis_title='X',
        yaxis_title='Y',
        yaxis=dict(scaleanchor="x", scaleratio=1)
    )
    
    return fig

if __name__ == "__main__":
    main()