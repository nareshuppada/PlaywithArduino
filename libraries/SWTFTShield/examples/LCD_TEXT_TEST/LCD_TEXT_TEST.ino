

#include <Adafruit_GFX.h>    // Core graphics library
#include "SWTFT.h" // Hardware-specific library


// Assign human-readable names to some common 16-bit color values:
#define	BLACK   0x0000
#define	BLUE    0x001F
#define	RED     0xF800
#define	GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

SWTFT tft;
int col=0;

void setup(void) 
{
  tft.reset();
  uint16_t identifier = tft.readID();
  tft.begin(identifier);
 }

void loop(void) 
 {
    testText();
    delay(1000000);
 }

unsigned long testText() 
{
  tft.fillScreen(BLACK);  //LCD BACKGROUND COLOR
  unsigned long start = micros();
  tft.setCursor(0, 30);
  
  tft.setTextSize(4);
  tft.setTextColor(WHITE);
  tft.println("  WELCOME ");
  tft.setTextSize(2);
  tft.print("");
  tft.setTextSize(4);
  tft.println("    TO");
  tft.println("");
  
  tft.setTextColor(RED);  tft.setTextSize(3);
  tft.println("3DPRINTRONICS");
  tft.setTextColor(YELLOW); tft.setTextSize(2);
  tft.println("____________________");
  
  tft.setTextColor(GREEN);
  tft.setTextSize(2);
  tft.println(" THIS IS A LCD TEST");
  tft.println("");
  
  tft.setTextColor(BLUE); tft.setTextSize(2);
    tft.println(" ADD YOUR NAME HERE");       //TYPE YOUR NAME HERE AND GET STARTED
  tft.println("____________________");
   return micros() - start;
}


