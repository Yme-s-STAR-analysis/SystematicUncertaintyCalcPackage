SRC=../core

all: testPoint testSource testSystem testFormat

testPoint: testPoint.cxx $(SRC)/Point.cxx
	g++ $^ -o $@ -I$(SRC) `root-config --libs --cflags` -O3 -std=c++17

testSource: testSource.cxx $(SRC)/Point.cxx $(SRC)/Source.cxx
	g++ $^ -o $@ -I$(SRC) `root-config --libs --cflags` -O3 -std=c++17

testSystem: testSystem.cxx $(SRC)/Point.cxx $(SRC)/Source.cxx $(SRC)/System.cxx
	g++ $^ -o $@ -I$(SRC) `root-config --libs --cflags` -O3 -std=c++17

testFormat: testFormat.cxx $(SRC)/Point.cxx $(SRC)/Source.cxx $(SRC)/System.cxx $(SRC)/FormatSystem.cxx
	g++ $^ -o $@ -I$(SRC) `root-config --libs --cflags` -O3 -std=c++17

clean:
	rm testSource testPoint testSystem testFormat