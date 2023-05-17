
#include <Control_Surface.h>
 
// Instantiate a MIDI over USB interface.
USBMIDI_Interface midi;


int channel;
analog_t raw1 = 0;
analog_t raw2 = 0;

 
// Create a new instance of the class `CCPotentiometer`, called `potentiometer`,
// on pin A0, that sends MIDI messages with controller 7 (channel volume)
// on channel 1.
CCPotentiometer potentiometer {
  A0, {MIDI_CC::Modulation_Wheel, CHANNEL_5}
};

CCPotentiometer potentiometer1 {
A1, {MIDI_CC::Expression_Controller, CHANNEL_5}
};

// The filtered value read when potentiometer is at the 0% position
constexpr analog_t minimumValue = 3300;
// The filtered value read when potentiometer is at the 100% position
constexpr analog_t maximumValue = 16383;

// The filtered value read when potentiometer is at the 0% position
constexpr analog_t minimumValue1 = 500;
// The filtered value read when potentiometer is at the 100% position
constexpr analog_t maximumValue1 = 16383;
 
// A mapping function to eliminate the dead zones of the potentiometer:
// Some potentiometers don't output a perfect zero signal when you move them to
// the zero position, they will still output a value of 1 or 2, and the same
// goes for the maximum position.
analog_t mappingFunction(analog_t raw) {
    // make sure that the analog value is between the minimum and maximum
    raw = constrain(raw, minimumValue, maximumValue);
    return map(raw, minimumValue, maximumValue, 0, 16383);
}

analog_t mappingFunction1(analog_t raw) {
    // make sure that the analog value is between the minimum and maximum
    raw = constrain(raw, minimumValue1, maximumValue1);
    return map(raw, minimumValue1, maximumValue1, 0, 16383);
}

void setup() {

    // Add the mapping function to the potentiometer
    potentiometer.map(mappingFunction);
    potentiometer1.map(mappingFunction1);
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
