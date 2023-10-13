__author__ = 'Markus Kreitzer'
from pathlib import Path
import sys
import os.path
import matplotlib.dates as dates
from datetime import datetime
import dateutil.parser
import matplotlib.pyplot as plt
import pandas as pd


def plot_sensor_data(df, image_filename=None):
    # df.plot(x='date', y='ratio', x_compat=True)
    df.plot(x='created_at', y='ratio', x_compat=True)
    plt.title(filename)
    # plt.gca().xaxis.set_major_locator(dates.DayLocator())
    # plt.gca().xaxis.set_major_formatter(dates.DateFormatter('%d\n\n%a'))
    # plt.gca().invert_xaxis()
    # plt.gcf().autofmt_xdate(rotation=0, ha="center")
    if image_filename:
        plt.savefig(image_filename)
    else:
        plt.show()

#df.plot(x='date', y='ratio', x_compat=True)
df.plot(x_compat=True)
#df.plot.hexbin(x='period_high', y='period_low')
plt.title(filename)
# plt.gca().xaxis.set_major_locator(dates.DayLocator())
# plt.gca().xaxis.set_major_formatter(dates.DateFormatter('%d\n\n%a'))
# plt.gca().invert_xaxis()
# plt.gcf().autofmt_xdate(rotation=0, ha="center")
# plt.savefig('img/' + os.path.splitext(filename)[0]+'.png')
plt.show()


if __name__ == '__main__':
    filename = Path(sys.argv[1]).resolve()
    df = pd.read_csv(filename, parse_dates=True)
    df.set_index('created_at')
    image_filename = Path('img') / (filename.stem + '.png')
    plot_sensor_data(df, image_filename)

