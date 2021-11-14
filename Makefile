all:
	gcc -o gol game_of_life.c -g

clean :
	rm gol 
