/* Receive Incoming USB MIDI by reading data.  This approach
   gives you access to incoming MIDI message data, but requires
   more work to use that data.  For the simpler function-based
   approach, see InputFunctionsBasic and InputFunctionsComplete.

   Use the Arduino Serial Monitor to view the messages
   as Teensy receives them by USB MIDI

   You must select MIDI from the "Tools > USB Type" menu

   This example code is in the public domain.
*/
#include <Control_Surface.h>
 
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
struct MyMIDI_Callbacks : FineGrainedMIDI_Callbacks<MyMIDI_Callbacks> {
  // Note how this ^ name is identical to the argument used here ^
 
  // Function that is called whenever a MIDI Note Off message is received.

 
  // Function that is called whenever a MIDI Note On message is received.
  void onNoteOn(Channel myChannel, uint8_t note, uint8_t velocity, Cable cable) {
      channel = myChannel.getRaw();
      if(channel == 0) {
    myPitch = note;
    myVelocity = velocity;
   
  }
    if(channel == 1) {
    myPitch1 = note;
    myVelocity1 = velocity;
   
  }
       if(channel == 2) {
    myPitch2 = note;
    myVelocity2 = velocity;
   
  }
        if(channel == 3) {
    myPitch3 = note;
    myVelocity3 = velocity;
   
  }
  }
 void onControlChange(Channel channel, uint8_t control, uint8_t value,
                       Cable cable) {
                         
  
    if(control == 65 && value == 127) {
    
    usbMIDI.sendNoteOff(lastPitch3, lastVelocity3, 4);
    usbMIDI.sendNoteOn(myPitch3, myVelocity3, 4);
    lastPitch3 = myPitch3;
    lastVelocity3 = myVelocity3;
  }
  if(control == 65 && value == 0) {
    
    usbMIDI.sendNoteOff(lastPitch3, lastVelocity3, 4);
    usbMIDI.sendNoteOn(myPitch3, myVelocity3, 4);
    lastPitch3 = myPitch3;
    lastVelocity3 = myVelocity3;
  }
    if(control == 67 && value == 127) {
    
    usbMIDI.sendNoteOff(lastPitch2, lastVelocity2, 3);
    usbMIDI.sendNoteOn(myPitch2, myVelocity2, 3);
    lastPitch2 = myPitch2;
    lastVelocity2 = myVelocity2;
  
  }
  if(control == 67 && value == 0) {
    usbMIDI.sendNoteOff(lastPitch2, lastVelocity2, 3);
    usbMIDI.sendNoteOn(myPitch2, myVelocity2, 3);
    lastPitch2 = myPitch2;
    lastVelocity2 = myVelocity2;
  }
      if(control == 65 && value == 127) {
    

    usbMIDI.sendNoteOn(myPitch1, myVelocity1, 2);
      lastPitch1 = myPitch1;
    lastVelocity1 = myVelocity1;
  }
  if(control == 65 && value == 0) {
   
    usbMIDI.sendNoteOff(lastPitch1, lastVelocity1, 2);
   
    
  }
      if(control == 67 && value == 127) {
    

    usbMIDI.sendNoteOn(myPitch, myVelocity, 1);
    lastPitch = myPitch;
    lastVelocity = myVelocity;
  }
  if(control == 67 && value == 0) {
    
  usbMIDI.sendNoteOff(lastPitch,lastVelocity, 1);
   
    
  }

  }
 
} callback;
// Create a new instance of the class `CCPotentiometer`, called `potentiometer`,
// on pin A0, that sends MIDI messages with controller 7 (channel volume)
// on channel 1.
CCPotentiometer potentiometer {
  A0, {MIDI_CC::Modulation_Wheel, CHANNEL_5}
  
};
CCPotentiometer potentiometer1 {
  A0, {MIDI_CC::Modulation_Wheel, CHANNEL_6}
  
}; 

// The filtered value read when potentiometer is at the 0% position
constexpr analog_t minimumValue = 0;
// The filtered value read when potentiometer is at the 100% position
constexpr analog_t maximumValue = 5000;
 
// A mapping function to eliminate the dead zones of the potentiometer:
// Some potentiometers don't output a perfect zero signal when you move them to
// the zero position, they will still output a value of 1 or 2, and the same
// goes for the maximum position.
analog_t mappingFunction(analog_t raw) {
    // make sure that the analog value is between the minimum and maximum
    raw = constrain(raw, minimumValue, maximumValue);
    return map(raw, minimumValue, maximumValue, 0, 16383);
}

void setup() {

    // Add the mapping function to the potentiometer
    potentiometer.map(mappingFunction);
    // Initialize everything
    midi.begin(); 
    midi.setCallbacks(callback); 
    Control_Surface.begin();
}






void loop() {
  // usbMIDI.read() needs to be called rapidly from loop().  When
  // each MIDI messages arrives, it return true.  The message must
  // be fully processed before usbMIDI.read() is called again.
  
  midi.update();
  Control_Surface.loop(); 

  
 
    
  
  }
  
