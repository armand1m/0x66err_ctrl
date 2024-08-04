# Define the board type, port, and FQBN (Fully Qualified Board Name)
BOARD_FQBN = arduino:avr:mega

# Change this to your Arduino port
PORT = /dev/cu.usbmodem2143101  

# Set your desired baud rate
BAUD = 31250  

# Project directories and files
SRC_DIR = .
BUILD_DIR = build
LIB_DIR = libraries

# Change this to your main .ino file
SKETCH = $(SRC_DIR)/0x66err_ctrl.ino  

# Libraries to include (you can add more libraries as needed)
EXTERNAL_LIBRARIES = "Bounce2" "Encoder" "MIDI Library" "MCUFRIEND_kbv" "Adafruit TouchScreen" "Adafruit BusIO" "Adafruit GFX Library"

# Arduino CLI command
ARDUINO_CLI = arduino-cli

# Ignore directories when running clang-format
IGNORE_DIRS := ./tooling ./libraries

.PHONY: all build upload clean format serial

# Helper function to build the ignore pattern for find
define build_ignore_pattern
$(foreach dir,$(IGNORE_DIRS),-path $(dir) -prune -o)
endef

# Default target: build and upload
all: clean format build upload

# Build the project
build: 
	@echo "Installing libraries..."
	@$(ARDUINO_CLI) lib install $(EXTERNAL_LIBRARIES)
	@echo "Building the project..."
	@$(ARDUINO_CLI) compile --fqbn $(BOARD_FQBN) --build-path $(BUILD_DIR) --libraries $(LIB_DIR) $(SKETCH)

# Upload the project to the board
upload:
	@echo "Uploading to the board..."
	@$(ARDUINO_CLI) upload -p $(PORT) --fqbn $(BOARD_FQBN) $(SKETCH)

# Clean build files
clean:
	@echo "Cleaning build files..."
	@rm -rf $(BUILD_DIR)/*

# Additional targets for convenience
install_libs:
	@echo "Installing libraries..."
	@$(ARDUINO_CLI) lib install $(EXTERNAL_LIBRARIES)

# List all available boards and cores
list_boards:
	@$(ARDUINO_CLI) board list

# List all available cores
list_cores:
	@$(ARDUINO_CLI) core list

# Format the code
format:
	@echo "Running clang-format on all files, ignoring $(IGNORE_DIRS)..."
	@find . $(call build_ignore_pattern) -name "*.h" -exec clang-format -i -style=WebKit {} +

# Open serial monitor using screen
serial:
	@echo "Opening serial monitor on port $(PORT) with baud rate $(BAUD)..."
	@TERM=vt100 screen $(PORT) $(BAUD)

# Stop the serial monitor
stop_serial:
	@echo "Stopping serial monitor..."
	@killall screen

# flash the HIDUINO firmware into the atmega16u2
flash_hiduino:
	@echo "Changing directory to ./tooling/hiduino and running flashmidi.sh..."
	@cd ./tooling/hiduino && ./flashmidi.sh

# flash the original firmware back into the atmega16u2
flash_original:
	@echo "Changing directory to ./tooling/hiduino and running flashoriginal.sh..."
	@cd ./tooling/hiduino && ./flashoriginal.sh