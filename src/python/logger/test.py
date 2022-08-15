import paho.mqtt.client as mqtt
import json
import os
import time
import sys, getopt,random
import logging
import mlogger as mlogger
import threading
from queue import Queue
from command import command_input
import command
import sys
from datetime import datetime

# current dateTime
now = datetime.now()

# convert to string
date_time_str = now.strftime("%Y-%m-%d %H:%M:%S")
print('DateTime String:', date_time_str)
