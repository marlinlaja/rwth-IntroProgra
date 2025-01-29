all: hello.exe

hello.exe:
	g++ hello.cpp -o hello.exe

run: hello.exe
	.\hello.exe

clean:
	del *.exe

.PHONY: all clean run