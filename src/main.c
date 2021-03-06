#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
 
void show_life(void *life_arr, int col, int row){

        int (*life)[col] = life_arr;
        printf("\033[H");
        for(int r = 0; r < row; r++) {
                for(int c = 0; c < col; c++) 
                        printf(life[r][c] ? "\033[95;07m  \033[m" : "  ");
                printf("\033[E");
        }
        fflush(stdout);
}

void do_life(void *life_arr, int col, int row){

        unsigned (*Life)[col] = life_arr;
        unsigned copy[row][col];
        
        for(int r = 0; r < row; r++) {
                for(int c = 0; c < col; c++){
                        int neib = 0;
                        for (int r1 = r - 1; r1 <= r + 1; r1++)
                                for (int c1 = c - 1; c1 <= c + 1; c1++)
                                        if (Life[(r1 + row) % row][(c1 + col) % col])
                                                neib++;
                        /*
                          dont count itself
                        */
                        if (Life[r][c]) neib--;
                        copy[r][c] = (neib == 3 || (neib == 2 && Life[r][c]));
                }
        }
        /*
          update
        */
        for(int r = 0; r < row; r++){
                for(int c = 0; c < col; c++){
                        Life[r][c] = copy[r][c];
                }
        }
}

int main(int argc, char **argv){

        int col = 0, row = 0;
        if (argc > 1){
                col = strtol(argv[1], NULL, 10);
        }
        if (argc > 2){
                row = strtol(argv[2], NULL, 10);
        }
        if (col <= 0) col = 50;
        if (row <= 0) row = 50;
        
        long long int gen = 0;
        srand(time(NULL));
        
        unsigned Life[row][col];
        for(int c = 0; c < col; c++){
                for(int y = 0; y < row; y++){
                        
                        Life[y][c] = rand() % 2;
                }
        }
        while(1) {
                
                show_life(Life, col, row);
                do_life(Life, col, row);
                usleep(100000);
                printf("Generation: [%llu]\n",gen++); 
        }
}
