# QuadF450

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

1. Create symbolic links for executing PlatformIO from anywhere
```
# symbolic links
ln -s ~/.platformio/penv/bin/platformio ~/.local/bin/platformio
ln -s ~/.platformio/penv/bin/pio ~/.local/bin/pio
ln -s ~/.platformio/penv/bin/piodebuggdb ~/.local/bin/piodebuggdb
```

1. Add PlatformIO udev rules to allow PlatformIO access to devices
```
# this will do the thing
curl -fsSL https://raw.githubusercontent.com/platformio/platformio-core/develop/platformio/assets/system/99-platformio-udev.rules | sudo tee /etc/udev/rules.d/99-platformio-udev.rules
```

