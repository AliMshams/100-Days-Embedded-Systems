# Day 2: Interrupt Driven Button Press Counter

Moving away from polling (`digitalRead` inside `loop`) to hardware interrupts and robust software debouncing for precise event tracking.

##  What I Learned
- **Hardware Interrupts (`attachInterrupt`):** Triggering an immediate function call (`onEdge`) the moment a physical signal changes state, freeing up the main loop to run without delays.
- **The `volatile` Keyword:** Ensuring variables shared between normal code and Interrupt Service Routines are read fresh from memory instead of cached registers.
- **Interrupt Debouncing:** Implementing a time-delta check using `millis()` directly inside an ISR to filter out mechanical button bounce noise.

##  Files
- `Day_2.ino` - The complete source code.

##  Circuit Setup & Wiring
- **Push Button:** Connect one side of the button to **Digital Pin 2** (Interrupt capable) and the other side to **GND**.
- **Internal Pull-Up:** Code utilizes `INPUT_PULLUP`, so no external resistors are required.
