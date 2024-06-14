import matplotlib.pyplot as plt
import json

# Define the file name for the runtimes data
RUNTIMES_FILE = 'runtimes.json'

# Load the runtimes data from the JSON file
with open(RUNTIMES_FILE, 'r') as file:
    data = json.load(file)

# Extract matrix sizes and the maximum value for the y-axis
matrix_sizes = data['N']
y_max = data['y_top']

# Create a plot for each method
for method in data['methods']:
    runtimes = method['runtimes']
    label = method['name']
    plt.plot(matrix_sizes, runtimes, label=label)

# Set the labels and title for the plot
plt.xlabel('Size of Matrix - N ')
plt.ylabel('Elapsed Time (s)')
plt.title('Performance')

# Set the limit for the y-axis to make optimized plots more visible
plt.ylim(top=y_max)

# Display the legend to identify each method
plt.legend()

# Show the plot
plt.show()
