
default:
	g++ main.cpp ReadFile.cpp FilesToParse.cpp

gdb:
	g++ main.cpp ReadFile.cpp FilesToParse.cpp -g
	gdb ./a.out

valgrind: default
	valgrind --quiet --leak-check=full --error-exitcode=1 --show-leak-kinds=all --errors-for-leak-kinds=all --undef-value-errors=no ./a.out

clean:
	rm -rf a.out
