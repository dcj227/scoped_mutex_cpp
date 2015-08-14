all: test_scoped_mutex

test_scoped_mutex: test_scoped_mutex.cpp
	g++ -g -o test_scoped_mutex test_scoped_mutex.cpp
