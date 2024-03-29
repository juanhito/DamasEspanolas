#include<iostream>//Lib. que maneja entrada y salida cout/cin
#include<exception> //Lib. que me permite abortar el juego
using namespace std;
#define NO_JUGAR 0
#define ESPACIO_VACIO 1
#define FICHAS_BLANCAS 2
#define FICHAS_NEGRAS 3
#define FILAS 8
#define COLUMNAS 8
#define REINAS_BLANCAS 4
#define REINAS_NEGRAS 5
int intro();// Funcion que pinta y colorea a la Universidad Europea
void intercambio(int matrix[FILAS][COLUMNAS], int filaOrigen, int colOrigen, int filaDestino, int colDestino);//Intercambia fichas
int turno(int matrix[][COLUMNAS], int jugador,int filaOrigen,int colOrigen,int filaDestino,int colDestino);//Gestiona los turno y movimientos
char simbolos(int i);//Me ayuda a rellenar mi matrix, convierte los numeros en simbolos
void tablero(int matrix[FILAS][COLUMNAS]);//Dibuja el tablero

int intro(){
    int op=0;
    do{
       do{
            system("clear");
            cout<<"\t\t_____________________________________________________________________"<<endl;
            cout<<"\t\t                                                                    "<<endl;
            cout<<"\t\t UNIVERSIDAD EUROPEA - ESCUELA DE ARQUITECTURA, INGENIERIA Y DISEÑO"<<endl;
            cout<<"\t\t_____________________________________________________________________"<<endl<<endl;
            cout<<"\t\tProf.:Christian Sucuzhanay.                  Alumno : XXXXXXXXXXX"<<endl<<endl<<endl;
            cout<<"\t\t              << JUEGO DE LAS DAMAS ESPANOLAS >>"<<endl<<endl;
            cout<<"\t\t\t    ** Seleccionar una opción del menu [ 0-9] **"<<endl<<endl;
            cout<<"\t\t\t\t  [ 1 ] Ver reglas del juego "<<endl;
            cout<<"\t\t\t\t  [ 2 ] Jugar"<<endl;
            cout<<"\t\t\t\t  [ 0 ] SALIR"<<endl<<endl;
            cout<<"\t\t\t              Ingrese su opción ? : ";
            cin>>op;
        } while (op<0||op>2);
            switch (op){
                case 1:
                    system("clear");
                    cout<<"\t\t_____________________________________________________________________"<<endl;
                    cout<<"\t\t                                                                    "<<endl;
                    cout<<"\t\t UNIVERSIDAD EUROPEA - ESCUELA DE ARQUITECTURA, INGENIERIA Y DISEÑO"<<endl;
                    cout<<"\t\t_____________________________________________________________________"<<endl<<endl;
                    cout<<"\t\tProf.Javier Sanchez S.                  Alumno: Christian Sukuzhanay"<<endl<<endl<<endl;
                    cout<<"\t\t            << REGLAS DEL JUEGO DE LAS DAMAS ESPANOLAS >>\n";
                    cout<<"\t\t           ----------------------------------------------\n\n";
                    cout<<"\t\t1.- Inician el juego las fichas blancas por defecto"<<endl<<endl;
                    cout<<"\t\t2.- Las fichas SOLO se mueven 1 casilla hacia ADELANTE y en DIAGONAL\n ";
                    cout<<"\t\t    excepto al comer FICHA que pueden saltar\n\n";
                    cout<<"\t\t3.- Las fichas SALTAN mas de una casilla  SOLO cuando haya una ficha\n ";
                    cout<<"\t\t    contaria y la siguiente este vacia\n\n "; 
                    cout<<"\t\t4.- Gana quien coma mas fichas \n\n";
                    cout<<"\t\t5.- Si pasan mas de 2 horas sin que nadie gane se declara EMPATE\n\n\n\n ";
                    cout<<"\t\t\t\t PULSE [ 0 ] para SALIR: ";
                    cin>>op;
                    intro();
                case 2:
                    break;
                case 0:
                    system("clear");
                    abort();               
            }
        return 0;
    }while(op!=0);
    abort();
    
}

