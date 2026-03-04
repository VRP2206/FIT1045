from grid2d import Grid2D

# Method 1: Create a blank grid and add obstacles manually
print("Method 1: Manual obstacle placement")
grid1 = Grid2D.create_blank(5)
grid1.add_obstacle((1, 1))
grid1.add_obstacle((2, 2))
grid1.add_obstacle((3, 1))
print(f"Grid1 created with obstacles at: {sorted(grid1.obstacles)}")

# Method 2: Use interactive editor (uncomment to use)
# print("\nMethod 2: Interactive editor")
# grid2 = Grid2D.create_blank(10)
# grid2.interactive_editor()
# print(f"Grid2 created with {len(grid2.obstacles)} obstacles")

# Method 3: Traditional random generation
print("\nMethod 3: Random generation")
grid3 = Grid2D(8, obstacle_density=0.15)
print(f"Grid3 created with {len(grid3.obstacles)} random obstacles")

print("\nAll grids are ready for pathfinding algorithms!")