# TUI-Mapteract
Code the final project of Tangible User Interfaces at Wellesley (FA2018)
More info on http://frenchmatt.com/TUI-Mapteract/

## Usage
In principle, the circuit for Mapteract is simple. There are 14 LEDs connected to the Arduino with a shift-out circuit (Details: https://www.arduino.cc/en/tutorial/ShiftOut). The 8 flaps function like buttons, wired to the Arduino with a shift-in circuit (Details: https://www.arduino.cc/en/tutorial/ShiftIn). 

The code assumes the following pins (slightly different from tutorials):
#### LED pins
dataPin_leds = 11  
clockPin_leds = 12  
latchPin_leds = 13  

#### Switch pins
dataPin_switches = 9  
clockPin_switches = 7  
latchPin_switches = 8  

All of the code needed can be found in `Final_Project/Final_Project.ino`. Simply updload it to the Arduino on the circuit and you'll be good to go. You can test the shift register circuits using the code in `Shift_in/Shift_in.ino` and `Shift_out/Shift_out.ino`.


Note: the `docs/` folder holds the code for the website. 
