/**********************************
*LED 7-seg 4-digit Display Library*
*     Runtime Counter Example     *
*  by CRC.Mismatch - 20/04/2014   *
**********************************/
// Prepared for common-cathode displays.
#include <LED7Display.h>

#define BRIGHTNESS 200 //How long to show each digit, in microseconds. The bigger this is, higher the brightness.
#define DISP_DELAY 20  //How long between each time something is shown, in milliseconds. As this gets higher, it reduces power consumption at the cost of flickering and less brightness.

const byte outP[] = { 2, 3, 4, 5, 6, 7, 8, 9, 10 }; //Connect the respective anode segments to these pins.
const byte inD[] = { A3, A2, A1, A0 }; //Connect the digit cathodes (from right to left) to these pins.

LED7Display disp = LED7Display(inD, outP);
int counter = 0, hh = 0, mm = 0, ss = 0, tt = 0;

void setup() {
  disp.tick(ON); // Set the HH:MM separator on.
}

void loop() {
  tt = millis() / 1000;
  hh = tt / 3600;
  mm = tt / 60;
  ss = tt % 60;
  if (hh > 0) { // If the run time goes over an hour
    if (counter > (1000 / (DISP_DELAY + (BRIGHTNESS * 4 / 1000)))) {
      disp.tick(); // Tick the separator every second
      counter = 0;
    }
    disp.showTime((hh * 100) + mm); // Show hours and minutes
    counter++;
  } else {  // If we're not over an hour yet
    disp.showTime((mm * 100) + ss); // Show minutes and seconds
  }
  delay(DISP_DELAY);
}
