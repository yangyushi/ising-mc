#!/usr/bin/env python
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation


configs = np.loadtxt('configure.csv', delimiter=',')
size = int(configs.shape[1] ** 0.5)
frames = configs.shape[0]

fig, ax = plt.subplots()
fig.set_size_inches(3, 3)
img = ax.imshow(np.ones((size, size)), vmin=-1.5, vmax=1.5, cmap='bwr')

def run(frame):
    # update the data
    img.set_data(configs[frame].reshape(size, size))
    return img

ani = animation.FuncAnimation(fig, run, frames=frames, repeat=False, interval=10)

plt.show()
plt.close()
