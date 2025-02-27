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

//proyectil

class proyectil : public Principal {
private:
	bool activo;
	clock_t tInicio;
	int velocidadVertical;
public:
	proyectil(){
		activo=false;
		velocidadVertical=100;
	}
	
	void activar(int x, int y) {
		posX = x;
		posY = y - 1;
		activo = true;
		tInicio = clock();
	}
	
	void desactivar() {
		activo = false;
	}
	
	void actualizar() override {
		if (!activo) return;
		
		if (clock() - tInicio >= (velocidadVertical * CLOCKS_PER_SEC / 1000)) {
			gotoxy(posX, posY);
			putchar(' ');
			
			posY--;
			
			if (posY < 0) {
				desactivar();
			}
			
			tInicio = clock();
		}
	}
	
	void dibujar() override {
		if (!activo) return;
		
		gotoxy(posX, posY);
		putchar('|');
	}
	
	bool estaActivo() {
		return activo;
	}
	
	int getX() {
		return posX;
	}
	
	int getY() {
		return posY;
	}
};


//gestor de interface 

class pantalla {
public:
	void mostrarPantallaInicial() {
		clrscr();
		textcolor(LIGHTCYAN);
		gotoxy(10, 3);
		cout << "DEFENSA EN EL GRAN CANON DE TITAN";
		gotoxy(5, 12);
		cout << "Dispara algunos proyectiles.";
		gotoxy(5, 13);
		cout << "Suerte y espera los refuerzos.";
		textcolor(WHITE);
		gotoxy(5, 15);
		cout << "Juega con las flechas DERECHA e IZQUIERDA";
		gotoxy(5, 16);
		cout << "Dispara con ESPACIO" ;
		
		gotoxy(10, 19);
		cout << "Presiona cualquier tecla para comenzar...";
		getch(); // Espera a que el jugador presione una tecla
	}
	
	void mostrarPantallaGameOver(int puntaje) {
		clrscr();
		textcolor(RED);
		gotoxy(10, 6);
		cout << "GAME OVER";
		textcolor(LIGHTMAGENTA);
		cout << "Puntaje final: " << puntaje;
		textcolor(WHITE);
		esperar(10000);
		mostrarPantallaInicial();
	}
	
	void mostrarPantallaVictoria(int puntaje) {
		clrscr();
		textcolor(GREEN);
		gotoxy(10, 6);
		textcolor(WHITE);
		cout << "FELICITACIONES!";
		gotoxy(10, 16);
		textcolor(LIGHTBLUE);
		cout << "Puntaje final: " << puntaje;
		textcolor(WHITE);
		esperar(10000); // Espera 7 segundos
		mostrarPantallaInicial();
	}
	
	void dibujarMarco() {
		textcolor(WHITE);
		// solo agrego línea inferior
		gotoxy(1, VENTANA + 2);
		putchar(218); 
		gotoxy(1, VENTANA + 3);
		putchar(179); 
		gotoxy(ANCHO, VENTANA + 2);
		putchar(191); 
		gotoxy(ANCHO, VENTANA + 3);
		putchar(179);
		gotoxy(1, VENTANA + 4);
		putchar(195); 
		gotoxy(1, VENTANA + 5);
		putchar(179);
		gotoxy(ANCHO, VENTANA + 4);
		putchar(180); 
		gotoxy(ANCHO, VENTANA + 5);
		putchar(179);
		gotoxy(1, VENTANA + 6);
		putchar(192); 
		gotoxy(ANCHO, VENTANA + 6);
		putchar(217); 
		for (int i = 2; i <= ANCHO -1; i++) {
			gotoxy(i, VENTANA + 2);
			putchar(196);
			gotoxy(i, VENTANA + 4);
			putchar(196);
			gotoxy(i, VENTANA + 6);
			putchar(196);
		}
		gotoxy(ANCHO/2, VENTANA + 2);
		putchar(194);
		gotoxy(ANCHO/2, VENTANA + 3);
		putchar(179);
		gotoxy(ANCHO/2, VENTANA + 4);
		putchar(193);
		
		textcolor(WHITE);
	}
	
