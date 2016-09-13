#include <Arduino.h>
#include "EB_Bluetooth.h"
#include "SoftwareSerial.h"

//EB_Bluetooth(RX, TX)
EB_Bluetooth myBluetooth(11,10);

void setup()
{
	Serial.begin(115200);
	Serial.println("Dette er en test");
	myBluetooth.begin();
	if(myBluetooth.setName("Torkild Sin")){
		Serial.println("Set Bluetooth Name Ok");
	}else{
		Serial.println("Set Bluetooth Name Failed");
	}
	Serial.println("Waiting to be connected");
}

void loop()
{
	char dat;
	if(myBluetooth.available()){
		dat = myBluetooth.read();
		Serial.print(dat);
	}
	if(Serial.available()){
		dat = Serial.read();
		myBluetooth.print(dat);
	}
}
