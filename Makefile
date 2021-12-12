CC = clang++

all:	
	mkdir out || make build

build:
	$(CC) main.cpp -o out/tapiocabuilder.exe

clean:
	rd /s /q out && mkdir out