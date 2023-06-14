#include <Control_Surface.h>
#include <Arduino_Helpers.h>
#include <AH/Hardware/Button.hpp>
// Instantiate a MIDI over USB interface.
USBMIDI_Interface midi;
byte myPitch;
byte myVelocity;
byte myPitch1;
byte myVelocity1;
byte lastPitch;
byte lastVelocity;
byte lastPitch1;
byte lastVelocity1;
byte lastPitch2;
byte lastVelocity2;
byte lastPitch3;
byte lastVelocity3;
byte myPitch2;
byte myVelocity2;
byte myPitch3;
byte myVelocity3;

int channel;
analog_t raw1 = 0;
analog_t raw2 = 0;
Button pushbutton {1};
Button pushbutton1 {24};
struct MyMIDI_Callbacks : FineGrainedMIDI_Callbacks<MyMIDI_Callbacks> {
void onNoteOn(Channel myChannel, uint8_t note, uint8_t velocity, Cable cable) {
      channel = myChannel.getRaw();
    if(channel == 0) {
    myPitch = note;
    myVelocity = velocity;
    myPitch2 = note;
    myVelocity2 = velocity;
   
  }
    if(channel == 1) {
    myPitch1 = note;
    myVelocity1 = velocity;
    myPitch3 = note;
    myVelocity3 = velocity;
  }


}
} callback;

  CCPotentiometer potentiometer {
  A4, {MIDI_CC::Expression_Controller, CHANNEL_5}
  
};

constexpr analog_t minimumValue = 0;
constexpr analog_t maximumValue = 5000;
analog_t mappingFunction(analog_t raw) {
    // make sure that the analog value is between the minimum and maximum
    raw = constrain(raw, minimumValue, maximumValue);
    return map(raw, minimumValue, maximumValue, 0, 16383);
}

void setup() {
  // put your setup code here, to run once:
potentiometer.map(mappingFunction);
pushbutton.begin();
pushbutton1.begin();
midi.begin(); 
midi.setCallbacks(callback); 
Control_Surface.begin();
}

void loop() {
   // put your main code here, to run repeatedly:
  midi.update();
  Control_Surface.loop();
  pushbutton.update();  
  pushbutton1.update();    
  if (pushbutton.getState() == Button::Rising) {
    usbMIDI.sendNoteOff(lastPitch3, lastVelocity3, 4);
    usbMIDI.sendNoteOn(myPitch3, myVelocity3, 4);
    lastPitch3 = myPitch3;
    lastVelocity3 = myVelocity3;
    usbMIDI.sendNoteOn(myPitch1, myVelocity1, 2);
    lastPitch1 = myPitch1;
    lastVelocity1 = myVelocity1;
  }
  else if (pushbutton.getState() == Button::Falling) {
    usbMIDI.sendNoteOff(lastPitch3, lastVelocity3, 4);
    usbMIDI.sendNoteOn(myPitch3, myVelocity3, 4);
    lastPitch3 = myPitch3;
    lastVelocity3 = myVelocity3;
    usbMIDI.sendNoteOff(lastPitch1, lastVelocity1, 2);
  }
  if (pushbutton1.getState() == Button::Rising) {
    usbMIDI.sendNoteOff(lastPitch2, lastVelocity2, 3);
    usbMIDI.sendNoteOn(myPitch2, myVelocity2, 3);
    lastPitch2 = myPitch2;
    lastVelocity2 = myVelocity2;
    usbMIDI.sendNoteOn(myPitch, myVelocity, 1);
    lastPitch = myPitch;
    lastVelocity = myVelocity;
  }
  else if (pushbutton1.getState() == Button::Falling) {
    usbMIDI.sendNoteOff(lastPitch2, lastVelocity2, 3);
    usbMIDI.sendNoteOn(myPitch2, myVelocity2, 3);
    lastPitch2 = myPitch2;
    lastVelocity2 = myVelocity2;
    usbMIDI.sendNoteOff(lastPitch,lastVelocity, 1);
  }
  }
