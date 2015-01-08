FLAGS = -lsfml-graphics -lsfml-window -lsfml-system 
BPATH = ./Build/
SPATH = ./src/
INAME = main.cpp

all : out compile

out : $(SPATH)main.cpp
	g++ -c $(SPATH)main.cpp -o $(BPATH)main.o

compile: $(BPATH)main.o
	g++ -o $(BPATH)app $(BPATH)main.o $(FLAGS) 
