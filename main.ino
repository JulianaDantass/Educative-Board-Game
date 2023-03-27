
// include the library code:
#include <LiquidCrystal.h>
#include <Keypad.h>

#define buzzer A5

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

//definicao quantidade linhas e colunas
const byte LINHAS= 4;
const byte COLUNAS= 4;

//definicao dos pinos das linhas e colunas
byte PinosLinhas[LINHAS]= {A1, A2, A3, A4};
byte PinosColunas[COLUNAS]= {10, 9, 8, 7};

char matriz_teclas[LINHAS][COLUNAS]=
{
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'},
};

Keypad keypad= Keypad (makeKeymap(matriz_teclas),PinosLinhas, 
                            PinosColunas, LINHAS, COLUNAS);

//variaveis
int colunaLCD= 0;
int linhaLCD= 0;
int i= 1;
int pontos1= 0;
int pontos2= 0;
int ultimo1= 1;           //os dois vao comecar tentando pelo caminho dificil
int ultimo2= 1;           //os dois vao comecar tentando pelo caminho dificil
int acertos1 = 0;
int acertos2 = 0;

String digitado;
String resultado;


void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(A0));
  lcd.begin(16, 2);
  
  ///////////////////////////////////what the display shows in the beggining of the game
  lcd.setCursor(0, 0);
  lcd.print("-THINK MATH RUN-");
  delay(3000);
  lcd.clear();
  delay(500);
  lcd.setCursor(0, 0);
  lcd.print("Preparem-se! O");     
  lcd.setCursor(0, 1);
  lcd.print("jogo vai comecar");
  delay(3000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Comecem pelo");
  lcd.setCursor(0, 1);
  lcd.print("caminho curto");
  delay(3000);
  lcd.clear();
  /////////////////////////////////////////////
  
  digitado= "";
}

