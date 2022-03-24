#include <Arduino.h>

// RINGCLOCK
// Orologio analogico a LED RGB da parete 
// Piattaforma: 
//  NODEMCU con EPS12E, 
//  due elettromagneti opzionali con driver a transistori
//  WS2812B anelli a 24 LED
// Funzioni: 
//  Indicazione ora esatta con  NTC da internet o gestione RTC con batteria tampone
//  Gong 
// Credits:
//  
// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// Released under the GPLv3 license to match the rest of the
// Adafruit NeoPixel library

#include <Adafruit_NeoPixel.h>

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN  D2 //Su NONEMCU ESP12 va bene D2=GPIO4
#define ABS(N) (N<0)?-N:N
#define NUMPIXELS 24 // Popular NeoPixel ring size

// When setting up the NeoPixel library, we tell it how many pixels,
// and which pin to use to send signals. Note that for older NeoPixel
// strips you might need to change the third parameter -- see the
// strandtest example for more information on possible values.
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#define DELAYVAL 200 // Time (in milliseconds) to pause between pixels

void Riempi (byte R, byte G, byte B){
    Serial.printf("\nR,G,B= %3i, %3i, %3i",R,G,B);
    for(int i=0; i<NUMPIXELS; i++) { // For each pixel...
        pixels.setPixelColor(i, pixels.Color(R, G, B));
        pixels.show();   // Send the updated pixel colors to the hardware.
        delay(20); // Pause before next pass through loop
    }
}

void Nuance (void){
    static int i=0;
    static byte R,G,B;
    R+=random(8)-4; R %= 128;
    G+=random(8)-4; G %= 128;
    B+=random(8)-4; B %= 128;
    Serial.printf("\nR,G,B= %3i, %3i, %3i",R,G,B);
    i++;
    pixels.setPixelColor(i % NUMPIXELS, pixels.Color(R, G, B));
    pixels.show();   // Send the updated pixel colors to the hardware.
}

void setup() {
    Serial.begin (9600); delay(200);
    // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
    // Any other board, you can remove this part (but no harm leaving it):
    #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
    clock_prescale_set(clock_div_1);
    #endif
    // END of Trinket-specific code.
    Serial.print("Anello LED v.1.0");
    pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
    pixels.clear(); // Set all pixel colors to 'off'd
    randomSeed(1);
}

void loop() {
    // The first NeoPixel in a strand is #0, second is 1, all the way up
    // to the count of pixels minus one.
    static byte livello_R ;
    static byte livello_G ;
    static byte livello_B ;
    // static uint16_t Media;

    livello_R = random(128);
    livello_G = random(16);
    livello_B = random(16);
    Serial.printf("\nR,G,B= %3i, %3i, %3i",livello_R,livello_G,livello_B);
    Riempi(livello_R,livello_G,livello_B);

    livello_R = random(16);
    livello_G = random(128);
    livello_B = random(16);
    Serial.printf("\nR,G,B= %3i, %3i, %3i",livello_R,livello_G,livello_B);
    Riempi(livello_R,livello_G,livello_B);

    livello_R = random(16);
    livello_G = random(16);
    livello_B = random(128);
    Serial.printf("\nR,G,B= %3i, %3i, %3i",livello_R,livello_G,livello_B);
    Riempi(livello_R,livello_G,livello_B);

    Nuance();
    delay(20); // Pause before next pass through loop
}
