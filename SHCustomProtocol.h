#ifndef __SHCUSTOMPROTOCOL_H__
#define __SHCUSTOMPROTOCOL_H__

#include <Arduino.h>

#include <Servo.h>





class SHCustomProtocol {
private:

public:

	/*
	CUSTOM PROTOCOL CLASS
	SEE https://github.com/zegreatclan/SimHub/wiki/Custom-Arduino-hardware-support

	GENERAL RULES :
		- ALWAYS BACKUP THIS FILE, reinstalling/updating SimHub would overwrite it with the default version.
		- Read data AS FAST AS POSSIBLE in the read function
		- NEVER block the arduino (using delay for instance)
		- Make sure the data read in "read()" function READS ALL THE DATA from the serial port matching the custom protocol definition
		- Idle function is called hundreds of times per second, never use it for slow code, arduino performances would fall
		- If you use library suspending interrupts make sure to use it only in the "read" function when ALL data has been read from the serial port.
			It is the only interrupt safe place

	COMMON FUNCTIONS :
		- FlowSerialReadStringUntil('\n')
			Read the incoming data up to the end (\n) won't be included
		- FlowSerialReadStringUntil(';')
			Read the incoming data up to the separator (;) separator won't be included
		- FlowSerialDebugPrintLn(string)
			Send a debug message to simhub which will display in the log panel and log file (only use it when debugging, it would slow down arduino in run conditions)

	*/

	// Called when starting the arduino (setup method in main sketch)
	
	Servo servo1;  // create servo object to control a servo
	Servo servo2;  // create servo object to control a servo
	int Acc; // g forces from game
	int angle; //output angle of servo
	float GFloat;
    int GFint;
	
	void setup() {
		
		servo1.attach(9);  // attaches the servo on pin 9 to the servo object
		servo2.attach(10);  // attaches the servo on pin 10 to the servo object
		
	}

	// Called when new data is coming from computer
	void read() {
		// EXAMPLE 1 - read the whole message and sent it back to simhub as debug message
		// Protocol formula can be set in simhub to anything, it will just echo it
		// -------------------------------------------------------
		String message = FlowSerialReadStringUntil('\n');
		FlowSerialDebugPrintLn("Message_received: " + message);
		
		Acc = message.toInt(); //write G forces to integer
		String  Gforce = getValue(message,';',0);
		GFloat = Gforce.toFloat();
		GFint = GFloat * 100;
		//read games states
		String GamePaused = getValue(message,';',1);
		String GameRunning = getValue(message,';',2);
		//return states for debugging purposes
		FlowSerialDebugPrintLn("Game Paused: " + GamePaused);
		FlowSerialDebugPrintLn("Game Running: " + GameRunning);
		
		//maps servo angle to g forces, but only when in cockpit
		if(GamePaused == "0" and GameRunning == "1"){
			angle = map(GFint,-1500,3000,0,180);	
		}
		else{
			angle = 0;	
		}
		//write ouput to servo's
		servo1.write(angle);
		servo2.write(angle);
		//return values for debugging purposes
		FlowSerialDebugPrintLn("Gforce value: " + String(GFloat));
		FlowSerialDebugPrintLn("Motor Angle: " + String(angle));
	
			
	
		/*
		// -------------------------------------------------------
		// EXAMPLE 2 - reads speed and gear from the message
		// Protocol formula must be set in simhub to
		// format([DataCorePlugin.GameData.NewData.SpeedKmh],'0') + ';' + isnull([DataCorePlugin.GameData.NewData.Gear],'N')
		// -------------------------------------------------------

		int speed = FlowSerialReadStringUntil(';').toInt();
		String gear = FlowSerialReadStringUntil('\n');

		FlowSerialDebugPrintLn("Speed : " + String(speed));
		FlowSerialDebugPrintLn("Gear : " + gear);
		*/
	}

	// Called once per arduino loop, timing can't be predicted, 
	// but it's called between each command sent to the arduino
	void loop() {
		//FlowSerialDebugPrintLn("cycletest");
	
		

	}


	// Called once between each byte read on arduino,
	// THIS IS A CRITICAL PATH :
	// AVOID ANY TIME CONSUMING ROUTINES !!!
	// PREFER READ OR LOOP METHOS AS MUCH AS POSSIBLE
	// AVOID ANY INTERRUPTS DISABLE (serial data would be lost!!!)
	void idle() {
	}
	
//stackoverflow.com/questions/9072320/split-string-into-string-array  //function to split string into values
String getValue(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length()-1;

  for(int i=0; i<=maxIndex && found<=index; i++){
    if(data.charAt(i)==separator || i==maxIndex){
        found++;
        strIndex[0] = strIndex[1]+1;
        strIndex[1] = (i == maxIndex) ? i+1 : i;
    }
  }

  return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
}
};

#endif