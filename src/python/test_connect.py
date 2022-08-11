#!python3
import paho.mqtt.client as mqtt  #import the client1
import time

def on_connect(client, userdata, flags, rc):
    if rc==0:
        client.connected_flag=True #set flag
        print("connected OK")
    else:
        print("Bad connection Returned code=",rc)

mqtt.Client.connected_flag=False#create flag in class
broker="broker.hivemq.com"
client = mqtt.Client("python1xsf")             #create new instance 
client.on_connect=on_connect  #bind call back function
client.loop_start()
print("Connecting to broker ",broker)
client.connect(broker)      #connect to broker
while not client.connected_flag: #wait in loop
    print("In wait loop")
    time.sleep(1)
print("in Main Loop")
client.loop_stop()    #Stop loop
client.disconnect() # disconnect
