import numpy as np
import matplotlib.pyplot as plt

data = np.loadtxt('result.csv', delimiter=',')
t, m, c = data.T 
plt.plot(t, m, '-o', label='<magnetisation>', markerfacecolor='w', color='tomato')
plt.plot(t, c, '-o', label='heat capacity', markerfacecolor='w', color='teal')
plt.xlabel('Temperature', fontsize=14)
plt.legend(fontsize=14)
plt.tight_layout()
plt.show()

