/* Simulates Game of life...  I hope to make it so that it's easy to test whole different rule sets
 * TODO : Exit game if equlized : check if board is same for 10 turns (consider oscillation of more than 10 as not "equalized" because it's not very 'obvious' for humen; at least for me) 
* Do I have to save 10 arrays..?? how to check,,,
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

#define MAPSIZEX 250
#define MAPSIZEY 60
//              012345678
#define L_GOL 0b001100000
#define C_GOL 0b000100000



//int oldmap[MAPSIZE + 10][MAPSIZE + 10];
int oldmap[MAPSIZEY][MAPSIZEX];
int newmap[MAPSIZEY][MAPSIZEX];

// user defiend initial points
void setINIT(){
    for(int i = 0; i < MAPSIZEY ; i++){
        for(int j = 0; j < MAPSIZEX; j++){
            oldmap[i][j] = rand() % 2 ;
        }
    }
}
void printMap(int (* map)[MAPSIZEY]){
    for(int i = 0; i < MAPSIZEY ; i++){
        for(int j = 0; j < MAPSIZEX; j++){
            printf("%c", map[i][j]?'X':' ');
        }
        printf("\n");
    }
    printf("\n");
}

// returns number of "On" cells near (x, y) with depth 1
// TODO : Could implement with more depth
int
checkNear(int x, int y, int(* map)[MAPSIZEY]){
    int depth = 1;
    int count = 0;

    // Top Boundary
    if(y - depth >= 0 && map[y - depth][x])    
        count++;
    
    // Bottom Boundary 
    if(y + depth < MAPSIZEY && map[y + depth][x])    
        count++;
    
    // Left Boundary
    if(x - depth >= 0 && map[y][x - depth])    
        count++;

    // Right Boundary
    if(x + depth < MAPSIZEX && map[y][x + depth])    
        count++;
    
    // Top Left
    if(y - depth >= 0 && x - depth >= 0 && map[y - depth][x - depth])    
        count++;
    
    // Top Right
    if(y + depth < MAPSIZEY && x - depth >= 0 && map[y + depth][x - depth])    
        count++;
    
    // Bottom Left
    if(y - depth >= 0  && x + depth >= 0 && map[y - depth][x + depth])    
        count++;

    // Bottom Rigt
    if(y + depth < MAPSIZEY && x + depth < MAPSIZEX  && map[y + depth][x + depth])    
        count++;

    return count;
}

// TODO: Generalize this with bitmap of nearcell to live / nearcell to creat
void lifeGameRule(int (* prevGen)[MAPSIZEY], int (* nextGen)[MAPSIZEY], unsigned int lbmap, unsigned int cbmap){
  
 //   printf("%x, %x\n", lbmap, cbmap);
    for(int i = 0; i < MAPSIZEY; i++){
        for(int j = 0; j < MAPSIZEX; j++){
              int nearCell = checkNear(j,i, prevGen);
//            printf("[%d, %d] : %d \n", j, i, nearCell);

            unsigned int nearbmap = 0x1 << (8 - nearCell) ;
	
	    nextGen[i][j] = 0;

            if(nearbmap & lbmap)
                nextGen[i][j] = prevGen[i][j]; // Just keep it alive, no new creation

            if(nearbmap & cbmap) 
                nextGen[i][j] = 1;

        }
    }
}

int main(){
    srand(time(0x0));    
    setINIT();
    
    int (*p_oldmap)[MAPSIZEY] = &oldmap;
    int (*p_newmap)[MAPSIZEY] = &newmap;
    
    printMap(p_oldmap);
    
    void * p_tmp;
    char begin;

    int gen = 0;
    sleep(2);

    while(1){
        
        lifeGameRule(p_oldmap, p_newmap, L_GOL, C_GOL);

 //      printf("\n\n ------- %d - th Gen ------ \n\n", gen++);
        printMap(p_newmap);

        p_tmp = p_oldmap;
        p_oldmap = p_newmap;
        p_newmap = p_tmp;

        usleep(100000);
    }
    return 0;
}
