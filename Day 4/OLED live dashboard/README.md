# Day 4: OLED live dashboard

Today I built a live dashboard on an SSD1306 OLED screen using a potentiometer to control a volume bar, along with a real-time frame rate counter.

## What I learned
- **I2C Addressing:** Finding the screen address (usually `0x3C`) using an I2C scanner sketch before running the main display code.
- **The Screen Buffer:** Drawing shapes and text to a hidden memory buffer first, then pushing it to the screen all at once using `display.display()`.
- **Mapping Values:** Using the `map()` function to scale analog inputs into pixel coordinates.

## Steps
1. **Run an I2C Scanner:** First, check that your OLED screen is wired properly and confirm its address shows up in the Serial Monitor.
2. **Dashboard Code:** Upload the main script to drive the bar graph and render the frame rate.

## Files
- `Day_4.ino`

## Wiring
- Connect **SDA** from the OLED to the microcontroller's SDA pin.
- Connect **SCL** from the OLED to the microcontroller's SCL pin.
- Connect **VCC** to 3.3V or 5V (depending on your module) and **GND** to GND.
- Connect the potentiometer middle pin to **A0**, and the outer pins to 5V and GND.
