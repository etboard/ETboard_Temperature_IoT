@echo off
@chcp 65001
if [%1]==[] goto :blank
@echo "Mac address of ETboard " %1
dist\mqtt-data-logger -b broker.hivemq.com -p 1883 -t %1/et/smpl/tele/sensor -n data-logger
@pause

:blank
@echo "Run with Mac address of ETboard"
@echo "example) run 96:EA:E8"
@pause
