conda create -n py310 python=3.10
http://www.steves-internet-guide.com/simple-python-mqtt-topic-logger/
MQTT << [96:EA:E8/et/smpl/tele/sensor] {"temperature":30.8,"humidity":51}

conda activate py310
G:
cd G:\src\git\ETboard_Temperature_IoT\src\python\mqtt-data-logger
python mqtt-data-logger.py -b broker.hivemq.com -p 1883 -n clcxid -t 96:EA:E8/et/smpl/tele/sensor -n data-logger
python simple-mqtt-data-logger.py -b broker.hivemq.com -p 1883 -n clcxid -t 96:EA:E8/et/smpl/tele/sensor -n data-logger
