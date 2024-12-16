import matplotlib.pyplot as plt

def sgn(net_value):
    return 1 if net_value > 0 else -1

desired_output = [[1, 0, 0],
                  [0, -1, 0],
                  [0, 0, 1]]

weight_matrix = [[-0.1, 0.15, 0.2],
                 [-0.2, 0.11, 0.17],
                 [0.17, 0.16, 0.11]]

input_matrix = [[0.1, 0.1],
                [0.2, 0.1],
                [0.5, 0.1],
                [0.6, 0.1],
                [0.3, 0.3],
                [0.4, 0.3]]

# Learning Rate
learning_rate = 1
error_list = []

# Augmenting The matrix with a bias factor
for i in range(len(input_matrix)):
    input_matrix[i].append(-1)

k = 1
p = 1
error = 1.0
epoch = 0

while True:
    error = 0  # Reset the error for this training cycle
    for i in range(6):
        net_values = []
        for k in range(3):
            net = 0.0
            for j in range(3):
                net += input_matrix[i][j] * weight_matrix[k][j]
            net_values.append(net)
        
        if max(net_values) < 0:
            max_net_index = net_values.index(min(net_values))
        else:
            max_net_index = net_values.index(max(net_values))
        
        sgn_net = sgn(max(net_values))
        
        # Update weight matrix
        for m in range(3):
            weight_matrix[max_net_index][m] += learning_rate * (desired_output[m][max_net_index] - sgn_net) * input_matrix[m][max_net_index]
        
        error += 0.5 * ((1 - sgn_net) ** 2)
        print("Error", error, "Updated Weight Matrix", weight_matrix)
        error_list.append(error)
    
    epoch += 1
    print(f"Epoch {epoch}: Updated weight matrix: {weight_matrix} Error: {error}")
    
    if error == 0 or epoch >= 100:
        break

plt.plot(error_list)
plt.xlabel("Epoch")
plt.ylabel("Error")
plt.title("Error vs. Epoch")
plt.show()
