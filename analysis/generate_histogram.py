__author__ = 'Markus Kreitzer'
import sys
import matplotlib.pyplot as plt
from pandas import DataFrame

from load_data import load_data

df: DataFrame = load_data(sys.argv[1])
plt.figure()
plt.plot(df.created_at[0:925*2], df.ratio[0:925*2])
plt.axvline(x=925, color='red', linestyle='dotted')
plt.axhline(y=2.5, color='red', linestyle='dotted')
plt.show()
plt.figure()
plt.hist(df.ratio[0:925*2], bins=20)
plt.show()
plt.title(filename)
#df.plot.kde()
# plt.gca().xaxis.set_major_locator(dates.DayLocator())
# plt.gca().xaxis.set_major_formatter(dates.DateFormatter('%d\n\n%a'))
# plt.gca().invert_xaxis()
# plt.gcf().autofmt_xdate(rotation=0, ha="center")
#plt.savefig('img/' + os.path.splitext(filename)[0]+'.png')
