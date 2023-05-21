
#include <Control_Surface.h>
 
// Instantiate a MIDI over USB interface.
USBMIDI_Interface midi;


int channel;
analog_t raw1 = 0;
analog_t raw2 = 0;
analog_t raw3 = 0;
analog_t raw4 = 0;
analog_t raw5 = 0;
analog_t raw6 = 0;
analog_t raw7 = 0;
analog_t raw8 = 0;
int val;
int val1;
int val2;
int val3;
int val4;
int val5;
int val6;
int val7;
int pressed1 = 0;
int pressed2 = 0;
int pressed3 = 0;
int pressed4 = 0;
 
// Create a new instance of the class `CCPotentiometer`, called `potentiometer`,
// on pin A0, that sends MIDI messages with controller 7 (channel volume)
// on channel 1.
CCPotentiometer potentiometer {
  A1, {MIDI_CC::Modulation_Wheel, CHANNEL_1}
};

CCPotentiometer potentiometer1 {
A0, {MIDI_CC::Expression_Controller, CHANNEL_1}
};

CCPotentiometer potentiometer2 {
  A3, {MIDI_CC::Modulation_Wheel, CHANNEL_2}
};

CCPotentiometer potentiometer3 {
A2, {MIDI_CC::Expression_Controller, CHANNEL_2}
};

CCPotentiometer potentiometer4 {
  A5, {MIDI_CC::Modulation_Wheel, CHANNEL_3}
};

CCPotentiometer potentiometer5 {
A4, {MIDI_CC::Expression_Controller, CHANNEL_3}
};

CCPotentiometer potentiometer6 {
  A7, {MIDI_CC::Modulation_Wheel, CHANNEL_4}
};

CCPotentiometer potentiometer7 {
A6, {MIDI_CC::Expression_Controller, CHANNEL_4}
};
// The filtered value read when potentiometer is at the 0% position
constexpr analog_t minimumValue = 0;
// The filtered value read when potentiometer is at the 100% position
constexpr analog_t maximumValue = 16383;

// The filtered value read when potentiometer is at the 0% position
constexpr analog_t minimumValue1 = 0;
// The filtered value read when potentiometer is at the 100% position
constexpr analog_t maximumValue1 = 16383;

// The filtered value read when potentiometer is at the 0% position
constexpr analog_t minimumValue2 = 0;
// The filtered value read when potentiometer is at the 100% position
constexpr analog_t maximumValue2 = 16383;

// The filtered value read when potentiometer is at the 0% position
constexpr analog_t minimumValue3 = 0;
// The filtered value read when potentiometer is at the 100% position
constexpr analog_t maximumValue3 = 16383;

// The filtered value read when potentiometer is at the 0% position
constexpr analog_t minimumValue4 = 0;
// The filtered value read when potentiometer is at the 100% position
constexpr analog_t maximumValue4 = 16383;

// The filtered value read when potentiometer is at the 0% position
constexpr analog_t minimumValue5 = 0;
// The filtered value read when potentiometer is at the 100% position
constexpr analog_t maximumValue5 = 16383;

// The filtered value read when potentiometer is at the 0% position
constexpr analog_t minimumValue6 = 0;
// The filtered value read when potentiometer is at the 100% position
constexpr analog_t maximumValue6 = 16383;

// The filtered value read when potentiometer is at the 0% position
constexpr analog_t minimumValue7 = 0;
// The filtered value read when potentiometer is at the 100% position
constexpr analog_t maximumValue7 = 16383;

 
// A mapping function to eliminate the dead zones of the potentiometer:
// Some potentiometers don't output a perfect zero signal when you move them to
// the zero position, they will still output a value of 1 or 2, and the same
// goes for the maximum position.
analog_t mappingFunction(analog_t raw1) {
    // make sure that the analog value is between the minimum and maximum
    raw1 = constrain(raw1, minimumValue, maximumValue);
    return map(raw1, minimumValue, maximumValue, 0, 16383);
}

