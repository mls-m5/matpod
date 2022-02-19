# matpod

A version of software for the Vorpal hexapod.

## Build

### Install platformio

Install in vscode if you use that or: 
https://platformio.org/install

### Build from command line

cd into directory

copy `matpod_config.h.orig` to `matpod_config.h` and set your wifi configurations

```bash
platformio run
```

### Flash to esp

```bash
platformio run -t upload
```

## Credits

Most of the hardware and project setup is done by [Philip](https://github.com/philsson).
