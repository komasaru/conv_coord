gcc_options = -std=c++17 -Wall -O2 --pedantic-errors

conv_coord: conv_coord.o coord.o matrix.o obliquity.o time.o common.o
	g++92 $(gcc_options) -o $@ $^

conv_coord.o : conv_coord.cpp
	g++92 $(gcc_options) -c $<

coord.o : coord.cpp
	g++92 $(gcc_options) -c $<

matrix.o : matrix.cpp
	g++92 $(gcc_options) -c $<

obliquity.o : obliquity.cpp
	g++92 $(gcc_options) -c $<

time.o : time.cpp
	g++92 $(gcc_options) -c $<

common.o : common.cpp
	g++92 $(gcc_options) -c $<

run : conv_coord
	./conv_coord

clean :
	rm -f ./conv_coord
	rm -f ./*.o

.PHONY : run clean