void loop(){
  
  int quemJoga;
  
  quemJoga= Jogador(i);
  
  if(pontos1 == 120 && quemJoga == 1){
    
   
  }else{
      lcd.setCursor(0, 0);
    
  	 if(quemJoga == 1){             //display shows that is turn of the first player
      lcd.print("Vez jogador 1");   
    }else{                          //display shows that is turn of the second player
      lcd.print("Vez jogador 2");   
    }
    
    delay(3000);                  
    lcd.clear();

    ////////////////////////   telling the user they must press "*" to check their response
    lcd.setCursor(0, 0);
    lcd.print("Aperte * para en-");  
    lcd.setCursor(0, 1);
    lcd.print("viar a resposta");     
    delay(5000);
    lcd.clear();
    ////////////////////////////

    lcd.setCursor(0, 0);
    lcd.print("Resolva:");           
    delay(1000);
    lcd.clear();
  }
  
  if(quemJoga == 1){     // player 1 turn
    
    switch(pontos1){
      
    	case 0:           //the player 1 begin in the "hard path"
      		if(ultimo1 == 1){
              SomaD();
            }else{      //if player 1" give the wrong answer previously, they go to the first question of the "easy path"
              SomaF();
            }
      		break;
      
      	case 10:
      		SomaF();    //second question of the "easy path" if the p1 gave the right answer
      		break;
      
      	case 20:
      		SomaF();    //third question of the "easy path" if the p1 gave the right answer
      		break;
      
    	case 30:           //comeca a subtracao
        
      	    if(ultimo1 == 1){
      		SubtracaoD();
		    
            }else{
            	SubtracaoF();
            }
      		break;
      
      	case 40:
      		SubtracaoF();
      		break;
      
      	case 50:
      		SubtracaoF();
      		break; 
      
      	case 60:           //comeca a multiplicacao
      		if(ultimo1 == 1){
      			MultiplicacaoD();
            }else{
            	MultiplicacaoF();
            }
      		break;
      
      	case 70:
      		MultiplicacaoF();
      		break; 
      
      	case 80:
      		MultiplicacaoF();
      		break; 
      
      	case 90:          //comeca a divisao
      		if(ultimo1 == 1){
      			DivisaoD();
            }else{
            	DivisaoF();
            }
      		break;
      
      	case 100:
      		DivisaoF();
      		break;
      
      	case 110:
      		DivisaoF();
      		break;
      	case 120:
      		if (pontos1 > pontos2){
              lcd.setCursor(0, 0);
  			  lcd.print("O JOGADOR 1");
              lcd.setCursor(0, 1);
              lcd.print("VENCEU");
              delay(6000);
              lcd.clear();
              i= 0;
              pontos1= 0;
              pontos2= 0;
              Reiniciar();
            }else{
              if(pontos1 == pontos2){
              	lcd.setCursor(0, 0);
  			  	lcd.print("EMPATE");
              	delay(4000);
              	lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("Parabens aos");
                lcd.setCursor(0, 1);
                lcd.print("jogadores");
                delay(3000);
                lcd.clear();
                
                Reiniciar();
              }
            }
      		break;
    }
  
 
  }else{       //quem joga é jogador 2
  	
     switch(pontos2){
       
    	case 0:           //comeca a soma
      		if(ultimo2 == 1){
              SomaD();
            }else{
              SomaF();
            }
      		break;
      
      	case 10:
      		SomaF();
      		break;
      
      	case 20:
      		SomaF();
      		break;
      
    	case 30:           //comeca a subtracao
      		if(ultimo2 == 1){
      			SubtracaoD();
            }else{
            	SubtracaoF();
            }
      		break;
      
      	case 40:
      		SubtracaoF();
      		break;
      
      	case 50:
      		SubtracaoF();
      		break; 
      
      	case 60:           //comeca a multiplicacao
      		if(ultimo2 == 1){
      			MultiplicacaoD();
            }else{
            	MultiplicacaoF();
            }
      		break;
      
      	case 70:
      		MultiplicacaoF();
      		break; 
      
      	case 80:
      		MultiplicacaoF();
      		break; 
      
      	case 90:          //comeca a divisao
      		if(ultimo2 == 1){
      			DivisaoD();
              	if(ultimo2 == 1){
              		if(pontos2 > pontos1){
                      lcd.setCursor(0, 0);
                      lcd.print("O JOGADOR 2");
                      lcd.setCursor(0, 1);
                      lcd.print("VENCEU");
                      delay(6000);
                      lcd.clear();
                      i=0;
                      pontos1= 0;
                      pontos2= 0;
                      Reiniciar();
            		}
              	}
            }else{
            	DivisaoF();
            }
      		break;
      
      	case 100:
      		DivisaoF();
      		break;
      
      	case 110:
      		DivisaoF();
       		if(pontos2 > pontos1){
              lcd.setCursor(0, 0);
  			  lcd.print("O JOGADOR 2");
              lcd.setCursor(0, 1);
  			  lcd.print("VENCEU");
              delay(6000);
              lcd.clear();
              
              Reiniciar();
            }
      		break;
       		
    }
  }
  
  i++;  
 }
  

