import math
import matplotlib.pyplot as plt

def get_factor(factor):
    if factor >= 1:
        return 0
    elif factor == 0:
        return 1
    elif 0 < factor < 1:
        return 1 - factor

# Input
num = int(input("Enter the number to calculate its Fuzzy Set: "))
x = int(input("Total numbers to calculate their membership value: "))

membership = [0.0] * x
mem_values = []

print("Enter the numbers:")
for i in range(x):
    value = int(input())
    mem_values.append(value)

sensitivity_parameter = int(input("Enter the value of Sensitivity Parameter: "))

# Fuzzy Set Calculation
for i in range(x):
    current_value = mem_values[i]
    factor = sensitivity_parameter * (abs(float(num) / max(current_value, num) - float(current_value) / max(current_value, num)))
    membership[i] = get_factor(factor)

# Display Fuzzy Set
print(f"Fuzzy set for {num} will be: {membership}")

# Plot the data using matplotlib
plt.title('Fuzzy Set')
plt.xlabel('Values')
plt.ylabel('Membership')
plt.ylim(0, 1)
plt.plot(mem_values, membership, label='Membership Values', marker='o')
plt.legend()
plt.show()
