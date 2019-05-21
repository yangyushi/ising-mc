ising: ising.cpp monte_carlo.cpp monte_carlo.h
	g++ -std=c++11 -o ising ising.cpp monte_carlo.cpp
clean:
	rm ising
