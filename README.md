# SimHubCustomForBeltTension

Place file in "C:\Program Files (x86)\SimHub\_Addons\Arduino\DisplayClientV2\" folder

Use following method https://github.com/SHWotever/SimHub/wiki/Custom-Arduino-hardware-support 
formula for serial data as follows: 
format([AccelerationSurge],'') + ';' + format([DataCorePlugin.GamePaused],'') + ';' + format([DataCorePlugin.GameRunning],'')
