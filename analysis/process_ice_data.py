import sys, re, json, requests, os
from pprint import pprint
import requests

filename = 'ice_sensor_run.csv'


params = (
    ('access_token', '79fd76b30720ad97bdf46d77d552aa2585ed0be2'),
)

response = requests.get('https://api.particle.io/v1/devices/1c002a001247353236343033/events', params=params, stream=True)

def uniquify(path):
    filename, extension = os.path.splitext(path)
    counter = 0

    while os.path.exists(path):
        path = "%s_%0.2d%s" % (filename, counter, extension)
        counter += 1

    return path

with open(uniquify(filename), 'a') as fh:
    fh.write("period_high, period_low, ratio, date")
    for line in response.iter_lines(decode_unicode=True):
        x = re.match(r'data:\s+(\{.+)', line)
        if x:
            y = json.loads(x.group(1))
            print(", ".join([y['data'], y['published_at']])+'\n')
            fh.write(", ".join([y['data'], y['published_at']])+'\n')
            fh.flush()
