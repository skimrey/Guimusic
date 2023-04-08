#include <Control_Surface.h>

 
 
USBMIDI_Interface usbmidi;
HardwareSerialMIDI_Interface serialmidi = {Serial1, MIDI_BAUD};
BidirectionalMIDI_PipeFactory<2> pipes;
Transposer<-3, +3> transposer(12);

// Push button on pin 2 to transpose.
IncrementDecrementSelector<transposer.getNumberOfBanks()> selector = {
  transposer,
  {10, 15},
  Wrap::Clamp,
};  



 

// The note numbers corresponding to the buttons in the matrix
const AddressMatrix<5, 15> addresses {{
  {59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73},
  {55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69},
  {50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64},
  {45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59},
  {40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54},
  
}};
const AddressMatrix<5, 15> addresses1 {{
  {60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74},
  {55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69},
  {50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64},
  {45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59},
  {40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54},
  
}};



Bankable::NoteButtonMatrix<5, 15> buttonmatrix {
  transposer,
  { 21, 20, 41, 40, 39 }, // row pins
  { 29, 32, 27, 7, 28, 5, 4, 14, 13, 12, 33, 34, 35, 31, 30 },    // column pins
  addresses,    // address matrix
  CHANNEL_1,    // channel and cable number
};
Bankable::NoteButtonMatrix<5, 15> buttonmatrix1 {
  transposer,
  { 21, 20, 41, 40, 39 }, // row pins
  { 29, 32, 27, 7, 28, 5, 4, 14, 13, 12, 33, 34, 35, 31, 30 },    // column pins
  addresses1,    // address matrix
  CHANNEL_2,    // channel and cable number
};
void setup() {
  Control_Surface | pipes | usbmidi;
  Control_Surface | pipes | serialmidi;
  Control_Surface.begin();
}
 
void loop() {
  Control_Surface.loop();
}
