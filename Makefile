CPP_FILES=main.cpp ReadFile.cpp Connections.cpp

connection_matrix:
	g++ $(CPP_FILES) -o $@

gdb:
	g++ $(CPP_FILES) -g
	gdb ./a.out

valgrind: connection_matrix
	valgrind --quiet --leak-check=full --error-exitcode=1 --show-leak-kinds=all --errors-for-leak-kinds=all --undef-value-errors=no ./connection_matrix

clean:
	rm -rf connection_matrix a.out a.out.dSYM/
