all: main.exe

main.exe:
	g++ main.cpp -o main.exe

run: main.exe
	.\main.exe

clean:
	del *.exe
	del *.dot

.PHONY: all clean run