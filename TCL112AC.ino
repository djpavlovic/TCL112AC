/*
* TCL112AC.ino - demonstrates how to send raw data for A/C Unit TCL112AC, 
* or TCL TAC-12CHSA/HCI Using Arduino Uno, and IR Shield found in here: 
* https://www.cooking-hacks.com/documentation/tutorials/control-hvac-infrared-devices-from-the-internet-with-ir-remote/
* Also using this lib: https://github.com/z3t0/Arduino-IRremote
* Version 0.1 1.July 2017
* 
* It is more efficient to use the sendNEC style function to send NEC signals.
* Use of sendRaw_Flash here, serves only as an example of using the function to save SRAM with RAW signals.
* 
* Typical Uses: Allows users to store a significant number of signals in flash for sending, without using up SRAM.
*               This is particularly important for sending RAW AC signal. Typically only one or 2 AC signals could be stored in SRAM using the traditional sendRAW function.
*               With this function a large number of RAW AC signals can be stored & sent from Flash on a standard Arduino, with no material SRAM overhead.
*               For even more Flash & signal storage, consider using a Mega1280/2560 with 128K/256K of available Flash vs the standard of 32k bytes.
*
* SRAM usage: On the Author's dev system the Arduino IDE 1.6.8 reported only 220 SRAM usage & 8,052 bytes of Flash storage used for this sketch.
*             In contrast, only one of the signals below will fit on a standard UNO using the example sendRAW function of IRremote (using SRAM to store the signal)
* reference issues: 
* https://www.analysir.com/blog/2016/04/11/sending-long-ac-signals-flash-irremote/
* https://github.com/z3t0/Arduino-IRremote/issues/480
* https://github.com/djpavlovic/TCL112AC
*/

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

//working
const unsigned int AC_irSignal_19c_Cool[] PROGMEM = {3100, 1550, 600, 1000, 550, 1050, 550, 250, 550, 300, 550, 250, 550, 1050, 550, 300, 500, 300, 550, 1050, 550, 1000, 600, 250, 550, 1050, 550, 250, 600, 250, 500, 1100, 550, 1050, 500, 300, 550, 1050, 500, 1050, 600, 250, 550, 250, 550, 1050, 550, 300, 550, 250, 550, 1050, 550, 300, 500, 300, 550, 300, 550, 250, 550, 300, 550, 250, 550, 300, 550, 300, 500, 300, 550, 300, 500, 300, 550, 300, 500, 300, 550, 300, 550, 250, 550, 300, 550, 250, 550, 1050, 550, 300, 500, 300, 550, 1050, 500, 300, 550, 300, 550, 1050, 500, 1050, 600, 250, 500, 300, 600, 250, 550, 250, 550, 300, 500, 300, 550, 300, 550, 250, 550, 1050, 550, 1050, 550, 300, 500, 300, 550, 300, 550, 250, 550, 300, 550, 1050, 500, 300, 550, 300, 500, 300, 550, 300, 500, 300, 550, 300, 550, 250, 550, 300, 550, 250, 550, 300, 550, 250, 550, 300, 550, 300, 500, 300, 550, 300, 500, 300, 550, 300, 550, 250, 550, 300, 500, 300, 550, 300, 500, 300, 550, 300, 500, 300, 550, 300, 500, 300, 550, 300, 550, 250, 600, 250, 500, 300, 550, 300, 550, 250, 550, 300, 500, 300, 550, 300, 550, 300, 500, 300, 550, 1050, 500, 300, 600, 1000, 550, 300, 550, 1050, 500, 300, 600, 250, 500, 1050, 550, 1050, 550}; // TCL112AC FFFFFEAC
const unsigned int AC_irSignal_off[] PROGMEM = {2900, 1800, 405, 1125, 405, 1125, 405, 405, 405, 405, 405, 405, 405, 1125, 405, 405, 405, 405, 405, 1125, 405, 1125, 405, 405, 405, 1125, 405, 405, 405, 405, 405, 1125, 405, 1125, 405, 405, 405, 1125, 405, 1125, 405, 405, 405, 405, 405, 1125, 405, 405, 405, 405, 405, 1125, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 1125, 405, 405, 405, 405, 405, 1125, 405, 1125, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 1125, 405, 405, 405, 1125, 405, 1125, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 1125, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 405, 1125, 405, 1125, 405, 1125, 405, 1125, 405, 405, 405, 405, 405, 405, 405, 1125, 405, 1125, 405}; //AnalysIR Batch Export (IRremote) - RAW

