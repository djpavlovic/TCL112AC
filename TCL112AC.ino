#include <IRremoteInt.h>
#include <IRremote.h>

int recvPin = 2; //receive pin on pin 2as coocking hacks, not used in this
int IRledPin =  3;      // IR emitter LED connected to digital pin 3
int buttonPin1 = 4;     // "Send" push-button connected to digital pin 4
int buttonPin2 = 5;     // "Receive" push-button connected to digital pin 5
int blueLedPin =  6;    // Blue LED connected to digital pin 6
int orangeLedPin =  7;  // Orange LED connected to digital pin 7
int buttonState1 = 0;  //storing button state

int khz = 38; // 38kHz carrier frequency for the NEC protocol

//IRrecv irrecv(recvPin);//not used
IRsend irsend;

void setup()   {
  // Initialize the Orange LED pin as an output
  pinMode(orangeLedPin, OUTPUT);
  // Initialize the Orange LED pin as an output
  pinMode(blueLedPin, OUTPUT);
  // Initialize the "Send" push-button pin as an input
  pinMode(buttonPin1, INPUT);
  // Initialize the "Receive" push-button pin as an input
  pinMode(buttonPin2, INPUT);

  // Set uart baudrate
  Serial.begin(9600);
}

void loop()   {
  // Read the state of the "Send" push-button value
  buttonState1 = digitalRead(buttonPin1);

  if (buttonState1 == HIGH) {
    Serial.println("Sending IR signal");
    digitalWrite(orangeLedPin, HIGH);
    delay(200);
    //sending code
    SendIRCode();
    digitalWrite(orangeLedPin, LOW);


    delay(5000);  // wait 5 seconds to resend the code
    Serial.println("5 secs passed");
    digitalWrite(blueLedPin, HIGH);
    delay(200);
    //sending code
    SendOffCode();
    digitalWrite(blueLedPin, LOW);
    delay(5000);  // wait 5 seconds to resend the code
    Serial.println("5 secs passed");

  }
}


void SendIRCode() {
  //sending 19c cool
  unsigned int  irSignal[] = {3100, 1550, 600, 1000, 550, 1050, 550, 250, 550, 300, 550, 250, 550, 1050, 550, 300, 500, 300, 550, 1050, 550, 1000, 600, 250, 550, 1050, 550, 250, 600, 250, 500, 1100, 550, 1050, 500, 300, 550, 1050, 500, 1050, 600, 250, 550, 250, 550, 1050, 550, 300, 550, 250, 550, 1050, 550, 300, 500, 300, 550, 300, 550, 250, 550, 300, 550, 250, 550, 300, 550, 300, 500, 300, 550, 300, 500, 300, 550, 300, 500, 300, 550, 300, 550, 250, 550, 300, 550, 250, 550, 1050, 550, 300, 500, 300, 550, 1050, 500, 300, 550, 300, 550, 1050, 500, 1050, 600, 250, 500, 300, 600, 250, 550, 250, 550, 300, 500, 300, 550, 300, 550, 250, 550, 1050, 550, 1050, 550, 300, 500, 300, 550, 300, 550, 250, 550, 300, 550, 1050, 500, 300, 550, 300, 500, 300, 550, 300, 500, 300, 550, 300, 550, 250, 550, 300, 550, 250, 550, 300, 550, 250, 550, 300, 550, 300, 500, 300, 550, 300, 500, 300, 550, 300, 550, 250, 550, 300, 500, 300, 550, 300, 500, 300, 550, 300, 500, 300, 550, 300, 500, 300, 550, 300, 550, 250, 600, 250, 500, 300, 550, 300, 550, 250, 550, 300, 500, 300, 550, 300, 550, 300, 500, 300, 550, 1050, 500, 300, 600, 1000, 550, 300, 550, 1050, 500, 300, 600, 250, 500, 1050, 550, 1050, 550}; // TCL112AC FFFFFEAC
  irsend.sendRaw(irSignal, sizeof(irSignal) / sizeof(irSignal[0]), khz);

}


void SendOffCode() {
  //off signal
  unsigned int Signal_0_0[] = {2900, 1800, 405, 1125, 405, 1125, 405, 405, 405, 405, 405, 405, 405, 1125, 405, 405, 405, 405, 405, 1125, 405, 1125, 405, 405, 405, 1125, 405, 405, 405, 405, 405, 1125, 405, 1125, 405, 405, 405, 1125, 405, 1125, 405, 405, 405, 405, 405, 1125, 405, 405, 405, 405, 405, 1125, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 1125, 405, 405, 405, 405, 405, 1125, 405, 1125, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 1125, 405, 405, 405, 1125, 405, 1125, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 1125, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 1125, 405, 1125, 405, 1125, 405, 1125, 405, 405, 405, 405, 405, 405, 405, 1125, 405, 1125, 405}; //AnalysIR Batch Export (IRremote) - RAW
  irsend.sendRaw(Signal_0_0, sizeof(Signal_0_0) / sizeof(Signal_0_0[0]), khz);

}
