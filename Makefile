FLAGS = -lsfml-graphics -lsfml-window -lsfml-system 
BPATH = ./Build/
SPATH = ./src/
INAME = Game.cpp

all : path out compile

path: | $(BPATH)

$(BPATH):
	mkdir -p $(BPATH);

out : $(SPATH)$(INAME)
	g++ -c $(SPATH)$(INAME) -o $(BPATH)main.o

compile: $(BPATH)main.o
	g++ -o $(BPATH)app $(BPATH)main.o $(FLAGS) 

clean:
	rm -r $(BPATH)
