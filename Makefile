FLAGS = -O2 -lsfml-graphics -lsfml-window -lsfml-system 
STD = -std=c++11
BPATH = ./Build/
SPATH = ./src/
INAME = Game.cpp

all : path out compile

path: | $(BPATH)

$(BPATH):
	mkdir -p $(BPATH);

out : $(SPATH)$(INAME)
	g++ -c $(SPATH)$(INAME) -o $(BPATH)main.o $(STD)

compile: $(BPATH)main.o
	g++ -o $(BPATH)app $(BPATH)main.o $(FLAGS) 

clean:
	rm -r $(BPATH)
