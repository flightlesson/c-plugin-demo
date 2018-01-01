all: main c-plugin.so cpp-plugin.so

main: main.c
	$(CC) main.c -o main

c-plugin.so: c_plugin.o
	$(CC) -shared -o c-plugin.so c_plugin.o

c_plugin.o: c_plugin.c plugin.h
	$(CC) -c c_plugin.c

cpp-plugin.so: cpp_plugin.o Klass.o
	$(CC) -shared -o cpp-plugin.so cpp_plugin.o Klass.o -l stdc++

cpp_plugin.o: cpp_plugin.cpp plugin.h Klass.hpp
	$(CC) -c cpp_plugin.cpp 


