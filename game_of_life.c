/* Simulates Game of life...
 * I hope to make it so that it's easy to test whole different rule sets
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAPSIZE 10

//int oldmap[MAPSIZE + 10][MAPSIZE + 10];
int oldmap[20][20];
int newmap[MAPSIZE][MAPSIZE];

// user defiend initial points
void setINIT(){
    oldmap[0][0] = 100;
    oldmap[0][1] = 101;
    oldmap[5][5] = 1;
    oldmap[5][6] = 1;
    oldmap[5][7] = 1;
}


void printMap(int ** map){
    for(int i = 0; i < MAPSIZE ; i++){
        for(int j = 0; j < MAPSIZE; j++){
            printf("%c", &map[j][i]?'X':'0');
        }
        printf("\n");
    }
}

// returns number of "On" cells near (x, y) with depth 1
// TODO : Could implement with more depth
int
checkNear(int x, int y, int** map){
    int depth = 1;
    int count = 0;

    // Left Boundary
    if(x - depth >= 0 && &map[x - depth][y])    
        count++;
    
    // Right Boundary
    if(x + depth < MAPSIZE && &map[x + depth][y])    
        count++;
    
    // Top Boundary
    if(y - depth >= 0 && &map[x][y - depth])    
        count++;

    // Bottom Boundary 
    if(y + depth < MAPSIZE && &map[x][y + depth])    
        count++;
    
    // Top Left
    if(x - depth >= 0 && y - depth >= 0 && &map[x - depth][y - depth])    
        count++;
    
    // Top Right
    if(x + depth < MAPSIZE && y - depth >= 0 && &map[x + depth][y - depth])    
        count++;
    
    // Bottom Left
    if(x - depth >= 0  && y + depth >= 0 && &map[x - depth][y + depth])    
        count++;

    // Bottom Rigt
    if(x + depth < MAPSIZE && y + depth < MAPSIZE  && &map[x + depth][y + depth])    
        count++;

    return count;
}

void lifeGameRule(int ** prevGen, int ** nextGen){
   // printf("%p, %p\n", prevGen, nextGen);
    for(int i = 0; i < MAPSIZE; i++){
        for(int j = 0; j < MAPSIZE; j++){
            int nearCell = checkNear(j,i, prevGen);
            printf("[%d, %d] : %d \n", j, i, nearCell);

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
    
    int **p_oldmap = oldmap;
    int ** p_newmap = newmap;
    
    for(int i = 0; i < MAPSIZE ; i++){
        for(int j = 0; j < MAPSIZE; j++){
            printf("%d ", oldmap[i][j]);
        }
        printf("\n");
    }

    printf("[0] : %p\n", oldmap);
    printf("[1] : %p\n", p_oldmap);
    
    for(int i = 0; i < MAPSIZE ; i++){
        for(int j = 0; j < MAPSIZE; j++){
            //printf("%d ", *(p_oldmap + (4 * i) +(j*2)));
            printf("%d ", p_oldmap[i][j]);
            
        }
        printf("\n");
    }
    
    void * p_tmp;
    
    printf("The map : %p\n", oldmap);
    printf("pmap : %p\n", p_oldmap);
    printf("\n");
    
    printf("The map: %p\n", oldmap[0]);
    printf("pp: %p\n", &p_oldmap[0]);
    printf("\n");
    
    //printf("The map: %p\n", oldmap[1]);
    //printf("pp: %p\n", *p_oldmap[1]);
    
    printf("The map: %d\n", oldmap[10][10]);
    printf("pp: %d\n", p_oldmap[10][10]);
    //printMap(p_oldmap);
    
    int a = 0;
    while(1){

      //  lifeGameRule(p_oldmap, p_newmap);

      //  printMap(p_newmap);
        
    //    p_tmp = p_oldmap;
      //  p_oldmap = p_newmap;
        //p_newmap = p_tmp;

        usleep(500000);
    }
    return 0;
}

