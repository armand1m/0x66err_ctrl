# Define the format target
.PHONY: format
format:
	@echo "Running clang-format on all header files..."
	@find . -type d \( -name "tooling" \) -prune -o -name "*.h" -print | xargs clang-format -i -style=WebKit

# Add other targets as needed
.PHONY: all
all: format
	@echo "Building project..."
	# Add your build commands here

.PHONY: clean
clean:
	@echo "Cleaning up..."
	# Add your clean commands here

.PHONY: test
test:
	@echo "Running tests..."
	# Add your test commands here
