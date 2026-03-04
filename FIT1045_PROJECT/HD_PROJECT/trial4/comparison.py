import streamlit as st
import plotly.graph_objects as go
import plotly.express as px
import pandas as pd
import time
from pathfinding import AStar, Dijkstra, RRT

class ComparisonDashboard:
    def __init__(self):
        self.algorithms = {
            'A*': AStar,
            'Dijkstra': Dijkstra,
            'RRT': RRT
        }
    
    def run_comparison(self, grid, start, goal):
        """Run all algorithms and compare their performance"""
        results = []
        
        for name, algorithm_class in self.algorithms.items():
            with st.spinner(f"Running {name}..."):
                pathfinder = algorithm_class(grid)
                
                # Measure performance
                start_time = time.time()
                path, visited = pathfinder.find_path(start, goal)
                end_time = time.time()
                
                results.append({
                    'Algorithm': name,
                    'Execution Time (s)': round(end_time - start_time, 4),
                    'Nodes Explored': len(visited),
                    'Path Length': len(path) if path else 0,
                    'Path Found': 'Yes' if path else 'No',
                    'Memory Usage': len(visited) * 24  # Approximate bytes per node
                })
        
        # Display results
        self._display_comparison_table(results)
        self._display_performance_charts(results)
    
    def _display_comparison_table(self, results):
        """Display comparison table"""
        df = pd.DataFrame(results)
        st.dataframe(df, use_container_width=True)
    
    def _display_performance_charts(self, results):
        """Display performance visualization charts"""
        df = pd.DataFrame(results)
        
        col1, col2 = st.columns(2)
        
        with col1:
            # Execution time comparison
            fig_time = px.bar(df, x='Algorithm', y='Execution Time (s)',
                             title='Execution Time Comparison',
                             color='Algorithm')
            st.plotly_chart(fig_time, use_container_width=True)
            
            # Memory usage comparison
            fig_memory = px.bar(df, x='Algorithm', y='Memory Usage',
                               title='Memory Usage Comparison (bytes)',
                               color='Algorithm')
            st.plotly_chart(fig_memory, use_container_width=True)
        
        with col2:
            # Nodes explored comparison
            fig_nodes = px.bar(df, x='Algorithm', y='Nodes Explored',
                              title='Nodes Explored Comparison',
                              color='Algorithm')
            st.plotly_chart(fig_nodes, use_container_width=True)
            
            # Path length comparison
            fig_path = px.bar(df, x='Algorithm', y='Path Length',
                             title='Path Length Comparison',
                             color='Algorithm')
            st.plotly_chart(fig_path, use_container_width=True)
        
        # Efficiency radar chart
        self._create_radar_chart(df)
    
    def _create_radar_chart(self, df):
        """Create radar chart for algorithm comparison"""
        # Normalize metrics for radar chart (0-1 scale)
        df_norm = df.copy()
        
        # Invert time and nodes (lower is better)
        max_time = df['Execution Time (s)'].max()
        max_nodes = df['Nodes Explored'].max()
        max_memory = df['Memory Usage'].max()
        
        df_norm['Speed'] = 1 - (df['Execution Time (s)'] / max_time) if max_time > 0 else 1
        df_norm['Efficiency'] = 1 - (df['Nodes Explored'] / max_nodes) if max_nodes > 0 else 1
        df_norm['Memory Efficiency'] = 1 - (df['Memory Usage'] / max_memory) if max_memory > 0 else 1
        df_norm['Path Quality'] = df['Path Length'] / df['Path Length'].max() if df['Path Length'].max() > 0 else 0
        
        fig = go.Figure()
        
        categories = ['Speed', 'Efficiency', 'Memory Efficiency', 'Path Quality']
        
        for _, row in df_norm.iterrows():
            values = [row[cat] for cat in categories]
            values += values[:1]  # Close the radar chart
            
            fig.add_trace(go.Scatterpolar(
                r=values,
                theta=categories + [categories[0]],
                fill='toself',
                name=row['Algorithm']
            ))
        
        fig.update_layout(
            polar=dict(
                radialaxis=dict(
                    visible=True,
                    range=[0, 1]
                )),
            showlegend=True,
            title="Algorithm Performance Radar Chart"
        )
        
        st.plotly_chart(fig, use_container_width=True)