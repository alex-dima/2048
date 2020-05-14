build:
	gcc -Wall main.c -o 2048 -lcurses -lpanel
clean:
	rm 2048
run:build
	./2048	
