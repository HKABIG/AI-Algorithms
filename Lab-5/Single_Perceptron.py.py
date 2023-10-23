import numpy as np
import matplotlib.pyplot as plt

# Define the sign function
def sgn(netvalue):
    return 1 if netvalue > 0 else -1

# Initialize the input matrix X
X = np.array([[1.0, -2.0, 1.5, 0.0],
              [1.0, -0.5, -2.0, -1.5],
              [0.0, 1.0, -1.0, 1.5]])

# Initialize the weight vector w
w = np.array([1.0, -1.0, 0.0, 0.5])

# Initialize the desired output vector d
d = np.array([1, -1, 1], dtype=int)

c = 1.0  # Learning rate as float

net, output = 0.0, 0
error = 1.0  # Initialize the error to a non-zero value

epochs = 0  # To keep track of the epochs
error_history = []  # To store error values for plotting

while error != 0.0:
    error = 0.0
    outputs=[]
    for i in range(3):
        net = 0.0

        # Calculate net
        for j in range(4):
            net += X[i][j] * w[j]

        # Compute output
        output = sgn(net)
        outputs.append(output)
        if output != d[i]:
            for k in range(4):
                w[k] += c * (d[i] - output) * X[i][k]

        error += float(d[i] - output)
        print("Output",w,"Activation",outputs,"Error",error)
        # Store the error for plotting
        error_history.append(error)

    epochs += 1

    # Print updated weight vector and error for each epoch
    print(f"Epoch {epochs}: Updated weight vector: {outputs} Error: {error}")

# Print final weight vector
print(f"Final weight vector: {w}")

# Plot error vs. epochs
plt.plot(error_history)
plt.xlabel("Epoch")
plt.ylabel("Error")
plt.title("Error vs. Epoch")
plt.show()