//testcases
const unsigned int AC_irSignal_auto_mode[] PROGMEM = {3050, 1600, 500, 1050, 600, 1000, 550, 300, 500, 300, 550, 250, 550, 1050, 550, 300, 500, 300, 550, 1050, 550, 1000, 600, 250, 500, 1050, 600, 250, 500, 350, 500, 1050, 550, 1050, 550, 250, 550, 1050, 550, 1000, 550, 300, 550, 300, 500, 1050, 600, 250, 500, 300, 500, 1100, 550, 250, 550, 300, 500, 300, 550, 300, 500, 300, 550, 300, 500, 350, 500, 300, 500, 300, 550, 300, 500, 300, 550, 300, 500, 300, 550, 300, 500, 300, 550, 300, 500, 300, 550, 1050, 500, 300, 550, 300, 500, 1050, 600, 250, 550, 250, 550, 300, 550, 250, 550, 300, 500, 1100, 500, 300, 500, 350, 500, 300, 500, 300, 550, 300, 500, 350, 500, 300, 500, 1100, 550, 250, 550, 300, 500, 300, 550, 300, 500, 300, 550, 300, 500, 300, 550, 300, 500, 300, 550, 300, 500, 300, 550, 250, 550, 300, 500, 350, 500, 300, 550, 300, 500, 300, 500, 350, 500, 300, 500, 350, 500, 300, 550, 300, 500, 300, 550, 300, 500, 300, 550, 300, 500, 300, 550, 300, 500, 300, 550, 250, 550, 300, 500, 300, 550, 300, 550, 300, 500, 300, 500, 350, 500, 300, 500, 350, 500, 300, 500, 350, 500, 300, 500, 350, 500, 300, 550, 300, 500, 1050, 550, 300, 500, 300, 550, 1050, 550, 300, 500, 300, 500, 1100, 550, 250, 500}; // TCL112AC FFFFFF6D
const unsigned int AC_irSignal_cold24c[] PROGMEM = {3100, 1550, 550, 1050, 600, 1000, 500, 300, 550, 300, 550, 250, 550, 1050, 550, 250, 550, 300, 500, 1050, 600, 1000, 600, 250, 500, 1050, 600, 250, 500, 300, 550, 1050, 500, 1100, 550, 250, 550, 1050, 550, 1000, 550, 300, 500, 300, 550, 1050, 550, 250, 550, 300, 500, 1050, 600, 250, 500, 350, 500, 300, 500, 300, 550, 300, 500, 300, 550, 300, 500, 300, 550, 250, 550, 300, 550, 300, 500, 300, 500, 350, 500, 300, 550, 300, 500, 300, 550, 300, 500, 1050, 550, 300, 500, 300, 550, 1050, 550, 300, 500, 300, 500, 1100, 550, 1000, 500, 350, 500, 300, 550, 300, 500, 300, 550, 300, 500, 300, 550, 1050, 550, 1000, 600, 1000, 550, 250, 550, 300, 500, 350, 500, 300, 500, 350, 500, 300, 550, 250, 550, 300, 550, 1050, 550, 1000, 600, 1000, 550, 250, 550, 300, 500, 300, 550, 300, 500, 300, 550, 300, 500, 300, 550, 300, 500, 300, 550, 250, 550, 300, 550, 250, 550, 300, 500, 350, 500, 300, 500, 350, 500, 300, 550, 300, 500, 300, 550, 300, 500, 300, 550, 250, 550, 300, 550, 250, 550, 300, 500, 300, 550, 300, 500, 300, 550, 300, 500, 300, 550, 300, 500, 300, 550, 300, 500, 1050, 550, 1050, 550, 1000, 600, 250, 500, 1050, 550, 1050, 600, 1000, 600, 1000, 550, 1000, 600}; // TCL112AC FFFFFE20
const unsigned int AC_irSignal_cworm30c[] PROGMEM = {3100, 1550, 550, 1050, 600, 1000, 500, 300, 550, 300, 500, 300, 550, 1050, 550, 250, 550, 300, 550, 1000, 600, 1000, 600, 250, 500, 1050, 600, 250, 500, 300, 550, 1050, 550, 1050, 550, 250, 550, 1050, 550, 1000, 550, 300, 500, 300, 550, 1050, 550, 250, 550, 300, 500, 1050, 600, 250, 500, 300, 550, 300, 550, 250, 550, 300, 500, 300, 550, 300, 500, 300, 500, 300, 550, 300, 550, 300, 500, 300, 550, 300, 500, 300, 550, 300, 500, 300, 550, 300, 500, 1050, 550, 300, 500, 300, 550, 1050, 550, 300, 500, 300, 500, 1100, 550, 250, 550, 250, 550, 300, 550, 250, 550, 300, 550, 250, 550, 300, 500, 1050, 600, 250, 500, 300, 550, 300, 500, 300, 550, 300, 500, 300, 550, 300, 500, 350, 500, 300, 500, 300, 550, 300, 500, 300, 550, 300, 500, 300, 550, 300, 500, 300, 550, 300, 500, 300, 500, 300, 550, 300, 500, 350, 500, 300, 500, 350, 500, 300, 550, 300, 500, 300, 550, 300, 500, 300, 550, 250, 550, 300, 550, 250, 550, 300, 500, 300, 550, 300, 500, 300, 550, 300, 500, 300, 550, 300, 500, 300, 550, 300, 500, 350, 500, 300, 500, 300, 550, 300, 500, 300, 550, 300, 500, 300, 550, 1050, 500, 1050, 600, 250, 500, 1100, 550, 1000, 550, 1050, 550, 250, 550, 300, 500}; // TCL112AC FFFFFF23
const unsigned int AC_irSignal_cworm30cextra[] PROGMEM = {3050, 1600, 550, 1050, 550, 1000, 550, 300, 500, 350, 500, 300, 500, 1050, 550, 300, 500, 300, 550, 1050, 550, 1000, 600, 250, 550, 1000, 600, 250, 550, 300, 500, 1050, 550, 1050, 550, 250, 550, 1050, 600, 1000, 500, 300, 550, 300, 500, 1050, 600, 250, 550, 250, 550, 1050, 600, 250, 500, 300, 550, 250, 550, 300, 550, 250, 550, 300, 500, 300, 550, 300, 500, 300, 550, 300, 500, 350, 500, 300, 500, 350, 500, 300, 550, 300, 500, 300, 550, 300, 500, 1050, 550, 300, 500, 300, 550, 1050, 550, 300, 500, 300, 500, 1100, 550, 250, 550, 300, 500, 300, 550, 300, 500, 300, 550, 250, 550, 300, 500, 1100, 550, 250, 550, 250, 550, 300, 550, 250, 550, 300, 550, 250, 550, 300, 500, 350, 500, 300, 500, 350, 500, 300, 500, 350, 500, 300, 500, 350, 500, 300, 550, 300, 500, 300, 550, 300, 500, 300, 550, 250, 550, 300, 550, 250, 550, 300, 500, 300, 600, 250, 500, 300, 550, 300, 550, 300, 500, 300, 500, 350, 500, 300, 500, 350, 500, 300, 500, 350, 500, 300, 550, 300, 500, 300, 550, 300, 500, 300, 550, 250, 550, 300, 500, 300, 550, 300, 550, 250, 550, 300, 500, 300, 550, 300, 500, 1050, 550, 1050, 600, 250, 500, 1100, 550, 1000, 550, 1050, 550, 250, 550, 300, 500}; // TCL112AC FFFFFF23
const unsigned int AC_irSignal_teardrop[] PROGMEM = {3050, 1600, 500, 1050, 600, 1000, 550, 300, 500, 300, 550, 250, 550, 1050, 550, 300, 500, 300, 550, 1050, 550, 1000, 600, 250, 500, 1050, 600, 250, 500, 350, 500, 1050, 550, 1050, 550, 250, 550, 1050, 550, 1000, 550, 300, 500, 350, 500, 1050, 600, 250, 500, 300, 500, 1100, 550, 250, 550, 300, 500, 300, 550, 300, 500, 300, 550, 300, 500, 350, 500, 300, 500, 350, 500, 300, 500, 300, 550, 300, 500, 300, 550, 300, 500, 300, 550, 300, 500, 300, 550, 1050, 550, 250, 550, 300, 550, 1000, 600, 250, 550, 250, 550, 300, 500, 1100, 500, 300, 550, 250, 550, 300, 550, 250, 550, 300, 500, 350, 500, 300, 500, 350, 500, 300, 500, 1100, 550, 250, 550, 300, 500, 300, 550, 300, 500, 350, 500, 300, 500, 300, 550, 300, 500, 300, 550, 300, 500, 300, 550, 300, 500, 300, 550, 300, 500, 300, 500, 300, 550, 300, 550, 300, 500, 300, 550, 300, 500, 300, 550, 300, 500, 300, 550, 300, 500, 300, 550, 300, 500, 300, 550, 300, 500, 300, 550, 300, 500, 300, 550, 250, 550, 300, 500, 300, 550, 300, 550, 300, 500, 300, 500, 350, 500, 300, 500, 350, 500, 300, 500, 350, 500, 300, 550, 1050, 550, 1000, 550, 1050, 550, 250, 550, 300, 500, 350, 500, 300, 500, 1050, 600, 1000, 600}; // TCL112AC FFFFFE3C
const unsigned int AC_irSignal_onFan[] PROGMEM = {3050, 1600, 500, 1100, 550, 1000, 550, 300, 500, 300, 550, 300, 500, 1050, 550, 300, 500, 300, 550, 1050, 550, 1000, 600, 250, 500, 1050, 600, 250, 500, 350, 500, 1050, 550, 1050, 550, 250, 550, 1050, 550, 1000, 550, 300, 500, 350, 500, 1050, 600, 250, 500, 300, 550, 1050, 550, 250, 550, 300, 500, 300, 500, 350, 500, 300, 550, 300, 500, 300, 550, 300, 500, 300, 550, 300, 500, 300, 550, 300, 500, 300, 550, 300, 500, 300, 550, 300, 500, 300, 550, 1050, 550, 250, 550, 300, 500, 1050, 600, 250, 500, 300, 550, 1050, 600, 1000, 500, 1050, 600, 250, 500, 300, 550, 300, 550, 250, 550, 300, 500, 300, 550, 300, 500, 300, 500, 1100, 550, 250, 550, 300, 500, 300, 550, 300, 500, 1050, 550, 300, 500, 1050, 550, 300, 500, 300, 550, 300, 500, 350, 500, 300, 500, 350, 500, 300, 550, 300, 500, 300, 550, 300, 500, 300, 550, 300, 500, 300, 500, 300, 550, 300, 550, 250, 550, 300, 550, 250, 550, 300, 500, 300, 550, 300, 500, 350, 500, 300, 500, 350, 500, 300, 500, 350, 500, 300, 500, 350, 500, 300, 550, 250, 550, 300, 500, 300, 550, 300, 550, 250, 550, 300, 500, 300, 550, 1050, 600, 1000, 550, 250, 550, 1050, 550, 1050, 550, 250, 550, 250, 550, 1050, 550, 1050, 550}; // TCL112AC FFFFFE4C

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
  Serial.println("Setup Finished");
}

