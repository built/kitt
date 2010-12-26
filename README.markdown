KITT
=======

This is my second Teensy project. Teensy is an Atmel-based microcontroller board.

This code will cycle patterns across pins D0-D7 on the Teensy and accept input from a connected computer about what patterns to display.
I put LEDs on those pins, but they could be other kinds of components too.

KITT takes input from the connected console over USB. There are currently 4 commands, one for each mode:

- k - "Knight-Rider" (lights swish back and forth)
- s - step (one light at a time)
- f - follow (step with a group of 3 lights)
- d - demo (lights progress from the ends toward the center and back)

You send commands from your computer's console. For example, here's how to activate "follow" mode:

`echo 'f' > /dev/cu.usbmodem12341`

You can also enter commands interactively from the shell like so:

`cat > /dev/cu.usbmodem12341`

Then you can enter a command character (see above) followed by [enter] and the display will change.

To exit, press Ctrl-D.

Details
=======
I built this for Teensy++ 1.0. You'll need to change the Makefile to accommodate the model of Teensy that you use.


Attribution
=======

This code is based on the example code that comes with the Teensy. 

The USB code was lifted from Ward Cunningham's Txtzyme project: <http://www.google.com/search?q=txtzyme>

