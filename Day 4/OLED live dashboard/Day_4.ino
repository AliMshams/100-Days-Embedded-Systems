#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display(128, 64, &Wire, -1);

unsigned long lastFpsCalc = 0;
int frames = 0;
int fps = 0;

void setup() {
  Serial.begin(9600);
  
  // check if the screen is connected at address 0x3C
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {   
    Serial.println("OLED not found");
    while (true); // stop here if the screen isn't found
  }
  display.clearDisplay();
  display.display();
}

void loop() {
  int raw = analogRead(A0);           // read the potentiometer value (0 to 1023)

  // scale the pot reading to fit inside the 120-pixel bar width
  long result = map(raw, 0, 1023, 0, 120);

  display.clearDisplay();
  
  // draw the empty bar outline and the filled volume bar
  display.drawRect(4, 40, 120, 10, WHITE);
  display.fillRect(4, 40, result, 10, WHITE);
  
  frames++; // count this frame

  // calculate FPS once every second using millis
  unsigned long now = millis();
  if (now - lastFpsCalc >= 1000) {
    fps = frames;
    frames = 0;
    lastFpsCalc = now;
  }
  
  // draw the FPS counter in the top-left corner
  display.setTextSize(1);       
  display.setTextColor(WHITE);       
  display.setCursor(5, 5); 
  display.print("FPS: ");     
  display.println(fps);

  // draw the volume label above the bar
  display.setTextSize(2);       
  display.setTextColor(WHITE);       
  display.setCursor(5, 20);       
  display.println("Volume:");
  
  // push everything from memory to the physical screen all at once
  display.display();
}