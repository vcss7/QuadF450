# QuadF450

## Component List

|    Component      | Manufacturer | Model Name   | Comm Interface | Operating Voltage |
|-------------------|--------------|--------------|----------------|-------------------|
| Microcontroller   | Teensy       | 4.1          | Multi          | 3.3V              |
| Display           | UCTRONICS    | UTC-602602   | I2C            | 3.3V to 5V        |
| Orientation       | Adafruit     | BNO055       | I2C            | 3.3V to 5V        |
| Press/Humid/Temp  | Adafruit     | BME280       | I2C            | 3.3V to 5V        |
| GPS               | Adafruit     | Ultimate GPS | UART           | 3.3V to 5V        |


## Installation

### PlatformIO Core

More information about installing and configuring PlatformIO Core can be found
on the [PlatformIO Installation Documentation](https://docs.platformio.org/en/latest/core/installation/index.html).

Here's the TLDR:

1. Install PlatformIO Core with script
```
# download script
curl -fsSL -o get-platformio.py https://raw.githubusercontent.com/platformio/platformio-core-installer/master/get-platformio.py

# run script
python3 get-platformio.py
```

2. Create symbolic links for executing PlatformIO from anywhere
```
# symbolic links
ln -s ~/.platformio/penv/bin/platformio ~/.local/bin/platformio
ln -s ~/.platformio/penv/bin/pio ~/.local/bin/pio
ln -s ~/.platformio/penv/bin/piodebuggdb ~/.local/bin/piodebuggdb
```

3. Add PlatformIO device management rules to allow PlatformIO access to devices
```
# this will do the thing
curl -fsSL https://raw.githubusercontent.com/platformio/platformio-core/develop/platformio/assets/system/99-platformio-udev.rules | sudo tee /etc/udev/rules.d/99-platformio-udev.rules
```

## Usage

Generate `compile_commands.json` to let clangd find header files
```
# generate compile_commands.json
pio run -t compiledb
```

To upload the firmware, connect the microcontroller and run:
```
# builds and uploads firmware for any enviornment in  platformio.ini file
pio run --target upload

# or, for only one enviornment in the file
pio run -e teensy41 -t upload
```

## Contributions
Before commiting to this repository, make sure the code being submitted complies
with:
    - MISRA 2012 coding guidelines
    - Doxygen documentation standards

### MISRA C 2012
To comply with thos guidelines, `cppcheck` CLI tool can be used along with its
`misra.py` addon. Here is a guide on how to use `cppcheck` to comply to MISRA C
2012 coding style guidelines: (link)[https://deepwiki.com/danmar/cppcheck/6.1-misra-compliance-checking]

Download `cppcheck`
```
# debian based linux distribution
sudo apt install cppcheck

# arch based linux distribution
sudo pacman -S cppcheck
```

Find where the `misra.py` addon is located in the system
```
sudo find / -name "misra.py" 2>/dev/null
```

Create a `cppcheck` dump file
```
cppcheck --dump file.c
```

Run `cppcheck` with the `misra.py` addon
```
cppcheck --addon=/<path>/<to>/<cppcheck>/<addon>/misra.py file.c.dump
```

Obtain a copy of the `misra_c_2012.txt` text file which contains all rules
outlined in the MISRA C 2012 coding guildlines for better output.

### Doxygen Documentation Standard


