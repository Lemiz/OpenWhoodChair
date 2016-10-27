
/*
  /*
  # This Sample code is for testing the DC Motor Driver 2x15A_lite module. // Upgraded by @hugobiwan to drive an open source wheelchair for @myhumankit.

  # Editor : Phoebe
  # Date   : 2012.11.6
  # Ver    : 0.1
  # Product: DC Motor Driver 2x15A_lite
  # SKU    : DRI0018

  # Description:
  # Drive 2 motors with this DC Motor Driver module

  # Hardwares:
  1. Arduino UNO
  2. DC Motor Driver 2x15A_lite
  3. DC motors x2

  #Steps:
  1.Connect the M1_PWM & M2_PWM to UNO digital 5 & 6
  2.Connect the M1_EN & M2_EN to UNO digital 4 & 7
  3.Connect +5V & GND to UNO 5V & GND
  4.Connect joystick switches in this order on a clock beginning from noon : 9,10,11,12. Connect the Ground of the switches to the arduino Ground

  # Function for current sense and diagnosis,if you want to use
  please connect the IS pins to Arduino
  Connect LA_IS and RA_IS to UNO digital 2 at the same time
  Connect LB_IS and RB_IS to UNO digital 3 at the same time
*/
//declaration des broches de joystick;
int haut = 8;
int droite = 9;
int bas = 10;
int gauche = 11;

//declaration des etats de broches de joystick;

int etat_haut = 0;
int etat_droite = 0;
int etat_bas = 0;
int etat_gauche = 0;



int E1 = 5;     //M1 Speed Control
int E2 = 6;     //M2 Speed Control
int M1 = 4;     //M1 Direction Control
int M2 = 7;     //M1 Direction Control
int counter = 0;



void stop(void)                    //Stop
{
  digitalWrite(E1, 0);
  digitalWrite(M1, LOW);
  digitalWrite(E2, 0);
  digitalWrite(M2, LOW);
}

//Contrôle par joystick
//on cree un array des 4 contacts de joystick possibles
int joystick[4];
int y = 0; //sert à incrémenter des saut dans le tableau, dans la fonction loop
int val = 0; // ordre de mouvement - 8 mouvements possibles et le stop.


void advance(char a, char b)         //Move forward
{
  analogWrite (E1, a);     //PWM Speed Control
  digitalWrite(M1, HIGH);
  analogWrite (E2, b);
  digitalWrite(M2, HIGH);
}
void back_off (char a, char b)         //Move backward
{
  analogWrite (E1, a);
  digitalWrite(M1, LOW);
  analogWrite (E2, b);
  digitalWrite(M2, LOW);
}
void turn_L (char a, char b)            //Turn Left
{
  analogWrite (E1, a);
  digitalWrite(M1, LOW);
  analogWrite (E2, b);
  digitalWrite(M2, HIGH);
}
void turn_R (char a, char b)            //Turn Right
{
  analogWrite (E1, a);
  digitalWrite(M1, HIGH);
  analogWrite (E2, b);
  digitalWrite(M2, LOW);
}
void current_sense()                  // current sense and diagnosis
{
  int val1 = digitalRead(2);
  int val2 = digitalRead(3);
  if (val1 == HIGH || val2 == HIGH) {
    counter++;
    if (counter == 3) {
      counter = 0;
      Serial.println("Warning");
    }
  }
}

void setup(void)
{
  int i;
  for (i = 4; i <= 7; i++)
    pinMode(i, OUTPUT);
  Serial.begin(9600);      //Set Baud Rate
  Serial.println("Lancement du joystick");
  digitalWrite(E1, LOW);
  digitalWrite(E2, LOW);
  pinMode(2, INPUT);
  pinMode(3, INPUT);

  //ajout du joystick- broches numérotées dans le sens des aiguilles d'une montre avec la 10 en position midi

  pinMode(haut, INPUT); //
  pinMode(droite, INPUT);
  pinMode(bas, INPUT);
  pinMode(gauche, INPUT);

  //activation des internal pullups

  digitalWrite(haut, HIGH);
  digitalWrite(droite, HIGH);
  digitalWrite(bas, HIGH);
  digitalWrite(gauche, HIGH);
}

