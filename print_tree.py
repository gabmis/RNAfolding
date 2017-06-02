import numpy as np
import matplotlib.pyplot as plt
plt.close('all')
f = open('letters.txt', 'r')
letters = []
x = []
y = []
while(True):
    letter = f.readline()
    if(letter == ""):
        break
    letters.append(letter)
    x.append(float(f.readline()))
    y.append(float(f.readline()))


for i in range(len(y)):
    plt.text(x[i],y[i],letters[i][0],fontsize = 13)
    print(letters[i][0])
    print(x[i])
    print(y[i])

xmax = 0.0
xmin = 0.0
ymax = 0.0
ymin=0.0

for i in range(len(x)):
    xmax = max(xmax, x[i])
    xmin = min(xmin, x[i])
    ymax = max(ymax, y[i])
    ymin = min(ymin, y[i])

xmax +=1
ymax+=1
xmin-=1
ymin-=1

if(xmax-xmin>ymax-ymin):
    ymin = ymin - (xmax-xmin-(ymax-ymin))/2
    ymax = ymax + (xmax-xmin-(ymax-ymin))/2
else:
    xmin = xmin - (ymax - ymin - (xmax - xmin)) / 2
    xmax = xmax + (ymax - ymin - (xmax - xmin)) / 2


plt.axis([xmin,xmax, ymin, ymax])
plt.show()