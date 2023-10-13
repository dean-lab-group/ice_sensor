from load_data import load_data
import sys
import matplotlib.pyplot as plt

df = load_data(sys.argv[1])
period_low = df.period_low
period_high = df.period_high
df.temp = 2.03-0.025*df.temp
R1 = 27_380
R2 = 9_200_000
R_L = R1 + R2
R_H = R1
R_eq_1 = R_H / R_L
print(f"Incorrect: {R_eq_1} Ohms")
# R_eq = 1/((400-50)/(2.49-1.65))
R_eq_2 = 0.0024
print(f"Correct: {R_eq_2} Ohms")
ratio_incorrect = (period_low/period_high)
# Add moving average filter
ratio_ma = ratio_incorrect.rolling(window=100).mean()
ratio_ma.plot(title='Incorrect_MA')
ratio_correct = 1.5 + R_eq_2*(period_low/period_high)

# ratio_incorrect.plot(title='Correct')
#ratio_correct.plot(title='Incorrect')
#df.temp.plot(title='Temperature')
plt.show()