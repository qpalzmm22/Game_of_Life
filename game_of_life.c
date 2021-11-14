/* Simulates Game of life...  I hope to make it so that it's easy to test whole different rule sets
 * TODO : Exit game if equlized : check if board is same for 10 turns (consider oscillation of more than 10 as not "equalized" because it's not very 'obvious' for humen; at least for me) 
* Do I have to save 10 arrays..?? how to check,,,
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

#define MAPSIZE 100

//            012345678
#define L_GOL 001100000
#define C_GOL 000100000



//int oldmap[MAPSIZE + 10][MAPSIZE + 10];
int oldmap[MAPSIZE][MAPSIZE];
int newmap[MAPSIZE][MAPSIZE];

// user defiend initial points
void setINIT(){
    for(int i = 0; i < MAPSIZE ; i++){
        for(int j = 0; j < MAPSIZE; j++){
            oldmap[j][i] = rand() % 2 ;
        }
    }
}
void printMap(int (* map)[MAPSIZE]){
    for(int i = 0; i < MAPSIZE ; i++){
        for(int j = 0; j < MAPSIZE; j++){
            printf("%c", map[j][i]?'X':' ');
        }
        printf("\n");
    }
}

// returns number of "On" cells near (x, y) with depth 1
// TODO : Could implement with more depth
int
checkNear(int x, int y, int(* map)[MAPSIZE]){
    int depth = 1;
    int count = 0;

    // Top Boundary
    if(y - depth >= 0 && map[y - depth][x])    
        count++;
    
    // Bottom Boundary 
    if(y + depth < MAPSIZE && map[y + depth][x])    
        count++;
    
    // Left Boundary
    if(x - depth >= 0 && map[y][x - depth])    
        count++;

    // Right Boundary
    if(x + depth < MAPSIZE && map[y][x + depth])    
        count++;
    
    // Top Left
    if(y - depth >= 0 && x - depth >= 0 && map[y - depth][x - depth])    
        count++;
    
    // Top Right
    if(y + depth < MAPSIZE && x - depth >= 0 && map[y + depth][x - depth])    
        count++;
    
    // Bottom Left
    if(y - depth >= 0  && x + depth >= 0 && map[y - depth][x + depth])    
        count++;

    // Bottom Rigt
    if(y + depth < MAPSIZE && x + depth < MAPSIZE  && map[y + depth][x + depth])    
        count++;

    return count;
}

// TODO: Generalize this with bitmap of nearcell to live / nearcell to creat
void lifeGameRule(int (* prevGen)[MAPSIZE], int (* nextGen)[MAPSIZE], unsigned int lbmap, unsigned int cbmap){
   // printf("%p, %p\n", prevGen, nextGen);
    for(int i = 0; i < MAPSIZE; i++){
        for(int j = 0; j < MAPSIZE; j++){
	    int nearCell = checkNear(j,i, prevGen);
//            printf("[%d, %d] : %d \n", j, i, nearCell);
            
            unsigned int nearbmap = 1 << (8 - nearCell) ;

	    nextGen[i][j] = 0;

            if(nearbmap & lbmap) 
                nextGen[i][j] = 1;
            
            if(nearbmap & cbmap)
                nextGen[i][j] = prevGen[i][j]; // Just keep it alive, no new creation

        }
    }
}

int main(){
    srand(time(0x0));    
    setINIT();
    
    int (*p_oldmap)[MAPSIZE] = &oldmap;
    int (*p_newmap)[MAPSIZE] = &newmap;
    
    printMap(p_oldmap);
    
    void * p_tmp;
    char begin;

    int gen = 0;
    sleep(2);

    while(1){
        
        lifeGameRule(p_oldmap, p_newmap, L_GOL, C_GOL);

        printf("\n\n ------- %d - th Gen ------ \n\n", gen++);
        printMap(p_newmap);
        
        p_tmp = p_oldmap;
        p_oldmap = p_newmap;
        p_newmap = p_tmp;

        usleep(500000);
    }
    return 0;
}
