# YaoYaoBang

Alternative software for inexpensive LED-shaker-sticks based on the STC89C52RC processor


# Prerequisites

## USB to UART adapter

The processor is programmed via its UART interface, so you will need some kind of USB to UART adapter.

In my case, I already had an Arduino UNO, so I used its built-in serial like so:

![Wiring_Steckplatine](https://user-images.githubusercontent.com/2080713/141676486-e077129f-cab6-4244-ad3c-b57d224f1ba3.png)

To prevent the microcontroller on the Arduino itself from interfering, I wired the `RESET` line to `GND`, thus effectively disabling it.
You can also just remove the microcontroller from the Arduino board, or upload a sketch that Pins 0 and 1 to input and then goes into an infinite loop.

## Compiler

In order to compile the code in this reposity for the STC89C52RC, you need the [Small Device C Compiler](https://de.wikipedia.org/wiki/Small_Device_C_Compiler) (SDCC).
On Arch Linux, it is available from the Community repo directly.

## stcgal

[stcgal](https://github.com/grigorig/stcgal) is a simple tool used to flash the compiled code onto the processor. 
It is available via PIP or the AUR on Arch.

Alternatively, you should be able to use the official software from STC ([http://www.stcmicro.com/rjxz.html](http://www.stcmicro.com/rjxz.html)), but I didn't thoroughly test that.


# Building / Flashing

Open a terminal in the root folder of this repo and run

```sh
$ make build
```

to compile the code and then

```sh
$ make flash PORT=/dev/ttyACM0
```

to flash it onto your device.
You may have to replace the `/dev/ttyACM0` with the path that corresponds to the virtual COM port that your USB serial adapter created.
