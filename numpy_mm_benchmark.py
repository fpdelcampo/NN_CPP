import numpy as np
import time

def at512(n=50):
    times = []
    for _ in range(n):
        x = np.random.normal(0, 15, (512, 512)).astype('double')
        y = np.random.normal(0, 15, (512, 512)).astype('double')
        s = time.time()
        np.matmul(x, y)
        e = time.time()
        times.append(e-s)
    return np.mean(times)

def dot512(n=50):
    times = []
    for _ in range(n):
        x = np.random.normal(0, 15, (512, 512)).astype('double')
        y = np.random.normal(0, 15, (512, 512)).astype('double')
        s = time.time()
        np.dot(x, y)
        e = time.time()
        times.append(e-s)
    return np.mean(times)

def mm512(n=50):
    times = []
    for _ in range(n):
        x = np.random.normal(0, 15, (512, 512)).astype('double')
        y = np.random.normal(0, 15, (512, 512)).astype('double')
        s = time.time()
        np.matmul(x, y)
        e = time.time()
        times.append(e-s)
    return np.mean(times)


t1 = at512(10)
t2 = dot512(10)
t3 = mm512(10)
print(f"X @ Y: {t1}")
print(f"np.dot(X, Y): {t2}")
print(f"np.matmul(X, Y): {t3}")