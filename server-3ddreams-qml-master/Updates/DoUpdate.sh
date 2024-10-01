
#!/bin/bash
avrdude -c wiring -p ATmega2560 -P /dev/ttyACM0 -b 115200 -D -U flash:w:Update.hex
