unsigned long Time = millis();   //Tiempo de programa
unsigned long *ptrTime;
int Duracion = 7000;    //Duración predeterminada en milisegundos
int **puntero_clear;  //Puntero matriz clear
int **puntero_full;   //puntero matriz full
//int image[8]={};
int **puntero_image;  //puntero matriz imagen
int Cont = 1;     //Un contador sin nada especial
int8_t nFilas = 8;    //Numero de filas
int8_t nCol = 2;    //Numero de columnas
int8_t SER  = 3;    //Entrada
int8_t RCLK = 2;    //Reloj de regristo de salida
int8_t SRCLK = 4;   //Reloj de desplazamiento
int8_t Option;
void ledWrite(int GLed, int RLed){  //Gled = Columnas; Rled = Filas
  
   /*Los datos se envian de tal manera que los primeros que ingresan 
   son los ultimos en la posicion del integrado, si estan en */ 
   
   shiftOut(SER, SRCLK, LSBFIRST, RLed);
   shiftOut(SER, SRCLK, MSBFIRST, GLed);
  
   /*Activar el flanco de subido del regristo de salida. */
   digitalWrite(RCLK, LOW);
   digitalWrite(RCLK, HIGH);
   digitalWrite(RCLK, LOW);
}
//Creo una matriz para que todos los led´s este en LOW
void clear(){
  
   puntero_clear = new int*[nFilas];
  
   for(int i = 0;i<nFilas;i++){
   puntero_clear[i] = new int[nCol];
   }
  
   for(int i = 0;i<nFilas;i++,Cont = Cont*2){
      *(*(puntero_clear+i)+0) = 255;
      *(*(puntero_clear+i)+1) = Cont;
   }
}
void viewMatriz(int **puntero, int nFilas, int nCol){
 for(int i=0;i<nFilas; i++){
    ledWrite((*(*(puntero+i)+0)),(*(*(puntero+i)+1)));         
 }
}
void full(){
  
   puntero_full = new int*[nFilas];
  
   for(int i = 0;i<nFilas;i++){
   puntero_full[i] = new int[nCol];
   }
  
   for(int i = 0;i<nFilas;i++,Cont = Cont*2){
      *(*(puntero_full+i)+0) = 0;
      *(*(puntero_full+i)+1) = Cont; 
   }
}
void loop(){
  
  Cont=1;
  ptrTime=&Time;
  *ptrTime = millis();
  full();
  while (Time%Duracion < Duracion/2){    
    *ptrTime = millis();
    viewMatriz(puntero_full,nFilas,nCol);
  }
  clear();
  viewMatriz(puntero_clear,nFilas,nCol); 
  Serial.println(" ");
  Serial.println("       One moment, plis");
  delay(3000);  //Esto es para que el programa no se muera
}