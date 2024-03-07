all: FitExec

FitExec: FitMain.cxx FitCore.cxx
	g++ $^ -o $@ `root-config --libs --cflags` -std=c++17 -O3