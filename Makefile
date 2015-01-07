FLAGS = -g -o app -lsfml-graphics -lsfml-window -lsfml-system 

all : out compile

out : main.cpp
	g++ -c main.cpp

compile: main.o
	g++ main.o $(FLAGS) 
