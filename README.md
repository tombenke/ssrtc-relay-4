# Start-Stop RTC for 4 relays adapter

## About

This is the firmware of a circuit that uses WEMOS-D1-MINI ESP8266 based board that is extended with a 4 relays module and an RTC timer.
The board can be used to control 4 independent 24VAC valves of a dripping irrigator system.
Each valve is controlled by a software start-stop timer.

## Development

### Installation

The project uses [Arduino](https://www.arduino.cc/) and [arduino-cli](https://arduino.github.io/arduino-cli),
and [Taskfile](https://taskfile.dev/) for automation of the development tasks.

Install these tools before modify the source code, or build and upload the firmware to the board.

### Compile and Upload

Compile the source code:

```bash
task compile
```

Upload the compiled firmware:

```bash
task upload
```
