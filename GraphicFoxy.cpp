


//   PARA COMPILAR

//   g++ GraphicFoxy.cpp -lsfml-system -lsfml-graphics -lsfml-window -lsfml-audio; ./a.out

//==================================================================================


#include <SFML/Graphics.hpp>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include<cstdlib>
#include<cstdio>
#include<iostream>
#include<time.h>

using namespace std;
const float P = 0.2;
const int T = 100, POP = 500, Max=1000, idade = 50;//
int ocupacaoA = 0, ocupacaoB = 0, control = 1, k = 0;

int Sortear(){
	return rand() % 2;
}

int realocar(){
	return rand() % 4;
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

int contarCoelhos (int matriz[T][T], int px, int py){
	int counter = -1;
	for (int i = px-1; i < px+2; i++){
		for (int j = py-1; j < py+2; j++){
			if(matriz[i][j] == 1){
                counter++;
			}
		}
	}
	return counter;
}

int contarRaposas (int matriz[T][T], int px, int py){
	int counter = -1;
	for (int i = px-1; i < px+2; i++){
		for (int j = py-1; j < py+2; j++){
			if(matriz[i][j] > 1){
                counter++;
			}
		}
	}
	return counter;
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

void criar (int matriz[T][T], int px, int py, int valor){
	for (int i = px-1; i < px+2; i++){
		for (int j = py-1; j < py+2; j++){
			if ( i>0 && i<T && j>0 && j<T && matriz[i][j] == 0){
                    matriz[i][j] = valor;
                    j = py+2; i = px+2;

            }
		}
	}
}

void moverRaposa(int matriz[T][T]){
    int op = realocar();
    int erro;

    for ( int x = 1; x < T-1; x++){
        for ( int y = 1; y < T-1; y++){
            while(erro < 4){
                if ( (x-1) > 0 ){
                    if ( (y-1) > 0 ){
                        if ( matriz[x-1][y-1] == 0){
                            matriz[x-1][y-1] = matriz[x][y];
                            matriz[x][y] = 0;
                            erro = 4;
                            break;
                        }
                    }erro++;
                    if ( (y+1) < (T-1) ){
                        if ( matriz[x-1][y+1] == 0){
                            matriz[x-1][y+1] = matriz[x][y];
                            matriz[x][y] = 0;
                            erro = 4;
                            break;
                        }
                    }erro++;
                }

                if ( (x+1) < (T-1) ){
                    if ( (y-1) > 0 ){
                        if ( matriz[x-1][y-1] == 0){
                            matriz[x+1][y-1] = matriz[x][y];
                            matriz[x][y] = 0;
                            erro = 4;
                            break;
                        }
                    }erro++;
                    if ( (y+1) < (T-1) ){
                        if ( matriz[x-1][y+1] == 0){
                            matriz[x+1][y+1] = matriz[x][y];
                            matriz[x][y] = 0;
                            erro = 4;
                            break;
                        }
                    }erro++;
                }
            }
        }
    }
}





void moverRaposas(int matriz[T][T], int x, int y){
    int erro = 0;

    while ( erro < 4 ){
        if ( (x-1) != 0){ //pode subir
                        if ( (y-1) > 0 ){
                            if ( matriz[x-1][y-1] == 0){
                                matriz[x-1][y-1] = matriz[x][y];
                                matriz[x][y] = 0;
                                erro = 4; break;
                            }
                        }
                    } erro++;
            if ( (x-1) != 0){
                        if ( (y+1) != (T-1) ){ //pode descer
                            if ( matriz[x-1][y+1] == 0){
                                matriz[x-1][y+1] = matriz[x][y];
                                matriz[x][y] = 0;
                                erro = 4; break;
                            }
                        }
                    } erro++;
            if ( (x+1) != (T-1) ){
                        if ( (y-1) != 0){ //pode esquerda
                            if ( matriz[x+1][y-1] == 0){
                                matriz[x+1][y-1] = matriz[x][y];
                                matriz[x][y] = 0;
                                erro = 4; break;
                            }
                        }
                    } erro++;
            if ( (x+1) != (T-1) ){
                        if ( (y+1) != (T-1) ){ //pode direita
                            if ( matriz[x+1][y+1] == 0){
                                matriz[x+1][y+1] = matriz[x][y];
                                matriz[x][y] = 0;
                                erro = 4; break;
                            }
                        }
                    } erro++;

        }
    }




void moverCoelho(int matriz[T][T], int x, int y){
    int op = realocar(), erro = 0;

    while ( erro < 4 ){
        switch(op){
            case 0: if ( (x-1) != 0){ //pode subir
                        if ( matriz[x-1][y] == 0){
                            matriz[x-1][y] = matriz[x][y];
                            matriz[x][y] = 0;
                            erro = 4; break;
                        }
                    }op++; erro++;
            case 1: if ( (x+1) != (T-1) ){ //pode descer
                        if ( matriz[x+1][y] == 0){
                            matriz[x+1][y] = matriz[x][y];
                            matriz[x][y] = 0;
                            erro = 4; break;
                        }
                    }op++; erro++;
            case 2: if ( (y-1) != 0){ //pode esquerda
                        if ( matriz[x][y-1] == 0){
                            matriz[x][y-1] = matriz[x][y];
                            matriz[x][y] = 0;
                            erro = 4; break;
                        }
                    }op++; erro++;
            case 3: if ( (y+1) != (T-1) ){ //pode direita
                        if ( matriz[x][y+1] == 0){
                            matriz[x][y+1] = matriz[x][y];
                            matriz[x][y] = 0;
                            erro = 4; break;
                        }
                    }op++; erro++;
            case 4: op = 0;
        }
    }
}

void alimentar(int matriz[T][T]){
    int op = realocar(), erro = 0;
    for ( int x = 1; x < T-1; x++){
        for ( int y = 1; y < T-1; y++){
            if ( matriz[x-1][y-1] == 1){
                                matriz[x-1][y-1] = 0;
                                erro --;
                            } erro++;
            if ( matriz[x-1][y+1] == 1){
                                matriz[x-1][y+1] = 0;
                                erro --;
                            } erro++;
            if ( matriz[x+1][y-1] == 1){
                                matriz[x+1][y-1] = 0;
                                erro --;
                            } erro++;
            if ( matriz[x+1][y+1] == 1){
                                matriz[x+1][y+1] = 0;
                                erro --;
                            } erro++;
                 if (erro > 3){
                    matriz[x][y] = matriz[x][y]+1;
                }
            if (matriz[x][y]>1)  matriz[x][y] = matriz[x][y]+1;

            }
            
            
            }
        }




void reproduzir(int matriz[T][T]){
    int coe, rap;
    float b;
    for ( int x = 1; x < T-1; x++){
        for ( int y = 1; y < T-1; y++){


            if ( matriz[x][y] == 1 ){
                coe = contarCoelhos(matriz, x, y);
                if ( coe > 2 && control <= 3){
                    criar(matriz, x, y, 1);
                    control++;
                }
            }
            if ( matriz[x][y] > 1 ){
                rap = contarRaposas(matriz, x, y);
                if ( rap > 3 ){
                    criar(matriz, x, y, 2);
                }
            }

            b = k % control;
            if ( b == 0 ){
                control = 1;
            }
        }
    }
}

void falecer(int matriz[T][T]){
    for ( int x = 1; x < T-1; x++){
        for ( int y = 1; y < T-1; y++){
            if ( matriz[x][y] > 1 ){
                if (matriz[x][y] > 5){
                    matriz[x][y] = 0;
                }
            }
        }
    }
}

void regra(int matriz[T][T]){
    k++;
    falecer(matriz);
    reproduzir(matriz);
    for ( int x = 1; x < T-1; x++){
        for ( int y = 1; y < T-1; y++){
            if ( matriz[x][y] == 1 ){
                moverCoelho(matriz, x, y);
            }else{
                moverRaposas(matriz, x, y);
            }

        }
    }
    alimentar(matriz);
}



//-----------------------------------------------------------------------

void Pause (int milliseconds) {
	struct timespec ts;
	ts.tv_sec = 0;//milliseconds / 1000;
	ts.tv_nsec = (milliseconds % 1000) * 1000000;
	nanosleep(&ts, NULL);
}

void show (sf::RenderWindow *window, int matriz[T][T]) {

	sf::RectangleShape rect (sf::Vector2f (3.5, 3.5));
	
	for (int i = 0; i < T; i++){
		for (int j = 0; j < T; j++) {
			if (matriz[i][j]==0)
				rect.setFillColor (sf::Color(255, 255, 255));
			if (matriz[i][j]==1)
				rect.setFillColor (sf::Color(255, 0, 0)); //coelho
			if (matriz[i][j] > 1 )
				rect.setFillColor (sf::Color(0, 0, 255)); //raposa
			rect.setPosition  (i*5, j*5);         
			window->draw (rect);
	    }
	}
}

int main() {

	srand(time(NULL));
	int m[T][T], L = 0;
	sf::RenderWindow window(sf::VideoMode(500, 500), "Simulação de Torcida!");

	zerarMatriz(m);
	
	ocuparMatriz(m);
	
	while (window.isOpen()  ) {//&& (L < Max)
		sf::Event event;
		while (window.pollEvent(event)) 
			if( (event.type == sf::Event::Closed) || ( (event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape) ) )
				return 0;
			
		regra(m);

		if (k==0)
			break;
		
		window.clear();
			
		show (&window, m);

		window.display();

		Pause (10);
		L++;
		printf("%d\n", L );		
		
	}
	printf("\n%d\n", L);
	while (window.isOpen() ){ //|| L == Max
		sf::Event event;
		while (window.pollEvent(event)) 
			if( (event.type == sf::Event::Closed) || ( (event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape) ) )
				return 0;
		
		show (&window, m);
		
	}


	return 0;
}