void Verifica(String digitado, String resultado, int caminho){

  int posicaoPonto;
  char ponto= '.';
  
  while(1){
  lcd.setCursor(0, 1);
  char key = keypad.getKey();
    
    if(key == '*'){
      	digitado += ".00";
    	break;
    }
  
  	if(key != NO_KEY){
      digitado += key;
      lcd.print(digitado);
    }
  }
  
  if (digitado == resultado){
  	lcd.clear();
    lcd.setCursor(0, 0);
  	lcd.print("CORRETO!");
    
    //buzzer correto
    tone(buzzer, 730, 400);
    delay(300);
    noTone(buzzer);
    tone(buzzer, 630, 600);
    delay(500);
    noTone(buzzer);
    tone(buzzer, 530, 300);
    delay(200);
    
    
    lcd.clear();
    
    if(i % 2 != 0){       //quando o jogador 1 acerta
      ultimo1 = 1;
      acertos1 += 1;
      
      if(caminho == 1){   //se vier pelo caminho dificil
      	lcd.setCursor(0, 0);
  		lcd.print("AVANCE 1 CASA");
        delay(3000);
        lcd.clear();
        pontos1 += 30;
      }else{              //se vier pelo caminho facil
      	if(acertos1 == 3){
          lcd.setCursor(0, 0);
  		  lcd.print("VA PARA O");
          lcd.setCursor(0, 1);
  		  lcd.print("CURTO");
          delay(3000);
          lcd.clear();
          pontos1 += 10;  
          acertos1 = 0;
        }else{
        	lcd.setCursor(0, 0);
  			lcd.print("AVANCE 1 CASA");
        	delay(3000);
        	lcd.clear();
        	pontos1 += 10;
        }
      }
      
    }else{                //quando o jogador 2 acerta
      ultimo2 = 1;
      acertos2 += 1;
      
      if(caminho == 1){   //se vier pelo caminho dificil
      	lcd.setCursor(0, 0);
  		lcd.print("AVANCE 1 CASA");
        delay(3000);
        lcd.clear();
       	pontos2 += 30;
        acertos2 = 0;
      }else{              //se vier pelo caminho facil
      	if(acertos2 == 3){
          lcd.setCursor(0, 0);
  		  lcd.print("VA PARA O");
          lcd.setCursor(0, 1);
  		  lcd.print("CURTO");
          delay(3000);
          lcd.clear();
          pontos2 += 10;  
          acertos2 = 0;
        }else{
        	lcd.setCursor(0, 0);
  			lcd.print("AVANCE 1 CASA");
        	delay(3000);
        	lcd.clear();
        	pontos2 += 10;
        }
      }
    }
    
  }else{
    lcd.clear();
    lcd.setCursor(0, 0);
  	lcd.print("INCORRETO!");
    
    //buzzer incorreto
    tone(buzzer, 240, 200);
    delay(200);
    noTone(buzzer);
    tone(buzzer, 290, 200);
    delay(200);
    noTone(buzzer);
    tone(buzzer, 320, 600);
    delay(600);
    
    
    //printar o resultado certo
    posicaoPonto= resultado.indexOf(ponto);
    resultado.remove(posicaoPonto);
    lcd.clear();
    lcd.setCursor(0, 0);
  	lcd.print("Resposta certa: ");
    lcd.setCursor(0, 1);
    lcd.print(resultado);
    delay(3000);
    lcd.clear();
    
    if(i % 2 != 0){     //quando o jogador 1 erra
      ultimo1 = 0;
      
      lcd.setCursor(0, 0);
      
      if(caminho == 1){
  		  lcd.print("VA PARA O LONGO");  
        
      }else{
  		  lcd.print("CONTINUE NA CASA");
      }
      
     delay(3000);
     lcd.clear();
    }else{              //quando o jogador 2 erra
      ultimo2= 0;
      
      if(caminho == 1){
      	lcd.setCursor(0, 0);
  		lcd.print("VA PARA O LONGO");
        delay(3000);
        lcd.clear();
      }else{
      	lcd.setCursor(0, 0);
  		lcd.print("CONTINUE NA CASA");
        delay(3000);
        lcd.clear();
      }
    }
    
  }
  
}
  
  
int Jogador(int contador){ 
  
  if(contador % 2 != 0){
  	return 1;
  }else{
  	return 2;
  }
}
 
void SomaD (){  //funcao soma dificil
	
  int parcela1, parcela2;
  float resul;
  int caminho= 1;
  
  parcela1= random(199, 899);
  delay(1000);
  parcela2= random(199, 899);
  delay(1000);
      
  lcd.setCursor(0, 0);
  lcd.print(parcela1);
  lcd.print("+");
  lcd.print(parcela2);
  lcd.print("=");
  
  resul= parcela1 + parcela2;
  String resultado= String(resul);
  Verifica(digitado, resultado, caminho);
}

void SomaF (){     //funcao soma facil
	
  int parcela1, parcela2;
  float resul;
  int caminho= 2;
  
  parcela1= random(10, 99);
  delay(1000);
  parcela2= random(10, 99);
  delay(1000);
      
  lcd.setCursor(0, 0);
  lcd.print(parcela1);
  lcd.print("+");
  lcd.print(parcela2);
  lcd.print("=");
  
  resul= parcela1 + parcela2;
  String resultado= String(resul);
  Verifica(digitado, resultado, caminho);
}

void SubtracaoD(){   //funcao subtracao dificil
	
  int parcela1, parcela2;
  float resul;
  int caminho= 1;
  
  parcela1= random(101, 899);
  delay(1000);
  parcela2= random(101, 899);
  delay(1000);
  
  if(parcela1 > parcela2){
  	lcd.setCursor(0, 0);
  	lcd.print(parcela1);
  	lcd.print("-");
 	lcd.print(parcela2);
  	lcd.print("=");
      
  	resul= parcela1 - parcela2;
    
  }else{
    lcd.setCursor(0, 0);
  	lcd.print(parcela2);
  	lcd.print("-");
 	lcd.print(parcela1);
  	lcd.print("=");
    
    resul= parcela2 - parcela1;
  }
  
  String resultado= String(resul);
  digitado= "";
  Verifica(digitado, resultado, caminho);
} 

