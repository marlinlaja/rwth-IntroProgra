all: main.exe

main.exe:
	cd src && make libset.a
	g++ main.cpp -L./src -lset -o main.exe

run: main.exe
	.\main.exe

pdf: main.exe
	.\main.exe
	dot -Tpdf graph.dot -o graph.pdf

clean:
	del *.exe
	del *.dot
	del graph.pdf
	cd src && make clean

.PHONY: all clean run
