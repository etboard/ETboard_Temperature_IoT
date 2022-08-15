@echo off
@chcp 65001
if [%1]==[] goto :blank
@echo "이티보드 맥어드레스는 " %1
dist\mqtt-data-logger -b broker.hivemq.com -p 1883 -t %1/et/smpl/tele/sensor -n data-logger
@pause
@exit

:blank
@echo "이티보드 맥어드레스를 입력하세요"
@echo "예) run 96:EA:E8"
@pause
