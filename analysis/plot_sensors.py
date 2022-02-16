__author__ = 'Markus Kreitzer'
import sys
import os.path

import matplotlib.dates as dates
from datetime import datetime

import dateutil.parser
import matplotlib.pyplot as plt
import pandas as pd
dtypes = ['float', 'datetime']

filename = sys.argv[1]


columns = ['ratio', 'date']
df = pd.read_csv(filename, parse_dates=True, names=columns)
df.set_index('date')
#df.plot(x='date', y='ratio', x_compat=True)
df.plot(x_compat=True)
plt.title(filename)
# plt.gca().xaxis.set_major_locator(dates.DayLocator())
# plt.gca().xaxis.set_major_formatter(dates.DateFormatter('%d\n\n%a'))
# plt.gca().invert_xaxis()
# plt.gcf().autofmt_xdate(rotation=0, ha="center")
plt.savefig('img/' + os.path.splitext(filename)[0]+'.png')
