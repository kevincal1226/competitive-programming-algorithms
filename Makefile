BUILD_DIR = build

$(shell mkdir -p $(BUILD_DIR))

all: tests

tests:
	cmake -S . -B build
	cmake --build build
	./build/main
.PHONY: tests

clean:
	rm -rf build
.PHONY: clean