void loop()   {
  // Read the state of the "Send" push-button value
  buttonState1 = digitalRead(buttonPin1);
  if (buttonState1 == HIGH) {

    //START
    digitalWrite(orangeLedPin, HIGH);//some indications that it is being sent
    Serial.println("AC_irSignal_onFan");
    sendRAW_Flash(AC_irSignal_onFan, sizeof(AC_irSignal_onFan) / sizeof(int), khz); //code for sending
    delay(10000); //a good idea to have gaps between signals
    digitalWrite(orangeLedPin, LOW);//some indications that it is being sent
    //END

    //START
    digitalWrite(orangeLedPin, HIGH);//some indications that it is being sent
    Serial.println("AC_irSignal_teardrop");
    sendRAW_Flash(AC_irSignal_teardrop, sizeof(AC_irSignal_teardrop) / sizeof(int), khz); //code for sending
    delay(10000); //a good idea to have gaps between signals
    digitalWrite(orangeLedPin, LOW);//some indications that it is being sent
    //END

    //START
    digitalWrite(orangeLedPin, HIGH);//some indications that it is being sent
    Serial.println("AC_irSignal_cworm30cextra");
    sendRAW_Flash(AC_irSignal_cworm30cextra, sizeof(AC_irSignal_cworm30cextra) / sizeof(int), khz); //code for sending
    delay(10000); //a good idea to have gaps between signals
    digitalWrite(orangeLedPin, LOW);//some indications that it is being sent
    //END

    //START
    digitalWrite(orangeLedPin, HIGH);//some indications that it is being sent
    Serial.println("AC_irSignal_cworm30c");
    sendRAW_Flash(AC_irSignal_cworm30c, sizeof(AC_irSignal_cworm30c) / sizeof(int), khz); //code for sending
    delay(10000); //a good idea to have gaps between signals
    digitalWrite(orangeLedPin, LOW);//some indications that it is being sent
    //END

    //START
    digitalWrite(orangeLedPin, HIGH);//some indications that it is being sent
    Serial.println("AC_irSignal_19c_Cool");
    sendRAW_Flash(AC_irSignal_19c_Cool, sizeof(AC_irSignal_19c_Cool) / sizeof(int), khz); //code for sending
    delay(10000); //a good idea to have gaps between signals
    digitalWrite(orangeLedPin, LOW);//some indications that it is being sent
    //END



    //START
    digitalWrite(orangeLedPin, HIGH);//some indications that it is being sent
    Serial.println("AC_irSignal_auto_mode");
    sendRAW_Flash(AC_irSignal_auto_mode, sizeof(AC_irSignal_auto_mode) / sizeof(int), khz); //code for sending
    delay(10000); //a good idea to have gaps between signals
    digitalWrite(orangeLedPin, LOW);//some indications that it is being sent
    //END

    //START
    digitalWrite(orangeLedPin, HIGH);//some indications that it is being sent
    Serial.println("AC_irSignal_cold24c");
    sendRAW_Flash(AC_irSignal_cold24c, sizeof(AC_irSignal_cold24c) / sizeof(int), khz); //code for sending
    delay(10000); //a good idea to have gaps between signals
    digitalWrite(orangeLedPin, LOW);//some indications that it is being sent
    //END

    //START
    digitalWrite(orangeLedPin, HIGH);//some indications that it is being sent
    Serial.println("AC_irSignal_off");
    sendRAW_Flash(AC_irSignal_off, sizeof(AC_irSignal_off) / sizeof(int), khz); //code for sending
    delay(10000); //a good idea to have gaps between signals
    digitalWrite(orangeLedPin, LOW);//some indications that it is being sent
    //END
  }
}


void sendRAW_Flash(const unsigned int * signalArray, unsigned int signalLength, unsigned char carrierFreq) {
  Serial.println("Sending IR signal");
  irsend.enableIROut(carrierFreq); //initialise the carrier frequency for each signal to be sent

  for (unsigned int i = 0; i < signalLength; i++) {
    //tmp=pgm_read_word_near(&signalArray[i]);
    // tmp=cleanPanasonic(tmp); //not needed
    if (i & 1) irsend.space(pgm_read_word_near(&signalArray[i]));
    else irsend.mark(pgm_read_word_near(&signalArray[i]));
  }
  irsend.space(1);//make sure IR is turned off at end of signal

}
