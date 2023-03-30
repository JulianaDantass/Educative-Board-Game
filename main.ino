
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
  digitado= "";
  
  /////////////////////////////////// what the display shows in the beggining of the game
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
  
}

void loop(){
  
  int quemJoga;
  
  ////////////////////////////// just a piece of the code to alternate between the players. if "i" is odd then is player1 turn  //  "i" is pair then is player1 turn   
  if(i % 2 != 0){
  	quemJoga = 1;
  }else{
  	quemJoga = 2;
  }           
  //////////////////////////////


  if(pontos1 == 120 && quemJoga == 1){
    
      //just one exception
   
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
      
    	case 0:           /**********the player 1 begin in the "hard path" resolving SUM********/ 

      		if(ultimo1 == 1){
              Soma(1);    //first and unic question of the "hard path"
            }else{      
              Soma(2);   //if player 1" give the wrong answer previously, they go to the first question of the "easy path"
            }
      		break;
      
      case 10:
      		Soma(2);    //second question of the "easy path" if the p1 gave the right answer
      		break;
      
      case 20:
      		Soma(2);    //third question of the "easy path" if the p1 gave the right answer
      		break;
      
    	case 30:          /**********the player 1 returns to the "hard path" resolving  SUBTRACTION********/ 
        
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
      
      case 60:           /**********the player 1 returns to the "hard path" resolving  MULTIPLICATION********/ 
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
      
      case 90:          /**********the player 1 returns to the "hard path" resolving  DIVISION********/ 
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
  
 
  }else{      //same thing but for the SECOND PLAYER
  	
     switch(pontos2){     
       
    	case 0:           /**********the player 2 begin in the "hard path" resolving SUM********/ 
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
      
    	case 30:           /**********the player 2 begin in the "hard path" resolving SUBTRACION********/ 
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
      
      	case 60:          /**********the player 2 begin in the "hard path" resolving MULTIPLICATION********/ 
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
      
      	case 90:           /**********the player 2 begin in the "hard path" resolving DIVISION********/ 
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
  
  i++;           //increase the counter that is responsible for alternate the turns
 }
  

void Verifica(String digitado, String resultado, int caminho){      //this function gets the answer from the user and checks it

  int posicaoPonto;
  char ponto= '.';
  
  while(1){
    lcd.setCursor(0, 1);
    char key = keypad.getKey();       //the keypad waits for the user to press a key
    
    if(key == '*'){           //if the key is "*" means the user have a final answer and it breaks the while
      digitado += ".00";      //this is just an adaptation to make more easier the comparation between "user's answer" and the "final answer"
    	break;
    }
  
  	if(key != NO_KEY){       //if any key was pressed, then it will appear on display.  (OBS.: We don't have the feature to delete a key)
      digitado += key;
      lcd.print(digitado);
    }
  }
  
  if (digitado == resultado){    //if the result is correct
  	lcd.clear();
    lcd.setCursor(0, 0);
  	lcd.print("CORRETO!");
    
    /////////////////////////////// if the result is correct, this is the buzzer sound: 
    tone(buzzer, 730, 400);
    delay(300);
    noTone(buzzer);
    tone(buzzer, 630, 600);
    delay(500);
    noTone(buzzer);
    tone(buzzer, 530, 300);
    delay(200);
    
    
    lcd.clear();
    
    if(i % 2 != 0){       //if the turn is of player1
      ultimo1 = 1;
      acertos1 += 1;
      
      
      if(caminho == 1){        //if it came from the "hard path"
      	lcd.setCursor(0, 0);
  		  lcd.print("AVANCE 1 CASA");
        delay(3000);
        lcd.clear();
        pontos1 += 30;         //the player gets +30 points


      }else{                  //if it came from the "easy path"

        lcd.setCursor(0, 0);

      	if(acertos1 == 3){        //if is the last question, a mensage will appear to change the path      
          lcd.print("VA PARA O");
          lcd.setCursor(0, 1);
          lcd.print("CURTO");
          acertos1 = 0;

        }else{
        	lcd.setCursor(0, 0);
  			  lcd.print("AVANCE 1 CASA");
        }

        delay(3000);
        lcd.clear();
        pontos1 += 10;
      }
      
    }else{                //if the turn is of player2
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

      lcd.setCursor(0, 0);
      	if(acertos2 == 3){
          
  		    lcd.print("VA PARA O");
          lcd.setCursor(0, 1);
  		    lcd.print("CURTO");
          delay(3000);
          lcd.clear();
           
          acertos2 = 0;
        }else{

        	lcd.setCursor(0, 0);
  			  lcd.print("AVANCE 1 CASA");
        	delay(3000);
        	lcd.clear();
    
        }
        pontos2 += 10; 
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
 
void Soma (int cam){  //sum 
	
  int parcela1, parcela2;
  float resul;
  
  if(cam == 1){  //hard path (the sum is more complicated)

    parcela1= random(199, 899);
    delay(1000);
    parcela2= random(199, 899);
    delay(1000);

  }else{                       //easy path
    parcela1= random(10, 99);
    delay(1000);
    parcela2= random(10, 99);
    delay(1000);
  }

      
  lcd.setCursor(0, 0);
  lcd.print(parcela1);
  lcd.print("+");
  lcd.print(parcela2);
  lcd.print("=");
  
  resul= parcela1 + parcela2;
  String resultado= String(resul);
  Verifica(digitado, resultado, caminho);
}

void SubtracaoD(int cam){   //subtraction 
	
  int parcela1, parcela2;
  float resul;

  if(cam == 1){  //hard path

    parcela1= random(101, 899);
    delay(1000);
    parcela2= random(101, 899);
    delay(1000);

  }else{    //easy path

    parcela1= random(10, 99);
    delay(1000);
    parcela2= random(10, 99);
    delay(1000);

  }

  if(parcela1 > parcela2){      //just to unable a negative result
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


      
void Multiplicacao(int cam){   //multiplication 
	
  int parcela1, parcela2;
  float resul;

  if(cam == 1){

    parcela1= random(199, 499);
    delay(1000);
    parcela2= random(3, 9);
    delay(1000);

  }else{
    parcela1= random(11, 99);
    delay(1000);
    parcela2= random(2, 10);
    delay(1000);
  }
  
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


void Divisao(int cam){    //division
	
  int parcela1, parcela2;
  float resul;
  int flag;


  while(1){
    
    if(cam == 1){        //hard path

      parcela1= random(40, 500);
      delay(50);
      parcela2= random(5, 40);
      delay(50);
    }else{               //easy path

      parcela1= random(10, 99);
      delay(50);
      parcela2= random(2, 10);
      delay(50);
    }
    
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
 
