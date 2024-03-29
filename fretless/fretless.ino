#include <Control_Surface.h>
 
// Instantiate a MIDI over USB interface.
USBMIDI_Interface midi;

 
// Create a new instance of the class `CCPotentiometer`, called `potentiometer`,
// on pin A0, that sends MIDI messages with controller 7 (channel volume)
// on channel 1.
PBPotentiometer potentiometer {
A1, CHANNEL_1
};
CCPotentiometer potentiometer1 {
A0, {MIDI_CC::Expression_Controller, CHANNEL_1}
};

PBPotentiometer potentiometer2 {
A3, CHANNEL_2
};
CCPotentiometer potentiometer3 {
A2, {MIDI_CC::Expression_Controller, CHANNEL_2}
};

PBPotentiometer potentiometer4 {
A5, CHANNEL_3
};
CCPotentiometer potentiometer5 {
A4, {MIDI_CC::Expression_Controller, CHANNEL_3}
};

PBPotentiometer potentiometer6 {
A7, CHANNEL_4
};
CCPotentiometer potentiometer7 {
A6, {MIDI_CC::Expression_Controller, CHANNEL_4}
};

void setup() {

    // Add the mapping function to the potentiometer


    // Initialize everything
    midi.begin(); 
    Control_Surface.begin();
}






void loop() {
  // usbMIDI.read() needs to be called rapidly from loop().  When
  // each MIDI messages arrives, it return true.  The message must
  // be fully processed before usbMIDI.read() is called again.
  
  midi.update();


  Control_Surface.loop(); 

  
 
    
  
  }
