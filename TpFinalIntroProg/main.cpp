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

// nave 


class nave : public Principal{
private:
	int vidas;
	bool inmunidad;
	int aPosX, aPosY;
	clock_t tUltimaColision;
	
	
public:
	bool dispara;
	
	nave(){
		posX = ANCHO / 2;
		posY = 20;
		aPosX = posX;
		aPosY = posY;
		vidas = 5; 
		tUltimaColision = clock();
		dispara = false;
	}
		
		void mover(){ // mover con las teclas
			
			if(kbhit()){
				char tecla = getch();
				if(tecla == 75 && posX > 0){ // Izquierda
					aPosX = posX;
					posX--;
				}
				if(tecla == 77 && posX < ANCHO -1){ // Derecha
					aPosX = posX;
					posX++;
				}
				if(tecla==' '){
					dispara = true;
				}
			} else {
				gotoxy(aPosX, aPosY);
				putchar(' ');
			}
		}
			
			bool getDistapara(){
				return dispara;
			}
				void setDispara(bool _dispara){
					dispara = _dispara;
				}
					
					void dibujar() override{
						gotoxy(aPosX,posY);
						putchar(' ');
						gotoxy(posX,posY);
						if(inmunidad){
							textcolor(LIGHTRED);
						} else {
							textcolor(WHITE);
						}
						putchar('^');
						gotoxy(41,21);
					}
					void actualizar() override{
						
					}
					int getVidas(){
						return vidas;
					}
						
						int getX(){
							return posX;
						}
							int getY(){
								return posY;
							}
								bool getInmunidad(){
									return inmunidad;
								}
									
									
									void manejarColision(char _caracter) { 
										// Si el carácter no es espacio, cuenta como colisión
										if (_caracter != ' ') {
											// Verificar si ha pasado el tiempo de inmunidad
											if (clock() - tUltimaColision >= TIEMPO_INMUNIDAD * CLOCKS_PER_SEC / 1000) {
												vidas--;
												tUltimaColision = clock();
												mensaje = "Cuidado, puedes dañar la nave";
											}
										}
										
										if((clock() - tUltimaColision >= TIEMPO_INMUNIDAD * CLOCKS_PER_SEC / 1000)) {
											inmunidad = false;
										} else {
											inmunidad= true;
										}
									}
};


//nave enemiga 


class naveEnemiga : public Principal {
private:
	bool activa;
	int limiteIzq;
	int limiteDer;
	bool moviendoDerecha;
	int ultDesplazamiento;
	int aPosX, aPosY;
	int contadorLateral;
	int esperarLateral;
	
public:
	naveEnemiga(){
		activa=false;
		moviendoDerecha=true;
		ultDesplazamiento= 0;
		contadorLateral = 0;
		esperarLateral = 50;
		
	}
	
	void activar(int _desplazamiento) {
		posY = 1;
		posX = ANCHO / 2;
		limiteIzq = posX - 5;
		limiteDer = posX + 5;
		activa = true;
		ultDesplazamiento = _desplazamiento;
		contadorLateral = 0;
	}
	
	void desactivar() {
		activa = false;
	}
	
	void actDesplazamiento(int _desplazamiento) {
		if (_desplazamiento > ultDesplazamiento) {
			posY++;
			ulDesplazamiento = _desplazamiento;
			if (posY > VENTANA) {
				desactivar();
			}
		}
	}
	
	void actualizar() override {
		if (!activa) return;
		
		aPosX = posX;
		aPosY = posY;
		
		// Movimiento lateral medio raro
		if (moviendoDerecha) {
			posX++;
			if (posX >= limiteDer) moviendoDerecha = false;
		} else {
			posX--;
			if (posX <= limiteIzq) moviendoDerecha = true;
		}
	}
	
	void dibujar() override {
		if (!activa) return;
		
		gotoxy(posX, posY);
		textcolor(15);
		putchar('X');
		gotoxy(aPosX,aPosY);
		putchar(' ');
	}
	
	int getX(){ 
		return posX; 
	}
		int getY() { 
			return posY; 
		}
		bool estaActiva() { 
			return activa; 
		}
		
};


int main (int argc, char *argv[]) {
	return 0;
}

