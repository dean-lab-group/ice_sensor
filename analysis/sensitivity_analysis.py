import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from SALib.sample import saltelli
from SALib.analyze import sobol

# Assume a simple model for demonstration
def model(capacitance):
    return 1 if capacitance > 50 else 0  # Assume a threshold model for demonstration

# Load your data
data = pd.read_csv('your_data.csv')  # replace 'your_data.csv' with your data file

# Define the problem
problem = {
    'num_vars': 1,
    'names': ['capacitance'],
    'bounds': [[data['capacitance'].min(), data['capacitance'].max()]]
}

# Generate samples
param_values = saltelli.sample(problem, 1000)  # 1000 is the number of samples, adjust as needed

# Run the model
Y = np.array([model(capacitance) for capacitance in param_values])

# Perform the sensitivity analysis
Si = sobol.analyze(problem, Y, print_to_console=True)

# Plotting the results
fig, ax = plt.subplots(1, figsize=(10, 7))
ax.set_axis_off()
table_data = []
columns = ['Sobol Index', 'Value']
table_data.append(['First Order', Si['S1'][0]])
table_data.append(['Total Order', Si['ST'][0]])
ax.table(cellText=table_data, colLabels=columns, cellLoc = 'center', loc='center')
plt.title('Sobol Sensitivity Analysis')
plt.savefig('sobol_analysis.png')
plt.show()
