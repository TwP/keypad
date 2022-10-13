## Keypad

A neat and tidy little four button keypad has come into my possession. I had two ideas for what to do with it (one practical and one silly); hence, this repository was born. Each project lives in its own branch. This main branch exists merely to introduce the repository and to create some basic building blocks common to both projects.

![](media/keypad.png)

This was a fun little thing to play with, and it brought delight to my week. Hopefully this will bring delight to yours and inspire some creativity and silliness of your own.

### Resources

The Arduino, Gateron switches, and custom PCB all came from the good folks over at [Root Ventures](https://root.vc). Thank you for this fun little keypad.

The Arduino board is a [pro micro](https://deskthority.net/wiki/Arduino_Pro_Micro) with a micro USB connector and built-in AVR programmer. This means that you can plug the board into your computer, fire up the Arduino IDE, and immediately start uploading sketches to the board.

The [keypad.ino](keypad/keypad.ino) sketch in this main branch contains the basic building blocks for the two projects.

### Projects

* [TonerPad](https://github.com/TwP/keypad/tree/tonerpad) - the easy way to order color laser toner
* [KeyDeck](https://github.com/TwP/keypad/tree/keydeck) - an ersatz Elgato Stream Deck with clicky-clacky mechanical keys