int turno(int matrix[FILAS][COLUMNAS], int jugador,int filaOrigen,int colOrigen,int filaDestino,int colDestino)//Gestiona movimientos y turnos
{
    int comerFichaBlancas;
    int comerFichaNegras;
    
    if((filaOrigen < 0 && FILAS <= filaOrigen)&&(colOrigen < 0 && COLUMNAS <= colOrigen)){ // Comprueba filas y col esten dentro del tablero
        cout<<"\n No ves que el tablero no tiene esa posicion ? Estas fuera del tablero\n";
        return -1;
    }

    if((filaDestino < 0 && FILAS <= filaDestino)&&(colDestino < 0 && COLUMNAS<= colDestino)){// Comprueba filas y col esten dentro del tablero
        cout<<"\n No ves que el tablero no tiene esa posicion ? Estas fuera del tablero\n";
        return -1;
    }
        
    if(jugador == FICHAS_BLANCAS||jugador==REINAS_BLANCAS){//Comprueba que muevas solo donde haya fichas blancas
        if(matrix[filaOrigen][colOrigen] != FICHAS_BLANCAS &&matrix[filaOrigen][colOrigen] != REINAS_BLANCAS){
            cout<<"\n <<< Eres CIEGO ? , No tienes fichas ** BLANCAS **  en esa posicion >>>\n";
            return -1;
        }
    } else { //Comprueba que no muevas fichas negras
        if(matrix[filaOrigen][colOrigen] != FICHAS_NEGRAS && matrix[filaOrigen][colOrigen]!=REINAS_NEGRAS){
            cout<<"\n <<< Eres CIEGO ? , No tienes fichas ** NEGRAS **  en esa posicion >>>\n";
            return -1;
        }
    }
    
    if(matrix[filaDestino][colDestino] != ESPACIO_VACIO){//Comprueba que muevas solo espacios vacios.
        cout<<"\nSolo puedes mover a un espacios VACIOS!! como tu cerebro, jeje ( v )";
        return -1;
    }
    
    if(jugador == FICHAS_BLANCAS){//Comprueba que el movimiento de las BLANCAS no sea hacia atras
        if(filaOrigen >= filaDestino&&matrix[filaOrigen][colOrigen]!=REINAS_BLANCAS){
            cout<<"\nNo te da o que ??? No puedes mover hacia atras o quedarte en el mismo lugar\n";
            return -1;
        }


    } else {//Comprueba que el movimiento de las NEGRAS no sea hacia atras
        if(filaOrigen <= filaDestino&&matrix[filaOrigen][colOrigen]!=REINAS_NEGRAS){
            cout<<"\nNo te da o que ??? No puedes mover hacia atras o quedarte en el mismo lugar\n";
            return -1;
        }
    }
      
    //Comprueba si es un movimiento normal, una sola posicion
    if(filaOrigen - filaDestino == -1 || filaOrigen - filaDestino == 1){
        if(colOrigen - colDestino == 1 || colOrigen - colDestino == -1){
            intercambio(matrix,filaOrigen,colOrigen,filaDestino,colDestino);
            if(jugador==FICHAS_BLANCAS){
                if(filaDestino==7){
                    matrix[filaDestino][colDestino]=REINAS_BLANCAS;//cuando llega a la ultima fila se cambia a reina
                }
            }
            if(jugador==FICHAS_NEGRAS){
                if(filaDestino==0){
                    matrix[filaDestino][colDestino]=REINAS_NEGRAS;//cuando llega a la ultima fila se cambia a reina
                }
            }
            return 0;
        }


    } else{
        if(matrix[filaOrigen][colOrigen]==REINAS_BLANCAS) {


            if (filaOrigen - filaDestino == colOrigen - colDestino || filaOrigen-filaDestino==colDestino-colOrigen) {//comprueba que se mueve en diagonal
                if(filaOrigen-filaDestino>0&&colOrigen-colDestino>0){//cada if mira en que direccion se mueve y si hay fichas en esa diagonal en cuanto encuentra una para
                    for(int i=0;i<8;i++){
                        if(matrix[filaOrigen-i][colOrigen-i]==FICHAS_NEGRAS
                        ||matrix[filaOrigen-i][colOrigen-i]==REINAS_NEGRAS){//comprueba si se mueve arriba a la izquierda si hay fichas en medio y si las hay se las come
                            matrix[filaOrigen-i][colOrigen-i]=1;
                            if(matrix[filaOrigen-i-1][colOrigen-i-1]!=ESPACIO_VACIO){//comprueba que no haya 2 fichas en medio
                                cout<<"Hay otra ficha en medio";
                                return -1;
                            }
                            else{
                                intercambio(matrix, filaOrigen, colOrigen, filaDestino, colDestino);

                            }
                            i=8;
                        }
                    }
                }
                else if(filaOrigen-filaDestino>0&&colOrigen-colDestino<0){
                    for(int i=0;i<8;i++){
                        if(matrix[filaOrigen-i][colOrigen+i]==FICHAS_NEGRAS
                        ||matrix[filaOrigen-i][colOrigen+i]==REINAS_NEGRAS){//comprueba si en esa direccion hay fichas para ver si puede  comer
                            matrix[filaOrigen-i][colOrigen+i]=1;
                            if(matrix[filaOrigen-i-1][colOrigen+i+1]!=ESPACIO_VACIO){//comprueba quee no haya una ficha detras
                                cout<<"Hay otra ficha en medio";
                                return -1;
                            }
                            else{
                                intercambio(matrix, filaOrigen, colOrigen, filaDestino, colDestino);

                            }
                            i=8;
                        }
                    }
                }
                else if(filaOrigen-filaDestino<0&&colOrigen-colDestino>0){
                    for (int i = 0; i <8; i++) {
                        if (matrix[filaOrigen + i][colOrigen - i] == FICHAS_NEGRAS ||
                            matrix[filaOrigen + i][colOrigen - i] == REINAS_NEGRAS) {//comprueba si en esta direccion hay fichas y si las hay se las come
                            matrix[filaOrigen + i][colOrigen - i] = 1;
                        }
                        if(matrix[filaOrigen+i+1][colOrigen-i-1]!=ESPACIO_VACIO){//comprueba que no haya 2 fichas
                            cout<<"Hay otra ficha en medio";
                            return -1;
                        }
                        else{
                            intercambio(matrix, filaOrigen, colOrigen, filaDestino, colDestino);

                        }
                        i=8;

                    }

                }
                else if(filaOrigen-filaDestino<0&&colOrigen-colDestino<0) {
                    for (int i = 0; i < 8; i++) {
                        if (matrix[filaOrigen + i][colOrigen + i] == FICHAS_NEGRAS ||
                            matrix[filaOrigen + i][colOrigen + i] == REINAS_NEGRAS) {
                            matrix[filaOrigen + i][colOrigen + i] = 1;

                            if (matrix[filaOrigen + i + 1][colOrigen + i + 1]!=ESPACIO_VACIO) {
                                cout << "Hay otra ficha en medio";
                                return -1;
                            } else {
                                intercambio(matrix, filaOrigen, colOrigen, filaDestino, colDestino);

                            }
                            i = 8;
                        }
                    }
                    intercambio(matrix, filaOrigen, colOrigen, filaDestino, colDestino);
                }



            }
        }
        else if (matrix[filaOrigen][colOrigen]==REINAS_NEGRAS){//cada if comprueba si hay fichas contrarias en una direccion
                if (filaOrigen - filaDestino == colOrigen - colDestino || filaOrigen-filaDestino==colDestino-colOrigen) {//comprueba que se mueva en diagonal
                    if(filaOrigen-filaDestino>0&&colOrigen-colDestino>0){
                        for(int i=0;i<8;i++){
                            if(matrix[filaOrigen-i][colOrigen-i]==FICHAS_BLANCAS
                               ||matrix[filaOrigen-i][colOrigen-i]==REINAS_BLANCAS){
                                matrix[filaOrigen-i][colOrigen-i]=1;
                                if(matrix[filaOrigen-i-1][colOrigen-i-1]!=ESPACIO_VACIO){
                                    cout<<"Hay otra ficha en medio";
                                    return -1;
                                }
                                else{
                                    intercambio(matrix, filaOrigen, colOrigen, filaDestino, colDestino);
                                }
                                i=8;
                            }
                        }
                    }
                    else if(filaOrigen-filaDestino>0&&colOrigen-colDestino<0){
                        for(int i=0;i<8;i++){
                            if(matrix[filaOrigen-i][colOrigen+i]==FICHAS_BLANCAS
                               ||matrix[filaOrigen-i][colOrigen+i]==REINAS_BLANCAS){
                                matrix[filaOrigen-i][colOrigen+i]=1;
                                if(matrix[filaOrigen-i-1][colOrigen+i+1]!=ESPACIO_VACIO){
                                    cout<<"Hay otra ficha en medio";
                                    return -1;
                                }
                                else{
                                    intercambio(matrix, filaOrigen, colOrigen, filaDestino, colDestino);

                                }
                                i=8;
                            }
                        }
                    }
                    else if(filaOrigen-filaDestino<0&&colOrigen-colDestino>0){
                        for (int i = 0; i <8; i++) {
                            if (matrix[filaOrigen + i][colOrigen - i] == FICHAS_BLANCAS ||
                                matrix[filaOrigen + i][colOrigen - i] == REINAS_BLANCAS) {
                                matrix[filaOrigen + i][colOrigen - i] = 1;
                            }
                            if(matrix[filaOrigen+i+1][colOrigen-i-1]!=ESPACIO_VACIO){
                                cout<<"Hay otra ficha en medio";
                                return -1;
                            }
                            else{
                                intercambio(matrix, filaOrigen, colOrigen, filaDestino, colDestino);
                            }
                            i=8;
                        }
                    }
                    else if(filaOrigen-filaDestino<0&&colOrigen-colDestino<0) {
                        for (int i = 0; i < 8; i++) {
                            if (matrix[filaOrigen + i][colOrigen + i] == FICHAS_BLANCAS ||
                                matrix[filaOrigen + i][colOrigen + i] == REINAS_BLANCAS) {
                                matrix[filaOrigen + i][colOrigen + i] = 1;

                                if (matrix[filaOrigen + i + 1][colOrigen + i + 1] !=ESPACIO_VACIO) {
                                    cout << "Hay otra ficha en medio";
                                    return -1;
                                } else {
                                    intercambio(matrix, filaOrigen, colOrigen, filaDestino, colDestino);
                                }
                                i = 8;
                            }
                        }
                        intercambio(matrix, filaOrigen, colOrigen, filaDestino, colDestino);
                    }
                }
                return 0;
        }
    }
    //Comprueba si ha comido ficha de adversario
    if(filaOrigen - filaDestino == -2 || filaOrigen - filaDestino == 2){
        if(colOrigen - colDestino == -2 || colOrigen - colDestino == 2){
            // Comprueba si en la posicion del salto hay ficha contraria
            if(filaOrigen < filaDestino){ // Movimiento hacia abajo
                comerFichaBlancas = filaOrigen + 1;
            } else { // Movimiento hacia arriba
                comerFichaBlancas = filaOrigen - 1;
            }
            if(colOrigen < colDestino){ // Movimiento hacia abajo
                comerFichaNegras = colOrigen + 1;
            } else { // Movimiento hacia arriba
                comerFichaNegras = colOrigen - 1;
            }

            if(jugador==FICHAS_BLANCAS && matrix[comerFichaBlancas][comerFichaNegras]!=FICHAS_NEGRAS)
            {
                cout<<"\nSolo puedes saltar si COMES FICHA"<<comerFichaBlancas<<comerFichaNegras;
                return -1;
            }
            if(jugador==FICHAS_NEGRAS && matrix[comerFichaBlancas][comerFichaNegras] != FICHAS_BLANCAS){
                cout<<"\nSolo puedes saltar si COMES FICHA \n";
                return -1;
            }

            matrix[comerFichaBlancas][comerFichaNegras] = 1;
            intercambio(matrix,filaOrigen,colOrigen,filaDestino,colDestino);
            if(jugador==FICHAS_BLANCAS){
                if(filaDestino==7){
                    matrix[filaDestino][colDestino]=REINAS_BLANCAS;//cuando llega a la ultima fila se cambia a reina
                }
            }
            if(jugador==FICHAS_NEGRAS){
                if(filaDestino==0){
                    matrix[filaDestino][colDestino]=REINAS_NEGRAS;//cuando llega a la ultima fila se cambia a reina
                }
            }
            return 0;
        }
    }
    cout<<"Las fichas solo se pueden mover DIAGONALMENTE\n";
    return -1;
}
void tablero(int matrix[FILAS][COLUMNAS])//Pinta tablero
{
    int pintarFilas, pintarCol;
    system("clear");
    cout<<"\t\t_____________________________________________________________________"<<endl;
    cout<<"\t\t                                                                    "<<endl;
    cout<<"\t\t UNIVERSIDAD EUROPEA - ESCUELA DE ARQUITECTURA, INGENIERIA Y DISEÑO"<<endl;
    cout<<"\t\t_____________________________________________________________________"<<endl<<endl;
    cout<<"\t\tProf.: Christian Sucuzhanay                  Alumno: XXXXXXXXXXXXX"<<endl<<endl<<endl;
    cout<<"\t\t                << TABLERO DE LAS DAMAS ESPANOLAS >>"<<endl<<endl;
    cout<<"\n\t\t\t\t     B = fichas BLANCAS";
    cout<<"\n\t\t\t\t     N = fichas NEGRAS";
    cout<<"\n\t\t\t\t     v = espacios VACIOS jugables";
    cout<<"\n\n\t\t\t\t   +---+---+---+---+---+---+---+---+\n"; 
    for (pintarFilas=0; pintarFilas<FILAS; ++pintarFilas)
    {
        cout<<"\t\t\t\t"<<  pintarFilas+1  <<"  | "; // Pinto filas
        for (pintarCol=0; pintarCol<COLUMNAS; ++pintarCol)
        {
            cout<<simbolos(matrix[pintarFilas][pintarCol])<< " | " ;//Rellenamos tablero
        }
        cout<<"\n";
        cout<<"\t\t\t\t   +---+---+---+---+---+---+---+---+\n";
    }
    cout<<"\n\t\t\t\t     a   b   c   d   e   f   g   h\n\n\n";//Imprime leyenda para de colunmnas
}


