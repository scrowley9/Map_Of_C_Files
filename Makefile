
connection_matrix:
	g++ main.cpp ReadFile.cpp FilesToParse.cpp Connections.cpp -o $@

gdb:
	g++ main.cpp ReadFile.cpp FilesToParse.cpp Connections.cpp -g
	gdb ./a.out

valgrind: default
	valgrind --quiet --leak-check=full --error-exitcode=1 --show-leak-kinds=all --errors-for-leak-kinds=all --undef-value-errors=no ./a.out

clean:
	rm -rf connection_matrix
