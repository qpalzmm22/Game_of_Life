/* Simulates Game of life...  I hope to make it so that it's easy to test whole different rule sets
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAPSIZE 10

//int oldmap[MAPSIZE + 10][MAPSIZE + 10];
int oldmap[MAPSIZE][MAPSIZE];
int newmap[MAPSIZE][MAPSIZE];

// user defiend initial points
void setINIT(){
    oldmap[0][0] = 1;
    oldmap[0][1] = 1;
    oldmap[5][5] = 1;
    oldmap[5][6] = 1;
    oldmap[5][7] = 1;
}


void printMap(int (* map)[MAPSIZE]){
    for(int i = 0; i < MAPSIZE ; i++){
        for(int j = 0; j < MAPSIZE; j++){
            printf("%c", map[j][i]?'X':'0');
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

    // Left Boundary
    if(x - depth >= 0 && map[x - depth][y])    
        count++;
    
    // Right Boundary
    if(x + depth < MAPSIZE && map[x + depth][y])    
        count++;
    
    // Top Boundary
    if(y - depth >= 0 && map[x][y - depth])    
        count++;

    // Bottom Boundary 
    if(y + depth < MAPSIZE && map[x][y + depth])    
        count++;
    
    // Top Left
    if(x - depth >= 0 && y - depth >= 0 && map[x - depth][y - depth])    
        count++;
    
    // Top Right
    if(x + depth < MAPSIZE && y - depth >= 0 && map[x + depth][y - depth])    
        count++;
    
    // Bottom Left
    if(x - depth >= 0  && y + depth >= 0 && map[x - depth][y + depth])    
        count++;

    // Bottom Rigt
    if(x + depth < MAPSIZE && y + depth < MAPSIZE  && map[x + depth][y + depth])    
        count++;

    return count;
}

void lifeGameRule(int (* prevGen)[MAPSIZE], int (* nextGen)[MAPSIZE]){
   // printf("%p, %p\n", prevGen, nextGen);
    for(int i = 0; i < MAPSIZE; i++){
        for(int j = 0; j < MAPSIZE; j++){
            int nearCell = checkNear(j,i, prevGen);
//            printf("[%d, %d] : %d \n", j, i, nearCell);

            nextGen[i][j] = 0;

            if(nearCell == 3) 
                nextGen[i][j] = 1;
            
            if(nearCell == 2)
                nextGen[i][j] = prevGen[i][j]; // Just keep it alive, no new creation

        }
    }
}

int main(){
    
    setINIT();
    
    int (*p_oldmap)[MAPSIZE] = &oldmap;
    int (*p_newmap)[MAPSIZE] = &newmap;
    
    printMap(p_oldmap);
    
    void * p_tmp;
    
    int gen = 0;
    while(1){
        
        lifeGameRule(p_oldmap, p_newmap);

        printf("\n\n ------- %d - th Gen ------ \n\n", gen++);
        printMap(p_newmap);
        
        p_tmp = p_oldmap;
        p_oldmap = p_newmap;
        p_newmap = p_tmp;

        usleep(1000000);
    }
    return 0;
}