	void actInterface(int vidas, int puntaje) {
		gotoxy(5, VENTANA + 3);
		cout << "VIDAS: " << vidas;
		gotoxy(21, VENTANA + 3);
		cout << "   PUNTAJE: " << puntaje;
		textcolor(LIGHTGREEN);
		gotoxy(2,VENTANA + 5);
		cout << mensaje;
		textcolor(WHITE);
	}

};


//juego 

class Juego {
private:
	pantalla gestorPantalla;
	terreno zona;
	nave gladiador;
	naveEnemiga enemigo;
	proyectil proyectiles[5];
	
	clock_t tInicioScroll;
	clock_t tInicioLateral;
	
	void inicializar() {
		gladiador = nave();
		enemigo = naveEnemiga();
		for (int i = 0; i < 5; i++) {
			proyectiles[i] = proyectil();
		}
		puntaje = 0;
		desplazamiento = 0;
		VELOCIDAD = VELOCIDAD_INICIAL;
		
		zona.inicializarCanon();
		clrscr();
		
		tInicioScroll = clock();
		tInicioLateral = clock();
		mensaje = " ";
	}
	
	void manejarEntrada() {
		gladiador.mover();
		if (gladiador.dispara) {
			for (int i = 0; i < 5; i++) {
				if (!proyectiles[i].estaActivo()) {
					proyectiles[i].activar(gladiador.getX(), gladiador.getY());
					break;
				}
			}
			gladiador.dispara = false;
		}
	}
	
	void actualizarJuego() {
		if (clock() - tInicioScroll >= (VELOCIDAD * CLOCKS_PER_SEC / 1000)) {
			desplazamiento++;
			puntaje += 10;
			zona.dibujar();
			enemigo.actualizarDesplazamiento(desplazamiento);
			tInicioScroll = clock();
			if (desplazamiento % 25 == 0 && !enemigo.estaActiva()) {
				enemigo.activar(desplazamiento);
			}
		}
		
		if (clock() - tInicioLateral >= (VELOCIDAD * 2 * CLOCKS_PER_SEC / 1000)) {
			enemigo.actualizar();
			tInicioLateral = clock();
		}
		for (int i = 0; i < 5; i++) {
			if (proyectiles[i].estaActivo()) {
				proyectiles[i].actualizar();
				if (enemigo.estaActiva() &&
					proyectiles[i].getX() == enemigo.getX() &&
					proyectiles[i].getY() == enemigo.getY()) {
					enemigo.desactivar();
					proyectiles[i].desactivar();
					puntaje += 100;
					mensaje = "Excelente Puntería                  ";
				}
			}
		}
		
		gladiador.manejarColision(zona.fondo(gladiador.getX()));
		if (enemigo.estaActiva() &&
			gladiador.getX() == enemigo.getX() &&
			gladiador.getY() == enemigo.getY()) {
			gladiador.manejarColision('X'); 
		}
	}
	
	void dibujarJuego() {
		gestorPantalla.dibujarMarco();
		gestorPantalla.actualizarInterface(gladiador.getVidas(), puntaje);
		enemigo.dibujar();
		gladiador.dibujar();
		for (int i = 0; i < 5; i++) {
			proyectiles[i].dibujar();
		}
	}
	
	bool verificarEstado() {
		if (gladiador.getVidas() <= 0) {
			gestorPantalla.mostrarPantallaGameOver(puntaje);
			return false;
		}
		if (desplazamiento >= 800) {
			gestorPantalla.mostrarPantallaVictoria(puntaje);
			return false;
		}
		return true;
	}
	
public:
		void ejecutar() {
			while (true) {
				gestorPantalla.mostrarPantallaInicial();
				inicializar();
				while (true) {
					manejarEntrada();
					actualizarJuego();
					dibujarJuego();
					if (!verificarEstado()) {
						break;
					}
				}
			}
		}
};

int main (int argc, char *argv[]) {
	Juego juego;
	juego.ejecutar();
	return 0;
}

