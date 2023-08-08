import matplotlib.pyplot as plt
import random
import math

x = []
y = []


def random_normal():
    theta = 2 * 3.1415926 * random.uniform(0, 1)
    rho = math.sqrt(-2 * math.log(random.uniform(0, 1)))
    return rho * math.cos(theta)


for i in range(1000):
    x.append(random_normal())
    y.append(random_normal())

plt.scatter(x, y)
plt.show()
