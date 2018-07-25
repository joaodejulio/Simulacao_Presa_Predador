//   PARA COMPILAR
//   g++ testematriz.cpp 	//-lsfml-system -lsfml-graphics -lsfml-window -lsfml-audio; ./a.out
//==================================================================================
//#include <SFML/Graphics.hpp>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include<cstdlib>
#include<cstdio>
#include<iostream>
#include<time.h>

using namespace std;

const int T = 10, POP = 5;
int ocupacaoA = 0, ocupacaoB = 0;

int Sortear(){
	return rand() % 2;
}

int realocar(){
	return rand() % (T-2) + 1;
}

void zerarMatriz(int matriz[T][T]){
	int i, j;
	for(i = 0; i<T; i++){
		for(j = 0; j<T; j++){
			matriz[i][j] = 0;
		}
	}
}

void imprimirMatriz(int matriz[T][T]){
	int i, j;
	for(i = 0; i<T; i++){
		for(j = 0; j<T; j++){
			cout << matriz[i][j];
		}
		printf("\n");
	}
}

int contarIguais (int matriz[T][T], int px, int py){
	int counter = -1;
	if ( matriz[px][py] == 0 ){
        return 0;
    }

	int valor = matriz[px][py];
	for (int i = px-1; i < px+2; i++){
		for (int j = py-1; j < py+2; j++){
			if(matriz[i][j] == valor){
                counter++;
			}
		}
	}
	return counter;
}

int contarTodos (int matriz[T][T], int px, int py){
	int counter = -1;
	if ( matriz[px][py] == 0 ){
        return 0;
	}
	for (int i = px-1; i < px+2; i++){
		for (int j = py-1; j < py+2; j++){
			if( matriz[i][j] != 0){
                counter++;
			}
		}
	}
	return counter;
}

void regra(int matriz[T][T]){
	bool teste = 0;
	int same, all, a, b;

	for(int x = 1; x < T-1; x++){
		for(int y = 1; y < T-1; y++){
			if (matriz[x][y] == 0)
                teste = 1;

            same = contarIguais(matriz, x, y);
			all = contarTodos(matriz, x, y);

			if (all == 0)
                all = 1;

			if (matriz[x][y] == 1){
				if (all == same){
                    teste = 1;
				}
			}

			if (matriz[x][y] == 2){
				if( (same / all) > 0.3 ){
                    teste = 1;
				}
			}

			//realocacao
			while(teste == 0){
				a = realocar();
				b = realocar();
				if( matriz[a][b] == 0){
				    matriz[a][b] = matriz[x][y];
				    matriz[x][y] = 0;
				    teste = 1;
				}
			}

		    teste = 0;
		}
	}
}

void ocuparMatriz(int matriz[T][T]){
	int i, j, sorteio;
	while( (ocupacaoA < POP) || (ocupacaoB < POP) ){
	    for(i = 1; i < T-1; i++){
	        for(j = 1; j < T-1; j++){
	            sorteio = Sortear();
	            if (sorteio == 1){ // se sim, vai ocupar a matriz
	                sorteio = Sortear();
	                if( (ocupacaoA < POP) && (sorteio == 1) ){
	                	matriz[i][j] = 1;
	                	ocupacaoA++;
	                }
	                if( (ocupacaoB < POP) && (sorteio != 1) ){
	                	matriz[i][j] = 2;
	                	ocupacaoB++;
	                }
	            }
	        }
	    }
	}
}

int main (){

	srand(time(NULL));
	int m[T][T];

	zerarMatriz(m);
	ocuparMatriz(m);
	imprimirMatriz(m);
	printf("\n");

	regra(m);
	imprimirMatriz(m);
	printf("\n");

	regra(m);
	imprimirMatriz(m);
	printf("\n");

	regra(m);
	imprimirMatriz(m);
	printf("\n");

	return 0;
}
