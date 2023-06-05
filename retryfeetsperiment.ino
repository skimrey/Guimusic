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
byte activenote1 = 0;
byte activenote2 = 0;
byte activenote3 = 0;
byte activenote4 = 0;
int pressed1 = 0;
int pressed2 = 0;
int channel;
int bendchannel;
int counter = 0;
uint16_t cur_pitchbend1 = 0;
uint16_t cur_pitchbend2 = 0;
uint16_t cur_pitchbend3 = 0;
uint16_t cur_pitchbend4 = 0;
uint16_t las_pitchbend1 = 0;
uint16_t las_pitchbend2 = 0;
uint16_t las_pitchbend3 = 0;
uint16_t las_pitchbend4 = 0;
uint8_t cur_express1 = 0;
uint8_t cur_express2 = 0;
uint8_t cur_express3 = 0;
uint8_t cur_express4 = 0;
int expresschannel;
uint8_t las_express1 = 0;
uint8_t las_express2 = 0;
uint8_t las_express3 = 0;
uint8_t las_express4 = 0;
analog_t raw1 = 0;
analog_t raw2 = 0;
Button pushbutton {1};
Button pushbutton1 {24};
struct MyMIDI_Callbacks : FineGrainedMIDI_Callbacks<MyMIDI_Callbacks> {

void onControlChange(Channel thisChannel, uint8_t controller, uint8_t value, Cable cable) {
     expresschannel = thisChannel.getRaw();
     if(controller == 11) {
    if (expresschannel == 0) {
      cur_express1 = value;
    }
    if (expresschannel == 1) {
      cur_express2 = value;
    }
    if (expresschannel == 2) {
      cur_express3 = value;
    }
    if (expresschannel == 3) {
      cur_express4 = value;
    }
  }
}
void onNoteOn(Channel myChannel, uint8_t note, uint8_t velocity, Cable cable) {
      channel = myChannel.getRaw();



    if(note == 52 && activenote4 == 0 && activenote3 == 0 && activenote2 == 0){
    myPitch = note;
    myVelocity = velocity;
    } else if(note == 59 && activenote3 == 0 && activenote2 == 0){
    myPitch = note;
    myVelocity = velocity;
    } else if(note == 66 && activenote1 == 0){
    myPitch = note;
    myVelocity = velocity;
    } else if(note == 73){
    myPitch = note;
    myVelocity = velocity;
    }    
    

    if(note == 73 && activenote1 == 0 && activenote2 == 0 && activenote3 == 0){
    myPitch1 = note;
    myVelocity1 = velocity;
    } else if(note == 66 && activenote1 == 0 && activenote2 == 0){
    myPitch1 = note;
    myVelocity1 = velocity;
    } else if(note == 59 && activenote1 == 0){
    myPitch1 = note;
    myVelocity1 = velocity;
    } else if(note == 52){
    myPitch1 = note;
    myVelocity1 = velocity;
    }

    if(note == 52){
      activenote1 = 1;
    }
    if(note == 59){
      activenote2 = 1;
    }
    if(note == 66){
      activenote3 = 1;
    }
    if(note == 73){
      activenote4 = 1;
    }
    

}
void onNoteOff(Channel myChannel, uint8_t note, uint8_t velocity, Cable cable) {
      channel = myChannel.getRaw();

    if(note == 52){
      activenote1 = 0;
    }
    else if(note == 59){
      activenote2 = 0;
    }
    else if(note == 66){
      activenote3 = 0;
    }
    else if(note == 73){
      activenote4 = 0;
    }
    
    
    if(note == 52 && activenote2 == 1){
      myPitch1 = 59;
    }
    else if(note == 52 && activenote3 == 1){
      myPitch1 = 66;
    }
    else if(note == 52 && activenote4 == 1){
      myPitch = 73;
    }
    
    else if(note == 59 && activenote3 == 1){
      myPitch1 = 66;
    }
    else if(note == 59 && activenote4 == 1){
      myPitch1 = 73;
    }

    else if(note == 66 && activenote4 == 1){
      myPitch1 = 73;
    }
    
    
    if(note == 73 && activenote3 == 1){
      myPitch = 66;
    }
    else if(note == 73 && activenote2 == 1){
    myPitch = 59;
    }
    else if(note == 73 && activenote1 == 1){
      myPitch = 52;
    }
    else if(note == 66 && activenote2 == 1){
      myPitch = 59;
    }
    else if(note == 66 && activenote1 == 1){
      myPitch = 52;
    }
    else if(note == 59 && activenote1 == 1){
      myPitch = 52;
    }
}
  void onPitchBend(Channel inChannel, uint16_t inValue, Cable cable1) {
    bendchannel = inChannel.getRaw();
    if (bendchannel == 0) {
      cur_pitchbend1 = inValue - 8192;
    }
    if (bendchannel == 1) {
      cur_pitchbend2 = inValue - 8192;
    }
    if (bendchannel == 2) {
      cur_pitchbend3 = inValue - 8192;
    }
    if (bendchannel == 3) {
      cur_pitchbend4 = inValue - 8192;
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
    usbMIDI.sendNoteOn(myPitch1, myVelocity1, 4);
    lastPitch3 = myPitch1;
    lastVelocity3 = myVelocity1;
    usbMIDI.sendNoteOn(myPitch1, myVelocity1, 2);
    lastPitch1 = myPitch1;
    lastVelocity1 = myVelocity1;
    pressed1 = 1;
  }
  else if (pushbutton.getState() == Button::Falling) {
    usbMIDI.sendNoteOff(lastPitch3, lastVelocity3, 4);
    usbMIDI.sendNoteOn(myPitch1, myVelocity1, 4);
    lastPitch3 = myPitch1;
    lastVelocity3 = myVelocity1;
    usbMIDI.sendNoteOff(lastPitch1, lastVelocity1, 2);
    pressed1 = 0;
  }
  if (pushbutton1.getState() == Button::Rising) {
    usbMIDI.sendNoteOff(lastPitch2, lastVelocity2, 3);
    usbMIDI.sendNoteOn(myPitch, myVelocity, 3);
    lastPitch2 = myPitch;
    lastVelocity2 = myVelocity;
    usbMIDI.sendNoteOn(myPitch, myVelocity, 1);
    lastPitch = myPitch;
    lastVelocity = myVelocity;
    pressed2 = 1;
  }
  else if (pushbutton1.getState() == Button::Falling) {
    usbMIDI.sendNoteOff(lastPitch2, lastVelocity2, 3);
    usbMIDI.sendNoteOn(myPitch, myVelocity, 3);
    lastPitch2 = myPitch;
    lastVelocity2 = myVelocity;
    usbMIDI.sendNoteOff(lastPitch,lastVelocity, 1);
    pressed2 = 0;
  }

  if(pressed1 == 1 ) {
    if (myPitch1 == 73 && las_pitchbend4 != cur_pitchbend4) {
      usbMIDI.sendPitchBend(cur_pitchbend4, 2);
      las_pitchbend4 = cur_pitchbend4;
    }
    else if (myPitch1 == 66 && las_pitchbend3 != cur_pitchbend3) {
      usbMIDI.sendPitchBend(cur_pitchbend3, 2);
      las_pitchbend3 = cur_pitchbend3;
    }
    else if (myPitch1 == 59 && las_pitchbend2 != cur_pitchbend2) {
      usbMIDI.sendPitchBend(cur_pitchbend2, 2);
      las_pitchbend2 = cur_pitchbend2;
    }
    else if(myPitch1 == 52 && las_pitchbend1 != cur_pitchbend1) {
      usbMIDI.sendPitchBend(cur_pitchbend1, 2);
      las_pitchbend1 = cur_pitchbend1;
    }
    
    
    
  }
    if(pressed2 == 1 ) {
    if (myPitch == 73 && las_pitchbend4 != cur_pitchbend4 ) {
      usbMIDI.sendPitchBend(cur_pitchbend4, 3);
      las_pitchbend4 = cur_pitchbend4;
    }
    else if (myPitch == 66 && las_pitchbend3 != cur_pitchbend3 ) {
      usbMIDI.sendPitchBend(cur_pitchbend3, 3);
      las_pitchbend3 = cur_pitchbend3;
    }
    else if (myPitch == 59 && las_pitchbend2 != cur_pitchbend2 ) {
      usbMIDI.sendPitchBend(cur_pitchbend2, 3);
      las_pitchbend2 = cur_pitchbend2;
    }
    else if(myPitch == 52 && las_pitchbend1 != cur_pitchbend1){
      usbMIDI.sendPitchBend(cur_pitchbend1, 3);
      las_pitchbend1 = cur_pitchbend1;
    }
    
    
    
    }
    if(pressed2 == 1 ) {
    if (myPitch == 52 && las_express1 != cur_express1) {
      usbMIDI.sendControlChange(11, cur_express1, 3);
      las_express1 = cur_express1;
    }
    else if (myPitch == 59 && las_express2 != cur_express2) {
      usbMIDI.sendControlChange(11, cur_express2, 3);
      las_express2 = cur_express2;
    }
    else if (myPitch == 66 && las_express3 != cur_express3) {      
      usbMIDI.sendControlChange(11, cur_express3, 3);
      las_express3 = cur_express3;
    }
    else if (myPitch == 73 && las_express4 != cur_express4) {
      usbMIDI.sendControlChange(11, cur_express4, 3);
      las_express4 = cur_express4;
    }
   }
       if(pressed1 == 1 ) {
    if (myPitch1 == 52 && las_express1 != cur_express1) {
      usbMIDI.sendControlChange(11, cur_express1, 2);
      las_express1 = cur_express1;
    }
    else if (myPitch1 == 59 && las_express2 != cur_express2) {
      usbMIDI.sendControlChange(11, cur_express2, 2);
      las_express2 = cur_express2;
    }
    else if (myPitch1 == 66 && las_express3 != cur_express3) {
      usbMIDI.sendControlChange(11, cur_express3, 2);
      las_express3 = cur_express3;
    }
    else if (myPitch1 == 73 && las_express4 != cur_express4) {
      usbMIDI.sendControlChange(11, cur_express4, 2);
      las_express4 = cur_express4;
    }
       }
  }
  
  
