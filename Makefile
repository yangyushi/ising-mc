ising: *.cpp
	g++ -std=c++11 -o ising ising.cpp monte_carlo.cpp analyse.cpp
clean:
	rm ising
