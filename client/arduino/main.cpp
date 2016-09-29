#include <Arduino.h>
#include "libraries/EB_Bluetooth.h"
#include <SoftwareSerial.h>
#include <Wire.h>
#include <DHT.h>

//EB_Bluetooth(RX, TX)
EB_Bluetooth myBluetooth(11, 10);

#define DHTPIN 2
#define DHTTYPE DHT11

// Initialize DHT sensor.
DHT dht(DHTPIN, DHTTYPE);


void print(String message) {
	byte bytes[message.length()];
	message.getBytes(bytes, message.length());
	for (int i = 0; i < message.length(); i++) {
		myBluetooth.print(bytes[i]);
	}
}

void setup() {
	Serial.begin(115200);
	myBluetooth.begin();
	if (myBluetooth.setName("DTH11 Sensor")) {
		Serial.println("Set Bluetooth Name Ok");
	} else {
		Serial.println("Set Bluetooth Name Failed");
	}
	Serial.println("Waiting to be connected");
}

void loop() {
	delay(2000);
//	char dat;
//	if (myBluetooth.available()) {
//		dat = myBluetooth.read();
//		Serial.print(dat);
//	}
//	if (Serial.available()) {
//		dat = Serial.read();
//		myBluetooth.print(dat);
//	}

	// Reading temperature or humidity takes about 250 milliseconds!
	// Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
	float h = dht.readHumidity();
	// Read temperature as Celsius (the default)
	float t = dht.readTemperature();

	// Check if any reads failed and exit early (to try again).
	if (isnan(h) || isnan(t)) {
		print("Failed to read from DHT sensor!");
		return;
	}
	// Compute heat index in Celsius (isFahreheit = false)
	float hic = dht.computeHeatIndex(t, h, false);
	char buffer[10];

	print("H: ");
	print(dtostrf(h,4,2,buffer));
	print("T: ");
	print(dtostrf(t,4,2,buffer));
	print("\t");
	Serial.print("#");
}

