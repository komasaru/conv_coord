gcc_options = -std=c++17 -Wall -O2 --pedantic-errors

conv_coord: conv_coord.o convert.o matrix.o obliquity.o time.o
	g++102 $(gcc_options) -o $@ $^

conv_coord.o : conv_coord.cpp
	g++102 $(gcc_options) -c $<

convert.o : convert.cpp
	g++102 $(gcc_options) -c $<

matrix.o : matrix.cpp
	g++102 $(gcc_options) -c $<

obliquity.o : obliquity.cpp
	g++102 $(gcc_options) -c $<

time.o : time.cpp
	g++102 $(gcc_options) -c $<

run : conv_coord
	./conv_coord

clean :
	rm -f ./conv_coord
	rm -f ./*.o

.PHONY : run clean

