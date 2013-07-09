from pylab import *
import csv
import sys
from math import ceil

data = [(line[0], line[1:]) for line in csv.reader(sys.stdin)]
str_title = data[0][0]
data = data[1:]

fig = figure(str_title, figsize = (20, 20))
ax = axes([0.1, 0.1, 2.0, 2.0])

NUMBER_BY_LINE = 4
for i, model in enumerate(data):
    ax = subplot2grid((int(ceil(len(data) / NUMBER_BY_LINE)), NUMBER_BY_LINE), (int(i / NUMBER_BY_LINE), i % NUMBER_BY_LINE), title = model[0])
    ax.pie(model[1], labels = ('A', 'N', 'S', 'naive'), colors = ('#FF7F00', '#7F00FF', 'g', 'c'))

if len(sys.argv) > 1:
    savefig(sys.argv[1] + '.png')
else:
    show()
