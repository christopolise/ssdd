# Seven Segment Display Display

_This project is an emulator for the firmware that will run on the Seven Segment Display Display. The SSDD is a grid of 48X18 seven segment digits. The emulator uses ncurses to simulate the display and all of the software on it._

Components
----------

For the hardware build, visit [this link](https://www.instructables.com/7-Segment-Display-Array/) which has detailed instructions, Arduino sketches, and Gerber files to quickly fab the project.


|Library|Description|
|:-------|:--------|
|ssdd_display|Generates an ASCII grid equivalent to the physical display and allows various methods for drawing to them|
|pong|Classic arcade game that illustrates functionality of the display|
|_snake (coming soon)_|Classic arcade game that involves a two-dimensional snake and a lot of skill| 

Compile/Run
-----------

`ssdd` depends upon the `ncurses.h` library. If using Ubuntu 20.04 (or any other recent Debian-based distro), you can check to

```bash
$ dpkg -l '*ncurses*' | grep '^ii'
```
If `ncurses` is installed, several packages will be displayed as the output. If `ncurses` is not installed, try:
```bash
$ sudo apt install libncurses5 libncurses5-dev
```
The package can then be compiled and run with:
```bash
$ gcc -o ssdd *.c -lncurses && ./ssdd
```

Game Instructions
-----------------
**Pong**

To play `pong` use the `w` and `s` to manuever the paddle up and down respectively.

**Snake**
_Coming Soon_

