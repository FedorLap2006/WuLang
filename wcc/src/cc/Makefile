all: clean out


# %.o: %.c
# 	gcc -c $< -o $@

out: gen.cpp lex.cpp parse.cpp types.cpp 
	g++ -std=c++11 *.cpp -o cc.exe

clean:
	# rm -rf *.o 