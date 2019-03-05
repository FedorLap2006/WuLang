CCT = gcc
PF ?= Win


all: lib_$(CCT)





lib_gcc:
	gcc -c src/$(PF)/*.c && mv *.o obj/$(PF)/
	gcc -shared -o obj/$(PF)/*.o

lib_g++:
	g++ -c