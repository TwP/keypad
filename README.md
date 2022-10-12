## KeyDeck

The [Stream Deck](https://www.elgato.com/en/stream-deck) is a very nice piece of hardware, but what it could really use are some tactile clicky keys. Enter the **KeyDeck** - an Arduino powered mechanical keypad for one button automations on your Mac.

![](media/keypad.png)

Each key supports a short press and a long press (about half a second) for a total of eight actions that can be performed. The **KeyDeck** emits keyboard events that are received [Hammerspoon](https://www.hammerspoon.org) which then takes the appropriate action. With tools like [Home Control](https://pvieito.com/2022/01/automate-homekit-with-homecontrol) you can even trigger home automation scenes and actions.

### How it Works

The Arduino keypad emits key-press events which are received by Hammerspoon running on the Mac. The key-press events are hard coded in the Arduino sketch, and the actions taken are controlled by the Hammerspoon configuration.

A short press of the first button (the one on the left) emits the following key combination: `⌘ ⌥ ⌃ 1`. The combination of _command_ `⌘` + _option_ `⌥` + _control_ `⌃` is used in the [`hammerspoon/init.lua`](hammerspoon/init.lua) script for dispatching the correct action. The numbers `1` through `8` are used for our eight possible actions. Each button uses it's corresponding number for the short press and then adds four for the long press. For example, the second button uses the number `2` for the short press and the number `6` for the long press.

Hammerspoon is where actions are dispatched based on the key-press. It can launch applications, adjust the volume, rearrange windows on screen - pretty much anything can be automated. Except for HomeKit. Apple (in their infinite wisdom) has not exposed a HomeKit API to MacOS. Another developer out on the internet decided to fix this oversight and so they created "Home Control" - a little menubar app that exposes HomeKit devices. The nice thing about "Home Control" is that it provides an `x-callback-url` scheme. Hammerspoon can create and send these URLs, and therefore, control HomeKit devices. Thank you Pedro José Pereira Vieito.

### Arduino

The board on the keypad is an [Arduino pro micro](https://deskthority.net/wiki/Arduino_Pro_Micro) with a micro USB connector and built-in AVR programmer. This means that you can plug the board into your computer, fire up the Arduino IDE, and immediately start uploading sketches to the board.

The [keypad.ino](keypad/keypad.ino) sketch in this main branch contains the basic building blocks for the two projects.
