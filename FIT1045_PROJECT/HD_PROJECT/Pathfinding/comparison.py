import streamlit as st
import plotly.express as px
import pandas as pd
import time
from pathfinding import AStar, Dijkstra, RRT

class ComparisonDashboard:
    def run_comparison(self, grid, start, goal):
        algorithms = {'A*': AStar, 'Dijkstra': Dijkstra, 'RRT': RRT}
        results = []
        
        for name, algorithm_class in algorithms.items():
            pathfinder = algorithm_class(grid)
            start_time = time.time()
            path, visited = pathfinder.find_path(start, goal)
            end_time = time.time()
            
            results.append({
                'Algorithm': name,
                'Time (s)': round(end_time - start_time, 4),
                'Nodes': len(visited),
                'Path Length': len(path) if path else 0
            })
        
        df = pd.DataFrame(results)
        st.dataframe(df)
        
        col1, col2 = st.columns(2)
        with col1:
            fig = px.bar(df, x='Algorithm', y='Time (s)', title='Execution Time')
            st.plotly_chart(fig, use_container_width=True)
        with col2:
            fig = px.bar(df, x='Algorithm', y='Nodes', title='Nodes Explored')
            st.plotly_chart(fig, use_container_width=True)