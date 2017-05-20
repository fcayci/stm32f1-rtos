# stm32f1-rtos

An example project for running the CMSIS-RTOS2 on an STM32F107-based board (Cortex-M3)
using gnu arm toolchain. Toggles PORTE pins 14 and 15. Depends on the CMSIS-5 library

# Preinstall
* Toolchain - [GNU ARM Toolchain](https://developer.arm.com/open-source/gnu-toolchain/gnu-rm/downloads)
* (Windows only) - [MinGW and MSYS ](http://www.mingw.org/)
* Programmer & Debugger - [STLink](https://github.com/texane/stlink)

# Initialize the CMSIS-5 library
* Run `git submodule init`
* Run `git submodule update`

or

* Clone the project recursively `git clone --recursive https://github.com/fcayci/stm32f1-rtos`

# Compile
* Browse into the directory and run `make` to compile.
```
Cleaning...
Building main.c
...
   text	   data	    bss	    dec	    hex	filename
  13608	    232	   6252	  20092	   4e7c	main.elf
Cleaning objects...
Successfully finished...
```

# Program
* Run `make burn` to program the chip.
```
...
Flash written and verified! jolly good!
```

# Debug
* Run `st-util` from one terminal
* Run `make debug` from a second terminal to debug the program.
* You can turn off tui layout with `tui disable` if needed
