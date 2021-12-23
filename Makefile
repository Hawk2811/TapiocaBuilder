CC = clang++

all:	
	mkdir out && make build

build:
ifeq ($(OS),Windows_NT)
		make win32build
else
		make unixbuild
endif

win32build:
	$(info Building TapiocaBuilder for Win32 Platforms)
	$(CC) src/win32.cpp -o out/tapiocabuilder.exe

unixbuild:
	$(info Building TapiocaBuilder for Unix Platforms)
	$(CC) src/unix.cpp -o out/tapiocabuilder

clean:
ifeq ($(OS),Windows_NT)
		rd /s /q out && mkdir out
else
		rm -r out && mkdir out
endif