## TonerPad

What model of toner cartridge does your printer take? First, you have to know your printer model, and then you have to dig through the manufacturer's website trying to find useful information buried amongst popups and marketing materials. Invariably, when you do find the proper toner cartridges, you forget to write this information down. And then you have to repeat the whole process again in seven months when the next toner cartridge reports that it is empty.

You need a **TonerPad** - a dedicated keyboard that will pull up toner information for your color laser printer.

![](media/tonerpad.png)

### Usage

Plug the **TonerPad** into a free USB port on your Mac computer. Press the button corresponding to the color of toner that you need. The product page will open up a web browser. If you want the high yield toner cartridge, then long press the button (about half a second), and you will be taken to the high capacity product page.

That's it! Nothing could be easier!

### Materials

The Arduino, Gateron switches, and custom PCB all came from the good folks over at [Root Ventures](https://root.vc). Thank you for this fun little keypad.

The colored keycaps are from [WASD](https://www.wasdkeyboards.com). I chose the "row 3" [blank keycaps](https://www.wasdkeyboards.com/row-3-size-1x1-cherry-mx-keycap.html) since those have the least angle.

The Arduino board is a [pro micro](https://deskthority.net/wiki/Arduino_Pro_Micro) with a micro USB connector and built-in AVR programmer. This means that you can plug the board into your computer, fire up the Arduino IDE, and immediately start uploading sketches to the board.

The [keypad.ino](keypad/keypad.ino) sketch contains the full sourcecode for this project. You can change the toner URLs in the sketch to those for your own color laser printer.
