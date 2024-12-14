import matplotlib.pyplot as plt
fig, (plt_avg, plt_max) = plt.subplots(2, 1)
plt_avg, plt_max = [plt_avg], [plt_max]
plt_avg[0].set_title('IncCriticalSection.avg')
plt_max[0].set_title('IncCriticalSection.max')