void intercambio(int matrix[FILAS][COLUMNAS], int filaOrigen, int colOrigen, int filaDestino, int colDestino)//Cambia fichas en la matrix
{
  int temp;// Para almacenar mientras intercambio las coordenadas
  temp = matrix[filaOrigen][colOrigen];
  matrix[filaOrigen][colOrigen] = matrix[filaDestino][colDestino];
  matrix[filaDestino][colDestino] = temp;
}


char simbolos(int i)//Cambia letras por numeros
{
    switch(i)
    {
  	case 0:
            return ' ';//no jugable
        case 1:
            return 'v';//espacio vacio  
        case 2:
            return 'b';//blancas
        case 3:
            return 'n';//negras
        case 4:
            return 'B';//Reina Blanca
        case 5:
            return 'N';//Reina Negra
    }
    return ('?');
}


int main()//Programa principal
{
    int filaOrigen, filaDestino;//Para almacernar las filas 1-8
    char colOrigen, colDestino;//Para almacenar el valor de las columnas que son a-h
    int matrix[FILAS][COLUMNAS]={//Matrix de fichas
                {0,2,0,2,0,2,0,2},
                {2,0,2,0,2,0,2,0},
                {0,2,0,2,0,2,0,2},
                {1,0,1,0,1,0,1,0},
                {0,1,0,1,0,1,0,1}, 
                {3,0,2,0,3,0,3,0},
                {0,3,0,3,0,3,0,3},
                {1,0,3,0,3,0,3,0}};//Tablero 0=no se puede, 1=vacio, 2=Blancas, 3=Negras
    intro();//Funcion que pinta y colorea Universidad Europea
    system("clear");//Limpia pantalla
    for(;;)
    {//Bucle infinito para captura y validacion de coordenada de ficha
        tablero(matrix);//Dibujo el tablero, TURNO BLANCAS, le paso la matrix d para dibujar el tablero
        while(1){//Mientras no sean validas las coordenadas no sale de este while
            cout<<"\nTURNO de las  * BLANCAS *  Ingrese FILA 1-8 y COLUMNA a-h de la ficha que desea mover, por ejemplo 3b\n";
            cin>>filaOrigen>>colOrigen;//Capturo coordenada de origen Blancas
            colOrigen = tolower(colOrigen);//Permite que el usuario meta las columnas en MAYUSCULAS o minusculas
    	    cout<<"Introduzca FILA 1-8 y COLUMNA a-h del destino de la ficha a mover,  por ejemplo 4a \n";
            cin>>filaDestino>>colDestino;//Capturo coordenada de destino Blancas
            colDestino = tolower(colDestino);
        	if(turno(matrix, FICHAS_BLANCAS, filaOrigen-1,colOrigen - 'a',filaDestino-1,colDestino - 'a') == 0)//Compruebo que sean validos las coordenadas
        	    break;
            cout<<"\nINTENTA de nuevo :\n";
        }
        system("clear");
        tablero(matrix);//Dibujo el tablero, TURNO NEGRAS, le paso la matrix d para dibujar el tablero
        while(1){//Mientras no sean validas las coordenadas no sale de este while
            cout<<"\nTURNO de las  * NEGRAS *  Ingrese FILA 1-8 y COLUMNA a-h de la ficha que desea mover, por ejemplo 6g\n";
            cin>>filaOrigen>>colOrigen;//Capturo coordenada de origen Negras
            colOrigen = tolower(colOrigen);
    	    cout<<"Introduzca FILA 1-8 y COLUMNA a-h del destino de la ficha a mover,  por ejemplo 5h \n";
            cin>>filaDestino>>colDestino;//Capturo coordenada de destino Negras
            colDestino = tolower(colDestino);//Permite que el usuario meta las columnas en MAYUSCULAS o minusculas
        	if(turno(matrix, FICHAS_NEGRAS, filaOrigen-1,colOrigen - 'a',filaDestino-1,colDestino - 'a') == 0)//Comprueba que sean validos las coordenadas
        	    break;
            cout<<"\nINTENTA de nuevo :\n)";
        }
    }
    return 0;
}
