SRC=../core

all: run MakeRootFile

run: main.cxx $(SRC)/Point.cxx $(SRC)/Source.cxx $(SRC)/System.cxx $(SRC)/FormatSystem.cxx GraphLoader.cxx
	g++ $^ -o $@ -I$(SRC) `root-config --libs --cflags` -O3 -std=c++17

MakeRootFile: MakeRootFile.cxx $(SRC)/Point.cxx $(SRC)/Source.cxx $(SRC)/System.cxx $(SRC)/FormatSystem.cxx GraphLoader.cxx
	g++ $^ -o $@ -I$(SRC) `root-config --libs --cflags` -O3 -std=c++17

clean:
	rm run