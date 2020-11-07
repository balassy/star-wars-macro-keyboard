# Star Wars Macro Keyboard

This is a Star Wars theme inspired device that you can connect to your computer and it will act as a HID keyboard.

![](./photos/external.jpg)

**Features:**
- 5 configurable buttons
- A safety switch with a safety LED
- 2 additional LEDs 
- 3D-printable case

## Getting Started

Coming soon...

## Configuration

In the source code you can define what keycodes will be sent when the buttons are pressed. Check for the `Key definitions` section and update the values for your needs.

Useful sources:
- [Keyboard Modifiers in the Arduino Reference](https://www.arduino.cc/reference/en/language/functions/usb/keyboard/keyboardmodifiers/)
- [usb_hid_keys.h](https://gist.github.com/MightyPork/6da26e382a7ad91b5496ee55fdc73db2)
- [USB HID Usage Table](https://www.freebsddiary.org/APC/usb_hid_usages.php)
- [USB HID Usage Tables specification](https://www.usb.org/sites/default/files/documents/hut1_12v2.pdf)

## Safety Switch

This device acts as a HID keyboard when connected to your computer via USB. If the code is faulty there's a chance that it will send random keycodes to your computer that can make uploading a fixed code impossible.

Safety switch to the rescue! If the safety switch is not pressed the keyboard will not send any keycodes to your computer, but keeps the code running on the Arduino, so you can keep it powered and upload new code to it.

## Wiring

Coming soon...

## 3D-Printable Case

Coming soon...

## Acknowledgements

This project was inspired by [David E. Madison's Building a DIY Stream Deck](https://www.partsnotincluded.com/diy-stream-deck-mini-macro-keyboard/) and [The Smugglers Room](https://www.thesmugglersroom.com/). Thanks both for sharing their passion and knowledge with the community.

## About the author

This project was created by [György Balássy](https://linkedin.com/in/balassy).
