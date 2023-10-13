import pandas as pd
from sklearn.linear_model import LinearRegression
from sklearn.model_selection import train_test_split
import sys

# Read CSV file into a pandas dataframe
filename = sys.argv[1]
if not filename: raise "No filename given"
df = pd.read_csv(filename)

# Calculate Pearson correlation coefficient between temp and ratio columns
column_names = "created_at,entry_id,period_high,period_low,ratio,temp,latitude,longitude,elevation,status".split(",")
df.columns = column_names
corr_coeff = df['field4'].corr(df['field3'], method='pearson')

# Print correlation coefficient
print('Pearson correlation coefficient:', corr_coeff)



# Split the data into training and testing sets
X = df[['field3']] # predictor variable
y = df['field4']    # target variable
train_size = 0.7  # percentage of data used for training
X_train, X_test, y_train, y_test = train_test_split(X, y, train_size=train_size, random_state=42)

# Train a linear regression model on the training data
model = LinearRegression()
model.fit(X_train, y_train)

# Evaluate the model on the testing data
score = model.score(X_test, y_test)
print('R-squared score:', score)

