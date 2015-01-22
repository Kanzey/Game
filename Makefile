FLAGS = -Ofast -lsfml-graphics -lsfml-window -lsfml-system -march=native -flto
STD = -std=c++11
BPATH = ./Build/
SPATH = ./src/
INAME = Game.cpp

all : path out compile

path: | $(BPATH)

$(BPATH):
	mkdir -p $(BPATH);

out : $(SPATH)$(INAME)
	g++ -c -Ofast $(SPATH)$(INAME) -o $(BPATH)main.o $(STD) -flto  -fuse-linker-plugin

compile: $(BPATH)main.o
	g++ -o $(BPATH)app $(BPATH)main.o $(FLAGS)  -fuse-linker-plugin

clean:
	rm -r $(BPATH)
