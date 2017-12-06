#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>

#define N 320
#define M 180
#define STEPS 10
using namespace std;

int lines, columns;
unsigned char array[2][N][M];
unsigned char count[N][M];

unsigned char (*prev)[M]=array[0];
unsigned char (*next)[M]=array[1];

void read_data() {
    ifstream fin("data.in");
    fin>>lines>>columns;
    unsigned char tmp;
    for(int l=0;l<lines;l++) {
        for(int c=0;c<columns;c++) {
            fin>>tmp; tmp-='0';
            for(int i=0;i+l<N;i+=5) {
                for(int j=0;j+c<M;j+=5) {
                    prev[i+l][j+c]=tmp; 
                }
            } 
        }
    }
}

void random_data() {
    for(int i=0;i<N;i++) {
        for(int j=0;j<M;j++) {
            prev[i][j]=rand()%2;
        }
    }  
}

void step() {
    memset(next, 0, N*M);  
    #pragma omp parallel for
    for(int i=0; i<N; i++) {
        for(int j=0; j<M; j++) {
            int count = prev[(i+N-1)%N][(j+M-1)%M]+prev[(i+N-1)%N][(j+0)%M]+prev[(i+N-1)%N][(j+1)%M]+
                        prev[(i+0)%N  ][(j+M-1)%M]+                        +prev[(i+0)%N  ][(j+1)%M]+
                        prev[(i+1)%N  ][(j+M-1)%M]+prev[(i+1)%N  ][(j+0)%M]+prev[(i+1)%N  ][(j+1)%M];
            if (prev[i][j]==1 and (count == 2 or count == 3)) {
                next[i][j]=1;            
            }
            if (prev[i][j]==0 and count == 3) {
                next[i][j]=1; 
            } 
        }
    }
    unsigned char (*aux)[M]; 
    aux = prev ; prev = next; next = aux;
}

int crc() {
    int acc = 0;
    for(int i=0;i<M;i++) {
        for(int j=0;j<N;j++) {
            acc = (acc ^ prev[i][j])*21;
        }
    }
    return acc;
}

void display(FILE *stream) {
    for(int i=0;i<N;i++) {
        for(int j=0;j<M;j++) {
            if(prev[i][j]==1) {
                fprintf(stream, "X");
            } 
            else {
                fprintf(stream, " ");
            }
        }
        fprintf(stream, "\n");
    }
}

int main () {
//    read_data();
    random_data();
    int initial_crc = crc();
    cout<<"initial_crc "<<initial_crc<<endl;
    FILE *stream = fopen("output/output.txt", "w"); 
    fprintf(stream, "%d %d %d\n", N, M, STEPS); 

    for(int i=0;i<STEPS;i++) {
        step();
        display(stream);
    }
    fclose(stream);
    
    return 0; 
}