void SubtracaoF(){   //funcao subtracao facil
	
  int parcela1, parcela2;
  float resul;
  int caminho= 2;
  
  parcela1= random(10, 99);
  delay(1000);
  parcela2= random(10, 99);
  delay(1000);
  
  if(parcela1 > parcela2){
  	lcd.setCursor(0, 0);
  	lcd.print(parcela1);
  	lcd.print("-");
 	lcd.print(parcela2);
  	lcd.print("=");
      
  	resul= parcela1 - parcela2;
  }else{
    lcd.setCursor(0, 0);
  	lcd.print(parcela2);
  	lcd.print("-");
 	lcd.print(parcela1);
  	lcd.print("=");
    
    resul= parcela2 - parcela1;
  }
  
  String resultado= String(resul);
  digitado= "";
  Verifica(digitado, resultado, caminho);
}  
      
void MultiplicacaoD(){   //multiplicacao dificil
	
  int parcela1, parcela2;
  float resul;
  int caminho= 1;
  
  parcela1= random(199, 499);
  delay(1000);
  parcela2= random(3, 9);
  delay(1000);
  
  lcd.setCursor(0, 0);
  lcd.print(parcela1);
  lcd.print("x");
  lcd.print(parcela2);
  lcd.print("=");
      
  resul= parcela1 * parcela2;
  
  String resultado= String(resul);
  digitado= "";
  Verifica(digitado, resultado, caminho);
}  

void MultiplicacaoF(){  //multiplicacao facil
	
  int parcela1, parcela2;
  float resul;
  int caminho= 2;
  
  parcela1= random(11, 99);
  delay(1000);
  parcela2= random(2, 10);
  delay(1000);
  
  lcd.setCursor(0, 0);
  lcd.print(parcela1);
  lcd.print("x");
  lcd.print(parcela2);
  lcd.print("=");
      
  resul= parcela1 * parcela2;
  
  String resultado= String(resul);
  digitado= "";
  Verifica(digitado, resultado, caminho);
}

void DivisaoD(){    //divisao dificil
	
  int parcela1, parcela2;
  float resul;
  int caminho= 1;
  
  while(1){
    
    parcela1= random(40, 500);
    delay(50);
    parcela2= random(5, 40);
    delay(50);
    
    if(parcela1 > parcela2 && parcela1 % parcela2 == 0){
      	resul= parcela1 / parcela2;
    	break;	
    }
    
  }
  
  lcd.setCursor(0, 0);
  lcd.print(parcela1);
  lcd.print("/");
  lcd.print(parcela2);
  lcd.print("=");
      
  
  String resultado= String(resul);
  digitado= "";
  Verifica(digitado, resultado, caminho);
}  
  
void DivisaoF(){      //divisao facil
	
  int parcela1, parcela2;
  float resul;
  int caminho= 2;
  
  while(1){
    parcela1= random(10, 99);
    delay(50);
    parcela2= random(2, 10);
    delay(50);
    
    if(parcela1 > parcela2 && parcela1 % parcela2 == 0){
      	resul= parcela1 / parcela2;
    	break;	
    }
    
  }
  lcd.setCursor(0, 0);
  lcd.print(parcela1);
  lcd.print("/");
  lcd.print(parcela2);
  lcd.print("=");
      
  
  String resultado= String(resul);
  digitado= "";
  Verifica(digitado, resultado, caminho);
}  

void Reiniciar(){
  
  i= 0;
  pontos1= 0;
  pontos2= 0;
  ultimo1= 1;
  ultimo2= 1;
  acertos1= 0;
  acertos2= 0;
	
  lcd.setCursor(0, 0);
  lcd.print("NOVO JOGO");
  delay(3000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("-THINK MATH RUN-");
  delay(3000);
  lcd.clear();
  delay(500);
  lcd.setCursor(0, 0);
  lcd.print("Preparem-se! O");
  lcd.setCursor(0, 1);
  lcd.print("jogo vai comecar");
  delay(3000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Comecem pelo");
  lcd.setCursor(0, 1);
  lcd.print("caminho curto");
  delay(3000);
  lcd.clear();
}
 
