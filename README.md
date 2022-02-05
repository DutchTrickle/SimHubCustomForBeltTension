# SimHubCustomForBeltTension

Place .h file in "C:\Program Files (x86)\SimHub\_Addons\Arduino\DisplayClientV2\" folder

Use following method https://github.com/SHWotever/SimHub/wiki/Custom-Arduino-hardware-support 

formula for serial data as follows: 

format([AccelerationSurge],'') + ';' + format([DataCorePlugin.GamePaused],'') + ';' + format([DataCorePlugin.GameRunning],'')


Servo's used: https://www.tinytronics.nl/shop/en/mechanics-and-actuators/motors/servomotors/td-8130mg-waterproof-digital-servo-30kg 

STL files for mount on 80x40 aluminium extrusion profile.

See in use here: https://www.youtube.com/watch?v=L4EWORSBIkU 

How to wire:
![Wiring Scheme](https://user-images.githubusercontent.com/17800628/152642218-f0a80a50-8eee-4607-be6a-57bb9d99189c.png)
