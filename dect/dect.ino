#define ONBOARD_LED 2
#define RELAY_PIN 7

#include <RCSwitch.h>

int const DURATION = 1100;
RCSwitch mySwitch = RCSwitch();

void setup() {
    Serial.begin(115200);
    mySwitch.enableReceive(27);  	// RF Receiver on interrupt 0 => pin #D2
    mySwitch.enableTransmit(12);
	pinMode(ONBOARD_LED, OUTPUT);
	pinMode(RELAY_PIN, OUTPUT);
	digitalWrite(RELAY_PIN, HIGH);
    Serial.println("=== booted ===");
    mySwitch.send("000000000001010100010001");
}

void loop() {
	if (mySwitch.available() &&
		mySwitch.getReceivedBitlength() == 24) {
     		Serial.println("doorbell recieved");
			tripRelay();
			mySwitch.resetAvailable();
	}
}

void busyLED(byte state) {	
	digitalWrite(ONBOARD_LED, state); 
}

void tripRelay() {
	busyLED(HIGH);
	digitalWrite(7, LOW);
	delay(DURATION);			// Doorbell is ringing
	digitalWrite(7, HIGH);
	delay(DURATION * 2);		// Cooldown
	busyLED(LOW);	
}
