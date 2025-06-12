# Makefile for DCDL Helper (CMake-based project)

.PHONY: all build run clean

all: build

build:
	cmake --preset vcpkg
	cmake --build --preset vcpkg

run: build
	./build/bin/dcdl-helper

clean:
	rm -rf build
