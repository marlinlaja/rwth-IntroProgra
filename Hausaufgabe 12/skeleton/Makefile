export INCLUDE_DIR = $(PWD)/include
ifeq ($(OS),Windows_NT)
    # Für Windows
    HTML_LINK := cmd /c mklink index.html doc\html\index.html
    REMOVE_FILE := del /q
	REMOVE_DIRECTORY := rmdir /S /Q
else
    # Für Linux (Virtual Box)
    HTML_LINK := ln -fs doc/html/index.html index.html
    REMOVE_FILE := rm -f
	REMOVE_DIRECTORY := rm -rf
endif


main.exe:
	cd library && make all
	g++ main.cpp -g -I./include -L./library -llinalg -o main.exe

index.html: include/linalg.hpp doc/linalg.dox doc/mainpage.dox
	cd doc && doxygen
	-$(HTML_LINK)

run:
	./main.exe input/input.txt

doc: index.html

clean:
	-cd doc && $(REMOVE_DIRECTORY) html latex
	$(REMOVE_FILE) docs_generated
	cd library && make clean
	$(REMOVE_FILE) *.exe
	$(REMOVE_FILE) index.html

all: doc main.exe

.PHONY: doc all clean