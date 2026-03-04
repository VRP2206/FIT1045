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
        st.sidebar.write("**Map Editor**")
        
        # Quick coordinate input
        coord_input = st.sidebar.text_input("Toggle obstacle (x,y):", placeholder="5,10")
        if st.sidebar.button("Toggle") and coord_input:
            try:
                x, y = map(int, coord_input.split(','))
                pos = (x, y)
                if pos in st.session_state.grid.obstacles:
                    st.session_state.grid.obstacles.remove(pos)
                else:
                    st.session_state.grid.add_obstacle(pos)
                st.rerun()
            except ValueError:
                st.sidebar.error("Invalid format")
        
        # Grid editor for small grids
        if grid_size <= 12:
            st.sidebar.write("**Click Grid Editor**")
            create_mini_grid(st.session_state.grid, (start_x, start_y), (end_x, end_y))
        
        if st.sidebar.button("Clear All"):
            st.session_state.grid = Grid2D.create_blank(grid_size)
            st.rerun()
        
        st.sidebar.write(f"Obstacles: {len(st.session_state.grid.obstacles)}")
    
    grid = st.session_state.grid
    start = (start_x, start_y)
    end = (end_x, end_y)
    
    col1, col2 = st.columns([3, 1])
    
    with col1:
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
        
        # Initialize hover coordinates in session state
        if 'hover_coords' not in st.session_state:
            st.session_state.hover_coords = None
        
        # Add instruction for users
        st.info("💡 Hover over the grid and press 'V' to toggle obstacles at that position")
        
        # Create input field for coordinates (hidden but functional)
        hover_input = st.text_input("Hover coordinates (auto-filled)", 
                                   value=str(st.session_state.hover_coords) if st.session_state.hover_coords else "",
                                   key="hover_input", 
                                   help="Coordinates will appear here when you hover. Press V to toggle obstacle.")
        
        # Toggle obstacle with V key simulation
        if st.button("Toggle Obstacle at Hover Position (or press V)", key="toggle_v"):
            if st.session_state.hover_coords:
                try:
                    coords_str = str(st.session_state.hover_coords).strip('()')
                    x, y = map(int, coords_str.split(', '))
                    pos = (x, y)
                    if pos != start and pos != end:
                        if pos in grid.obstacles:
                            grid.obstacles.remove(pos)
                        else:
                            grid.add_obstacle(pos)
                        st.rerun()
                except (ValueError, AttributeError):
                    st.error("Invalid hover coordinates")
        
        fig = create_plot(grid, start, end, st.session_state.get('path'), st.session_state.get('visited'))
        
        # Enhanced plot with click handling as fallback
        event = st.plotly_chart(fig, use_container_width=True, on_select="rerun", key="main_plot")
        
        # Handle click events as alternative to hover+V
        if event and hasattr(event, 'selection') and event.selection and event.selection.points:
            point = event.selection.points[0]
            x, y = int(point['x']), int(point['y'])
            pos = (x, y)
            if pos != start and pos != end:
                if pos in grid.obstacles:
                    grid.obstacles.remove(pos)
                else:
                    grid.add_obstacle(pos)
                st.rerun()
        
        # JavaScript for keyboard and hover handling
        st.components.v1.html(f"""
        <script>
        let currentHoverCoords = null;
        
        // Function to update hover coordinates
        function updateHoverCoords(x, y) {{
            currentHoverCoords = [Math.round(x), Math.round(y)];
            const input = window.parent.document.querySelector('input[data-testid="stTextInput"]');
            if (input) {{
                input.value = `(${{Math.round(x)}}, ${{Math.round(y)}})`;
                input.dispatchEvent(new Event('input', {{ bubbles: true }}));
            }}
        }}
        
        // Keyboard event listener
        document.addEventListener('keydown', function(e) {{
            if ((e.key === 'v' || e.key === 'V') && currentHoverCoords) {{
                const button = window.parent.document.querySelector('button[kind="secondary"]');
                if (button && button.textContent.includes('Toggle Obstacle')) {{
                    button.click();
                }}
            }}
        }});
        
        // Set up plot hover detection
        setTimeout(function() {{
            const plotDiv = window.parent.document.querySelector('.plotly-graph-div');
            if (plotDiv) {{
                plotDiv.on('plotly_hover', function(data) {{
                    if (data.points && data.points[0]) {{
                        updateHoverCoords(data.points[0].x, data.points[0].y);
                    }}
                }});
            }}
        }}, 1000);
        </script>
        """, height=0)
    
    with col2:
        if 'path' in st.session_state:
            st.metric("Algorithm", st.session_state.algorithm)
            st.metric("Time", f"{st.session_state.execution_time:.4f}s")
            st.metric("Nodes", st.session_state.nodes_explored)
            st.metric("Path Length", len(st.session_state.path) if st.session_state.path else "No path")
    
    if st.checkbox("Show Comparison"):
        dashboard = ComparisonDashboard()
        dashboard.run_comparison(grid, start, end)

def create_mini_grid(grid, start, end):
    for y in range(grid.size):
        cols = st.sidebar.columns(grid.size)
        for x in range(grid.size):
            with cols[x]:
                pos = (x, y)
                if pos == start:
                    st.button("🟢", key=f"mini_{x}_{y}", disabled=True)
                elif pos == end:
                    st.button("🔴", key=f"mini_{x}_{y}", disabled=True)
                elif pos in grid.obstacles:
                    if st.button("⬛", key=f"mini_{x}_{y}"):
                        grid.obstacles.remove(pos)
                        st.rerun()
                else:
                    if st.button("⬜", key=f"mini_{x}_{y}"):
                        grid.add_obstacle(pos)
                        st.rerun()

def create_plot(grid, start, end, path=None, visited=None):
    fig = go.Figure()
    
    # Create grid array
    grid_array = np.zeros((grid.size, grid.size))
    for x, y in grid.obstacles:
        grid_array[y, x] = 1
    
    fig.add_trace(go.Heatmap(
        z=grid_array,
        colorscale=[[0, 'white'], [1, 'black']],
        showscale=False,
        hovertemplate='X: %{x}<br>Y: %{y}<br>Press V to toggle obstacle<extra></extra>'
    ))
    
    if visited:
        vis_x, vis_y = zip(*visited)
        fig.add_trace(go.Scatter(
            x=vis_x, y=vis_y,
            mode='markers',
            marker=dict(size=8, color='lightblue', opacity=0.6),
            name='Visited'
        ))
    
    if path:
        path_x, path_y = zip(*path)
        fig.add_trace(go.Scatter(
            x=path_x, y=path_y,
            mode='lines+markers',
            line=dict(color='yellow', width=4),
            marker=dict(size=8, color='orange'),
            name='Path'
        ))
    
    fig.add_trace(go.Scatter(
        x=[start[0]], y=[start[1]],
        mode='markers',
        marker=dict(size=15, color='green', symbol='diamond'),
        name='Start'
    ))
    
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