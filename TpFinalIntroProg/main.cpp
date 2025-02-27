#include<iostream>
#include <conio2.h>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

const int WINDOW = 20;
const int VEL_INICIAL = 200;
const int ANCHO = 40;
const int ALTO = 1200;
const int VELPROYECTIL = 2000;
const int TIEMPO_MSJ = 5000;
const int TIEMPO_INMUNIDAD = 2000;
const int TIEMPO_PANTALLA_FINAL = 5000;
int desplazamiento = 0;
int VELOCIDAD = VEL_INICIAL;
int puntaje;
string mensaje;
bool mensajeActivo;

void esperar(int milisegundos) {
	clock_t inicio = clock();
	while (clock() - inicio < milisegundos * CLOCKS_PER_SEC / 1000);
}

class Principal{	
protected:	
	int posX, posY;public:
	virtual void dibujar() = 0;
	virtual void actualizar() = 0;
};

// terreno 


class terreno{
protected:
	string canon[ALTO];
	char canonChar[ALTO][ANCHO];
public:
	terreno(){};
	~terreno(){};
	
	void inicializarCanon(){ //
		srand(time(0));
		for (int i = 0; i < ALTO; i++) {
			int inicio=rand()%10 +5;
			int fin=rand()%10+25;
			int densidad = rand()%6+1;
			for(int densidad = 0;densidad<4;densidad++){
				for (int j = 0; j < ANCHO; j++) {
					if((j<inicio-1)|| (j>fin+1)){
						canonChar[i][j] = 176;
					}
					if ((j==inicio-1)||(j==fin+1)){
						canonChar[i][j] = 177;
					}
					if(j>inicio && j<fin){
						canonChar[i][j] = ' ';
					}
				}
				i++;
			}
			i--;
		}
		for (int i = 0; i < ALTO; i++) {
			string linea = "";
			for (int j = 0; j < ANCHO; j++) {
				linea += canonChar[i][j];
			}
			canon[i] = linea
		}
		mensaje = "No los enfrentes directamente";
	}
		void dibujar(){
			for(int i= 0; i<20;i++){
				gotoxy(1,i+1);
				textcolor(6);
				cout<<canon[desplazamiento + VENTANA -1 -i];
				textcolor(15);
				VELOCIDAD = VEL_INICIAL - static_cast<int>(desplazamiento / 10);
			}
		}
			
			char fondo(int _x) {
				return canon[desplazamiento][_x]; 
			}
			
};

int main (int argc, char *argv[]) {
	return 0;
}

