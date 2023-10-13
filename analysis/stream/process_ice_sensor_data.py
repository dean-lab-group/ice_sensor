import sys, re, json, requests, os
from pprint import pprint
import requests
import logging
import requests

from requests.adapters import HTTPAdapter
from requests.packages.urllib3.util.retry import Retry

logging.basicConfig(level=logging.DEBUG)

s = requests.Session()

retries = Retry(total=50000, backoff_factor=0.1) #, status_forcelist=[ 502, 503, 504 ])

s.mount('http://', HTTPAdapter(max_retries=retries))

#s.get("http://httpstat.us/503")


filename = 'data/ice_sensor_run_with_retry.csv'


params = (
    ('access_token', '79fd76b30720ad97bdf46d77d552aa2585ed0be2'),
)

response = s.get('https://api.particle.io/v1/devices/1c002a001247353236343033/events', params=params, stream=True)

def uniquify(path):
    filename, extension = os.path.splitext(path)
    counter = 0

    while os.path.exists(path):
        path = "%s_%0.2d%s" % (filename, counter, extension)
        counter += 1

    return path


with open(uniquify(filename), 'a') as fh:
    fh.write("period_high, period_low, ratio, date\n")
    for line in response.iter_lines(decode_unicode=True):
        x = re.match(r'data:\s+(\{.+)', line)
        if x:
            y = json.loads(x.group(1))
            print(", ".join([y['data'], y['published_at']])+'\n')
            fh.write(", ".join([y['data'], y['published_at']])+'\n')
            fh.flush()
