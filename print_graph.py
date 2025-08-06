from matplotlib import pyplot as plt
import pandas as pd

fig = plt.figure()
ax = fig.add_subplot(111)

# Координаты узлов (можно задать вручную)
coords = pd.read_csv('data.csv')
decision = list(pd.read_csv('decision.csv').columns)

print(decision)

positions = {}

for i in range(len(coords)):
    positions[str(i)] = (coords['x'][i], coords['y'][i])


for city, pos in positions.items():
    ax.scatter(*pos, s=100, label=city)
    ax.text(*pos, city, fontsize=12)

for i in range(len(coords)):
    for j in range(i + 1, len(coords)):
        ax.plot([coords['x'][i], coords['x'][j]], [coords['y'][i], coords['y'][j]], 'gray')


ax.plot([coords['x'][0], coords['x'][int(decision[0])]], [coords['y'][0], coords['y'][int(decision[0])]], 'red')

for i in range(len(decision) - 1):
    index = int(decision[i])
    j = int(decision[i + 1])
    ax.plot([coords['x'][index], coords['x'][j]], [coords['y'][index], coords['y'][j]], 'red')

ax.plot([coords['x'][int(decision[-1])], coords['x'][0]], [coords['y'][int(decision[-1])], coords['y'][0]], 'red')


plt.show()
