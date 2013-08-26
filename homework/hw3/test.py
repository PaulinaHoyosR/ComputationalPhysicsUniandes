# Using the magic encoding
# -*- coding: utf-8 -*-

"""
Demo using fontdict to control style of text and labels.
"""
import numpy as np
import matplotlib.pyplot as plt
from matplotlib import rc

rc('font', **{'sans-serif' : 'Arial',
                           'family' : 'sans-serif'})
rc('text', usetex=True)

font = {'family' : 'serif',
        'color'  : 'darkred',
        'weight' : 'normal',
        'size'   : 16,
        }

x = np.linspace(0.0, 5.0, 100)
y = np.cos(2 * np.pi * x) * np.exp(-x)

plt.plot(x, y, 'k')
plt.title('Damped exponential decay', fontdict=font)
a = '$\\alpha > \\beta$'
plt.text(2, 0.65, '%s' %(a) , fontdict=font)
plt.xlabel('time (s)', fontdict=font)
plt.ylabel('voltage (mV)', fontdict=font)

# Tweak spacing to prevent clipping of ylabel
plt.subplots_adjust(left=0.15)
plt.show()
