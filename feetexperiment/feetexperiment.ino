#include <Control_Surface.h>
#include <Arduino_Helpers.h>
#include <AH/Hardware/Button.hpp>

// Instantiate a MIDI over USB interface.
USBMIDI_Interface midi;
byte lastPitch;
byte lastVelocity;
byte lastPitch1;
byte lastVelocity1;
byte lastPitch2;
byte lastVelocity2;
byte lastPitch3;
byte lastVelocity3;
uint16_t cur_pitchbend1 = 0;
uint16_t cur_pitchbend2 = 0;
uint16_t cur_pitchbend3 = 0;
uint16_t cur_pitchbend4 = 0;
int bendchannel;

int channel;
Button pushbutton {1};
Button pushbutton1 {24};

bool buttonPressed1 = false;
bool buttonPressed2 = false;

struct MyMIDI_Callbacks : FineGrainedMIDI_Callbacks<MyMIDI_Callbacks> {
  void onNoteOn(Channel myChannel, uint8_t note, uint8_t velocity, Cable cable) {
    channel = myChannel.getRaw();
    lastPitch = note;
    lastVelocity = velocity;
    lastPitch1 = note;
    lastVelocity1 = velocity;
  }

  void onPitchBend(Channel inChannel, uint16_t inValue, Cable cable1) {
    bendchannel = inChannel.getRaw();
    if (bendchannel == 0) {
      cur_pitchbend1 = inValue / 2;
    }
    if (bendchannel == 1) {
      cur_pitchbend2 = inValue / 2;
    }
    if (bendchannel == 2) {
      cur_pitchbend3 = inValue / 2;
    }
    if (bendchannel == 3) {
      cur_pitchbend4 = inValue / 2;
    }
  }
} callback;

void setup() {
  pushbutton.begin();
  pushbutton1.begin();
  midi.begin();
  midi.setCallbacks(callback);
  Control_Surface.begin();
}

void loop() {
   pushbutton.update();
  pushbutton1.update();
  midi.update();
  Control_Surface.loop();


if (pushbutton.getState() == Button::Rising) {
  usbMIDI.sendNoteOn(lastPitch, lastVelocity, 1);
  buttonPressed1 = true;
} else if (pushbutton.getState() == Button::Falling) {
  buttonPressed1 = false;
  usbMIDI.sendNoteOff(lastPitch, lastVelocity, 1);
}

if (pushbutton1.getState() == Button::Rising) {
  usbMIDI.sendNoteOn(lastPitch1, lastVelocity1, 2);
  buttonPressed2 = true;
} else if (pushbutton1.getState() == Button::Falling) {
  usbMIDI.sendNoteOff(lastPitch1, lastVelocity1, 2);
  buttonPressed2 = false;
}


  // Send pitch bend messages
  if (buttonPressed1) {
    if (channel == 0) {
      usbMIDI.sendPitchBend(cur_pitchbend1, 1);
    }
    if (channel == 1) {
      usbMIDI.sendPitchBend(cur_pitchbend2, 1);
    }
    if (channel == 2) {
      usbMIDI.sendPitchBend(cur_pitchbend3, 1);
    }
    if (channel == 3) {
      usbMIDI.sendPitchBend(cur_pitchbend4, 1);
    }
  }
 
}
