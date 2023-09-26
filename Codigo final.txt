const int SER = 2;
const int RCLK = 3;
const int SRCLK =4;
int cpatrones, tpatrones;
char opcion;

int **puntero_matriz, ***puntero_matriz3d;
 
void definematrizbidi(){
  puntero_matriz = new int*[8];
  for(int i=0; i<8; i++){
    puntero_matriz[i] = new int[8];
  }
  for(int j=0; j<8; j++){
    for(int k=0; k<8; k++){
      *(*(puntero_matriz+j)+k)=0;     
    }
  }
}

void definematriztridi(int cpatrones){
  puntero_matriz3d = new int**[cpatrones];
  for(int i=0; i<cpatrones; i++){
    puntero_matriz3d[i] = new int*[8];
  
  	for(int j=0; j<8; j++){
    puntero_matriz3d[i][j] = new int[8];
  }
  }
  for(int i=0; i<cpatrones; i++){
    for(int j=0; j<8; j++){
      for(int k=0; k<8; k++){
        *(*(*(puntero_matriz3d+i)+j)+k)=0;
      }
    }
  }
}

void RecibirMatrizbidi(){
  char num_vol = 49;
  String valor; 
  long int fila;
  Serial.println("Para ingresar su patron, debe tener en cuenta que:");
  Serial.println("- El numero 1 se reflejara como el led encendido ");
  Serial.println("- El numero 0 se reflejara como el led apagado ");
  Serial.println("- Debe ingresar fila por fila");
  for(int i=0; i<=7; i++){
     Serial.print("Ingrese la fila ");
     Serial.println(i+1);
     while (Serial.available()==0){}
     valor = Serial.readStringUntil('\n');
     valor = num_vol + valor;
     fila = valor.toInt();
     for (int j=7; j>=0; j--){      
         *(*(puntero_matriz+i)+j)=fila%10;          
         fila=fila/10;                            
      }
   }  
} 

void RecibirMatriztridi(int cpatrones){
  char num_vol = 49;
  String valor; 
  long int fila;
  Serial.println("Para ingresar su patron, debe tener en cuenta que:");
  Serial.println("- El numero 1 se reflejara como el led encendido ");
  Serial.println("- El numero 0 se reflejara como el led apagado ");
  Serial.println("- Debe ingresar fila por fila");
  
  for(int i=0; i<cpatrones; i++){
    Serial.print("A continuacion ingrese la matriz ");
    Serial.println(i+1);
  for(int j=0; j<=7; j++){
     Serial.print("Ingrese la fila ");
     Serial.println(j+1);
     while (Serial.available()==0){}
     valor = Serial.readStringUntil('\n');
     valor = num_vol + valor;
     fila = valor.toInt();
     for (int k=7; k>=0; k--){      
         *(*(*(puntero_matriz3d+i)+j)+k)=fila%10;          
        fila=fila/10;                            
      }
   }
  }
} 
void manual(){
   Serial.println("**Manual de uso**");
    delay(700);
    Serial.print("- Si quiere ingresar un patron para que se muestre en los Leds, ");
    delay(700);
    Serial.println("tenga en cuenta que debe");
    delay(700);
    Serial.print("tener previamente visualizado el patron y unicamente ");
    delay(700);
    Serial.println("ingresar el numero 1, en caso de querer ver el");
    delay(700);
    Serial.print("led de la fila indicada prendido, ");
    delay(700);
    Serial.println("o 0 si lo desea ver apagado.");
    delay(700);
    Serial.print("-Tenga en cuenta que solo puede ingresar ocho ");
    delay(700); 
    Serial.println("digitos cuando se le pida la fila, en caso de no hacerlo");
    delay(700);
    Serial.println("puede que el resultado no sea lo que usted esperaba.");
    delay(700);
    Serial.println("Ejemplo de como debe ingresar una fila:");
    delay(700);
    Serial.println("Fila #n: 10010001");
    delay(700);
}

void relojregistro(int parametro){
  digitalWrite(parametro, 0);
  digitalWrite(parametro, 1);
  digitalWrite(parametro, 0);
}

void imagen(){
  int m;   
  for (int i=7; i>=0; i--){
    for (int j=7; j>=0; j--){
      m=*(*(puntero_matriz+i)+j);      
      digitalWrite(SER, m);
      relojregistro(SRCLK);
      relojregistro(RCLK);
    }
    
  }
}

void auxiliar(int tpatrones, int cpatrones){
  int m;
  for (int i=0; i<cpatrones; i++){
    for (int j=7; j>=0; j--){
      for(int k=7; k>=0; k--){
      m=*(*(*(puntero_matriz3d+i)+j)+k);      
      digitalWrite(SER, m);
      relojregistro(SRCLK);
      relojregistro(RCLK); 
      }
    }    
    delay(tpatrones);
  } 
}

void publik(){
  Serial.println("Bienvenido al menu de inicio");
  Serial.println("Ingrese el numero de la opcion que desea realizar");
  Serial.println("1. Verificar el funcionamiento de los 64 LEDs");
  Serial.println("2. Mostrar un patron");
  Serial.println("3. Secuencia de patrones");
  Serial.println("4. Manual de uso");
}

void verificacion(){
  for(int k=0; k<64; k++){
     digitalWrite(SER, 1);
     relojregistro(SRCLK); //Activar el flanco de subido
     relojregistro(RCLK); //Activar el flanco de subido del registro de salida
  }
  delay(5000);
    for(int k=0; k<64; k++){
     digitalWrite(SER, 0);
     relojregistro(SRCLK);
     relojregistro(RCLK);
     }
}  

void setup(){
  Serial.begin(9600);
  
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  
  digitalWrite(2, 0);
  digitalWrite(3, 0);
  digitalWrite(4, 0);
  
}

void loop(){
  publik();
  
  while(Serial.available()==0){}
  opcion = Serial.read();
  
  switch (opcion) {
    case 49:

      verificacion();
      delay(3000);
      break;
    case 50:

      definematrizbidi();
      RecibirMatrizbidi();
      imagen();
      break;
    case 51:

      Serial.println("Ingrese la cantidad de patrones que desea: ");
      while(Serial.available()==0){}
      cpatrones = Serial.parseInt();
    	//cpatrones = 4;
      
      Serial.println("Ingrese el tiempo entre patrones en milisegundos: ");
      while(Serial.available()==0){};
      tpatrones = Serial.parseInt();
    
      definematriztridi(cpatrones);
      RecibirMatriztridi(cpatrones);
      auxiliar(tpatrones, cpatrones);
      break;
    case 52:
     manual();
    break;
    default:
      Serial.println("Error!, El dato ingresado no es valido");
      break;

  }
}