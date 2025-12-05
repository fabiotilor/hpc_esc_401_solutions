#!/usr/bin/env python3

import numpy as np
import matplotlib
matplotlib.use("Agg")  # for headless environments
import matplotlib.pyplot as plt
from matplotlib.colors import LogNorm
from numpy import genfromtxt
import os

# paths to the files
path_to_output = "output/output_0010000.csv"
path_to_source = "output/output_source.csv"

# read image data
source = genfromtxt(path_to_source, delimiter=',')
data = genfromtxt(path_to_output, delimiter=',')

# extract nstep from filename reliably
filename = os.path.basename(path_to_output)  # e.g., "output_0010000.csv"
nstep_str = filename.split('_')[1].split('.')[0]  # "0010000"
nstep = int(nstep_str)

# plot the map
fig, ax = plt.subplots(1, 2, figsize=(7, 3), sharex=True)
fig.subplots_adjust(left=0.02, bottom=0.06, right=0.95, top=0.94, wspace=0.05)

im1 = ax[0].imshow(source.T, origin='lower')
im2 = ax[1].imshow(data.T, origin='lower')

ax[0].set_xlabel("ny")
ax[1].set_xlabel("ny")
ax[0].set_ylabel("nx")

ax[0].set_title("Source term")
ax[1].set_title(f"Approx. Solution, step={nstep}")

fig.colorbar(im1, ax=ax[0])
fig.colorbar(im2, ax=ax[1])

plt.tight_layout()
plt.savefig("test.png")
print("Plot saved as test.png")

