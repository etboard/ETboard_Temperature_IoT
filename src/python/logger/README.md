### 참고 소스
http://www.steves-internet-guide.com/simple-python-mqtt-topic-logger/

### 개발 환경 구축
install miniconda
conda create -n py310 python=3.10
conda activate py310

### 테스트
G:
cd G:\src\git\ETboard_Temperature_IoT\src\python\mqtt-data-logger
python mqtt-data-logger.py -b broker.hivemq.com -p 1883 -t 96:EA:E8/et/smpl/tele/sensor -n data-logger


### pyinstaller
패키지 폴더를 지정하지 않으면 paho를 찾지 못함
pyinstaller mqtt-data-logger.py -F -p C:\Users\mrbr\.conda\envs\py310\Lib\site-packages

### 실행
dist\mqtt-data-logger -b broker.hivemq.com -p 1883 -t 96:EA:E8/et/smpl/tele/sensor -n data-logger
또는
run 96:EA:E8
