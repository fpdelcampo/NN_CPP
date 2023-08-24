CXX = g++
CXXFLAGS = -std=c++17 -Wall

feedforward_test: feedforward_test.cpp
	$(CXX) $(CXXFLAGS) feedforward_test.cpp feedforward.cpp dense.cpp matrix.cpp -o feedforward_test