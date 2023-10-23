import matplotlib.pyplot as plt

def sgn(netvalue):
    return 1 if netvalue > 0 else -1

d = [[1, 0, 0],
     [0, -1, 0],
     [0, 0, 1]]
W = [[-0.1, 0.15, 0.2],
     [-0.2, 0.11, 0.17],
     [0.17, 0.16, 0.11]]


X = [[0.1, 0.1],
     [0.2, 0.1],
     [0.5, 0.1],
     [0.6, 0.1],
     [0.3, 0.3],
     [0.4, 0.3]]


# Learning Rate
c = 1
error_list = []
# Augmenting The matrix a bias factor
for i in range(len(X)):
    X[i].append(-1)
# print(X)

k=1
p=1
e=1.0
epoch = 0
while True:
    e = 0  # Reset the error for this training cycle
    for i in range(6):
        l = []
        for k in range(3):
            net = 0.0
            # l = []
            for j in range(3):
                net += X[i][j] * W[k][j]
                round(net, 3)
            l.append(net)
            # print(net)
        # print(l)
        if max(l)<0:
            max_net = l.index(min(l))
        else:
            max_net = l.index(max(l))
        sgn_net = sgn(max(l))
        #Update weight matrix
        for m in range(3):
            W[max_net][m] = W[max_net][m] + c *((d[m][max_net] - sgn_net))* X[m][max_net]
        e = 0.5*((1-sgn_net)**2)+ e
        print("Error", e, "Updated Weigh Matrix", W)
        error_list.append(e)
    epoch += 1
    if e == 0 or epoch >= 100:
        break
plt.plot(error_list)
plt.xlabel("Epoch")
plt.ylabel("Error")
plt.title("Error vs. Epoch")
plt.show()

