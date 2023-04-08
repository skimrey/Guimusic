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

int channel;
FilteredAnalog<10,       // Output precision in bits
               1,        // The amount of filtering
               uint16_t, // The integer type for the filter calculations
               analog_t  // The integer type for the upscaled analog values
              >
  analog = A0;
// Create a new instance of the class `CCPotentiometer`, called `potentiometer`,
// on pin A0, that sends MIDI messages with controller 7 (channel volume)
// on channel 1.
CCPotentiometer potentiometer {
  analog.getValue(), {MIDI_CC::Modulation_Wheel, CHANNEL_5}
  
};


// The filtered value read when potentiometer is at the 0% position
constexpr analog_t minimumValue = 0;
// The filtered value read when potentiometer is at the 100% position
constexpr analog_t maximumValue = 8000;
 
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
    Control_Surface.begin();
}






void loop() {
  // usbMIDI.read() needs to be called rapidly from loop().  When
  // each MIDI messages arrives, it return true.  The message must
  // be fully processed before usbMIDI.read() is called again.
  
  midi.update();
  Control_Surface.loop(); 

  
 
    
  
  }
  
