@echo off
@cls
@chcp 65001 > nul

@echo ##################################################################################
@echo # ETboard IoT Logger V0.91
@echo # ================================================================================
@echo # HTTP://ET.KETRi.RE.KR   Copyright 2022. KETRi. All rights reserved.
@echo ##################################################################################

if [%1]==[] goto :blank

@echo "Mac address of ETboard " %1
dist\mqtt-data-logger -b broker.hivemq.com -p 1883 -t %1/et/smpl/tele/sensor -n data-logger
@pause

:blank
@echo:
@echo Please run with the mac address of ETboard like as below
@echo run 96:EA:E8
@echo:
@pause
