data : dict[int, int] = {}
exec(open('test.txt').read())

import numpy as np
import matplotlib.pyplot as plt
import time

data = {k:v for k,v in sorted(data.items())}
keys = np.array([*data.keys()])
values = np.array([*data.values()])

fig = plt.figure()

plt.plot(keys, keys)
plt.plot(keys, keys + 300)
plt.plot(keys, keys * 0 + int(time.time()))
plt.plot(keys, values, 'ob')

timer = fig.canvas.new_timer(interval = 5000)
timer.add_callback(plt.close)

plt.show()

