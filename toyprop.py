import numpy as np

# network goes R50 --> R20 --> R20 --> R10
w_1 = np.random.normal(0,0.05,(50, 20))
b_1 = np.random.normal(0,0.05,20)

w_2 = np.random.normal(0,0.05,(20, 10))
b_2 = np.random.normal(0,0.05,10)

w_3 = np.random.normal(0,0.05,(10, 1))
b_3 = np.random.normal(0,0.05,1)

X = np.random.normal(0, 1, (10000, 50))
y = np.array([np.sum(X[x,:]**2) for x in range(10000)])

X_train = X[:8000, :]
X_test = X[8000:, :]

y_train = np.sum(X[:8000, :], axis=1)
y_test = np.sum(X[8000:, :], axis=1)

def loss(y, y_pred):
    return .5*(y-y_pred)**2

def dloss(y, y_pred):
    return y-y_pred

def activation(z):
    return z * (z>0)

def dactivation(z):
    return 1 * (z>0)

test_losses = []

def forward(X, params):
    w_1, b_1, w_2, b_2, w_3, b_3 = params
    z_1 = X @ w_1 + b_1
    a_1 = activation(z_1)

    z_2 = a_1 @ w_2 + b_2
    a_2 = activation(z_2)

    z_3 = a_2 @ w_3 + b_3
    a_3 = activation(z_3)

    return a_3, a_2, a_1

epochs = 20

for _ in range(epochs):    
    a_3, a_2, a_1 = forward(X_train, (w_1, b_1, w_2, b_2, w_3, b_3))
    out_test, _, _ = forward(X_test, (w_1, b_1, w_2, b_2, w_3, b_3))
    l = loss(y_train, a_3)
    dl_da_3 = dloss(y_train, a_3) # 2000 x 1
    print(dl_da_3.shape)
    #da_3_dz_3 = dactivation()
    test_losses.append(np.mean(loss(y_test, out_test)))

