data : dict[int, int] = {}
exec(open('test.txt').read())

import numpy as np
import matplotlib.pyplot as plt
import time

data = {k:v for k,v in sorted(data.items())}
ct = int(time.time())
data[ct]=float('inf')
keys = np.array([*data.keys()])
values = np.array([*data.values()])

plt.plot(keys, keys)
plt.plot(keys, keys + 300)
plt.plot(keys, keys * 0 + ct)
plt.scatter(keys, values, marker='o', s=0.1)

plt.show()

