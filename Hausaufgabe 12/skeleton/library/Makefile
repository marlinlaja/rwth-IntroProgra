ifeq ($(OS),Windows_NT)
    # Für Windows
    RM := del /q
else
    # Für Linux (Virtual Box)
    RM := rm -f
endif

all: liblinalg.a

liblinalg.a :
	g++ -c *.cpp
	ar rcs liblinalg.a *.o
clean:
	$(RM) /f liblinalg.a
	$(RM) *.o

.PHONY: all clean