analog_t mappingFunction1(analog_t raw2) {
    // make sure that the analog value is between the minimum and maximum
    raw2 = constrain(raw2, minimumValue1, maximumValue1);
    return map(raw2, minimumValue1, maximumValue1, 0, 16383);
}

analog_t mappingFunction2(analog_t raw3) {
    // make sure that the analog value is between the minimum and maximum
    raw3 = constrain(raw3, minimumValue2, maximumValue2);
    return map(raw3, minimumValue2, maximumValue2, 0, 16383);
}

analog_t mappingFunction3(analog_t raw4) {
    // make sure that the analog value is between the minimum and maximum
    raw4 = constrain(raw4, minimumValue3, maximumValue3);
    return map(raw4, minimumValue3, maximumValue3, 0, 16383);
}

analog_t mappingFunction4(analog_t raw5) {
    // make sure that the analog value is between the minimum and maximum
    raw5 = constrain(raw5, minimumValue4, maximumValue4);
    return map(raw5, minimumValue4, maximumValue4, 0, 16383);
}

analog_t mappingFunction5(analog_t raw6) {
    // make sure that the analog value is between the minimum and maximum
    raw6 = constrain(raw6, minimumValue5, maximumValue5);
    return map(raw6, minimumValue5, maximumValue5, 0, 16383);
}

analog_t mappingFunction6(analog_t raw7) {
    // make sure that the analog value is between the minimum and maximum
    raw7 = constrain(raw7, minimumValue6, maximumValue6);
    return map(raw7, minimumValue6, maximumValue6, 0, 16383);
}

analog_t mappingFunction7(analog_t raw8) {
    // make sure that the analog value is between the minimum and maximum
    raw8 = constrain(raw8, minimumValue7, maximumValue7);
    return map(raw8, minimumValue7, maximumValue7, 0, 16383);
}


void setup() {

    // Add the mapping function to the potentiometer
    potentiometer.map(mappingFunction);
    potentiometer1.map(mappingFunction1);
    potentiometer2.map(mappingFunction2);
    potentiometer3.map(mappingFunction3);
    potentiometer4.map(mappingFunction4);
    potentiometer5.map(mappingFunction5);
    potentiometer6.map(mappingFunction6);
    potentiometer7.map(mappingFunction7);

    // Initialize everything
    midi.begin(); 
    Control_Surface.begin();
}






void loop() {
  // usbMIDI.read() needs to be called rapidly from loop().  When
  // each MIDI messages arrives, it return true.  The message must
  // be fully processed before usbMIDI.read() is called again.
  
  midi.update();
  val = analogRead(0);
  val1 = analogRead(1);
  val2 = analogRead(2);
  val3 = analogRead(3);
  val4 = analogRead(4);
  val5 = analogRead(5);
  val6 = analogRead(6);
  val7 = analogRead(7);
  if(pressed1 == 0 && val > 200) {
    usbMIDI.sendNoteOn(60, 66, 1);
    pressed1 = 1;
  }
  if(val < 100 && pressed1 == 1) {
    usbMIDI.sendNoteOff(60,66,1);
    pressed1 = 0;
  }
    if(pressed2 == 0 && val2 > 200) {
    usbMIDI.sendNoteOn(65, 66, 2);
    pressed2 = 1;
  }
  if(val2 < 100 && pressed2 == 1) {
    usbMIDI.sendNoteOff(65,66,2);
    pressed2 = 0;
  }
    if(pressed3 == 0 && val4 > 200) {
    usbMIDI.sendNoteOn(70, 66, 3);
    pressed3 = 1;
  }
  if(val4 < 100 && pressed3 == 1) {
    usbMIDI.sendNoteOff(70,66,3);
    pressed3 = 0;
  }
      if(pressed4 == 0 && val6 > 200) {
    usbMIDI.sendNoteOn(75, 66, 4);
    pressed4 = 1;
  }
  if(val6 < 100 && pressed4 == 1) {
    usbMIDI.sendNoteOff(75,66,4);
    pressed4 = 0;
  }
  Control_Surface.loop(); 

  
 
    
  
  }
