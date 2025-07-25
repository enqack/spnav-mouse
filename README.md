# spnav-mouse

A Linux utility that bridges SpaceMouse (3D mouse) input to standard mouse control, allowing you to use your 3D mouse as a regular pointing device.

## Features

- Converts SpaceMouse movements to regular mouse cursor movements
- Supports scrolling using SpaceMouse rotation
- Maps SpaceMouse buttons to left/right mouse clicks
- Configurable sensitivity and deadzone settings
- Optional exclusive device grabbing
- Verbose mode for debugging

## Prerequisites

- Linux operating system
- libspnav (SpaceNav library)
- Development tools (gcc, make)
- Access to `/dev/uinput` (usually requires root permissions or being in the `input` group)

## Installation

```
make && sudo make install # Optional, installs to /usr/local/bin
```

## Usage

Basic usage:
```
bash spnav-mouse
``` 

With options:
```
bash spnav-mouse [-s SENSITIVITY] [-d DEADZONE] [-g] [-v]
``` 

### Command Line Options

- `-s, --sensitivity SENSITIVITY`: Set the mouse movement sensitivity (default: 1.0)
- `-d, --deadzone DEADZONE`: Set the deadzone for movement detection (default: 1.0)
- `-g, --grab`: Exclusively grab the SpaceMouse device
- `-v, --verbose`: Enable verbose output for debugging
- `--version`: Show version information
- `--help`: Display help message

## Controls

- X-axis movement: Horizontal mouse movement
- Z-axis movement: Vertical mouse movement
- Y-axis rotation: Scroll wheel
- Button 0: Left mouse button
- Button 1: Right mouse button

## Notes

- Requires spacenavd to be running
- May require root permissions or appropriate group membership to access input devices
- Clean exit can be triggered with Ctrl+C

## License

Copyright 2025 enqack

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS “AS IS” AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

## Contributing

Contributions are welcome! Please feel free to submit pull requests.

## Acknowledgments

- Thanks to the SpaceNav project for the libspnav library
- All contributors and users of this software
