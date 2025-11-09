import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

# Load the data, skipping the first line which is the 'cat' command output
# Assuming your final output is in 'slurm-1979932.out'
df = pd.read_csv('slurm-1979932.out', skiprows=0) 

# Pivot the data to get TIME as values, with THREADS as columns and BLOCKS as index
pivot_table = df.pivot(index='NUM_BLOCK', columns='NUM_THREAD', values='TIME')

# Create the plot
plt.figure(figsize=(10, 6))
heatmap = plt.pcolormesh(pivot_table.columns, pivot_table.index, pivot_table.values, shading='auto', cmap='viridis_r')

# Add a color bar
cbar = plt.colorbar(heatmap)
cbar.set_label('Execution Time (seconds)', rotation=270, labelpad=15)

# Set labels and title
plt.xlabel('Threads per Block (NUM_THREAD)')
plt.ylabel('Number of Blocks (NUM_BLOCK)')
plt.title('CUDA π Calculation Scaling on H100 GPU')
plt.xticks(pivot_table.columns)
plt.yticks(pivot_table.index)
plt.show()