void loop(void)
{
  /*
    static unsigned long timePoint = 0;    // current sense and diagnosis,if you want to use this
    if(millis() - timePoint > 1000){       //function,please show it & don't forget to connect the IS pins to Arduino
    current_sense();
    timePoint = millis();
    }
  */


  //On défini le caractere cible par la position du joystick
  //par exemple on code sa position dans un tableau

  int joystick[] = {etat_haut, etat_droite, etat_bas, etat_gauche};

  //debug

  //lecture des broches

  etat_haut = digitalRead(haut);
  etat_droite = digitalRead(droite);
  etat_bas = digitalRead(bas);
  etat_gauche = digitalRead(gauche);

  //temoin
  Serial.println(etat_haut);
  Serial.println(etat_droite);
  Serial.println(etat_bas);
  Serial.println(etat_gauche);
  Serial.println("----------------------------------------------------");
  //delay(100);


  //Ensuite on va regarder les valeurs du tableau et affecter le caractère. 8 positions possibles + le stop

  //positions pour avancer

  if (etat_haut == 0 && etat_droite == 1 && etat_bas == 1 && etat_gauche == 1)
  {
    Serial.println("avance");
    //ordre de mouvement
    val = 1;
  }
  if (etat_haut == 0 && etat_droite == 0 && etat_bas == 1 && etat_gauche == 1)
  {
    Serial.println("avance droite");
    //ordre de mouvement
    val = 8;
  }
  if (etat_haut == 1 && etat_droite == 0 && etat_bas == 1 && etat_gauche == 1)
  {
    Serial.println("droite");
    val = 3;
    //ordre de mouvement
  }
  if (etat_haut == 1 && etat_droite == 0 && etat_bas == 0 && etat_gauche == 1)
  {
    Serial.println("recule droite");
    //ordre de mouvement
    val = 4;
  }
  if (etat_haut == 1 && etat_droite == 1 && etat_bas == 0 && etat_gauche == 1)
  {
    Serial.println("recule");
    //ordre de mouvement
    val = 5;
  }
  if (etat_haut == 1 && etat_droite == 1 && etat_bas == 0 && etat_gauche == 0)
  {
    Serial.println("recule gauche");
    //ordre de mouvement
    val = 6;
  }
  if (etat_haut == 1 && etat_droite == 1 && etat_bas == 1 && etat_gauche == 0)
  {
    Serial.println("gauche");
    //ordre de mouvement
    val = 7;
  }
  if (etat_haut == 0 && etat_droite == 1 && etat_bas == 1 && etat_gauche == 0)
  {
    Serial.println("avance gauche");
    //ordre de mouvement
    val = 2;
  }
  else if (etat_haut == 0 && etat_bas == 0 || etat_gauche == 0 && etat_droite == 0 || etat_haut == 1 && etat_droite == 1 && etat_bas == 1 && etat_gauche == 1) {
    Serial.println("stop");
    val = 9;
  }

  Serial.println("----------------------------------------------------");
  Serial.println(val);
  //delay(1000);
  Serial.println("----------------------------------------------------");
  //fin du serial
  //ON LANCE L'ORDRE DE MOUVEMENT
  bouge(val);
}





//on utilise la fonction deja codee mais on va ajouter des codes pour les diagonales

void bouge(int valeur) {


  switch (valeur)
  {
    case 1://Move Forward
      advance (255, 255);  //move forward in max speed
      break;
    //avance vers la avant droite (diagonale 1)
    case 2:
      advance (255, 120);  //move forward in max speed
      break;
    //avance vers arriere droite (diagonale 2)
    case 4:
      back_off (255, 120);
      break;
    //avance vers arriere gauche (diagonale 3)
    case 6:
      back_off (120, 255);
      break;
    //avance vers avant gauche (diagonale 4)
    case 8:
      advance (120, 255);
      break;
    case 5://Move Backward
      back_off (255, 255);  //move back in max speed
      break;
    case 7://Turn Left
      turn_L (255, 255);
      break;
    case 3://Turn Right
      turn_R (255, 255);
      break;
    case 9:
      stop();
      break;
    default :
      stop();
      break;
  }
}


