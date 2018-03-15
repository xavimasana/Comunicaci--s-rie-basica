/***************************************************************************************************************************************************************************
                                                                
  o888.   c888o   .@@@@@@.      c8@@8c     O8OO  C88C   O88C                Xavi Masana 
   @@@@  o@@@@   @@@@@@@@@@   c@@@@@@@@@   @@@@ :@@@@O O@@@@                Lacetania
   .@@@@.@@@@c  O@@@@  C@@@o  @@@@  @@@@C  O@@@c8@@@@@ @@@@c                2n IT  
    :@@@@@@@:    @@@@C        @@@o  O@@@C   @@@@@@@@@@@@@@@                 Xais Crew Life
     :@@@@@:      @@@@@@O     @@@o          8@@@@@@@@@@@@@O                 Projecte: Comunicació Sèrie Bàsica
     o@@@@@C       @@@@@@@   O@@@o         .@@@@@@@@@@@@@@@    
     @@@@@@@          o@@@@.  @@@o  C@@@C    @@@@@@@@@@@@@     
    @@@@@@@@@   @@@@o  o@@@8  @@@O  8@@@O    O@@@@8 @@@@@o     
   @@@@8 @@@@@  .@@@@@@@@@@:  @@@@@@@@@@.     @@@@c @@@@@      
  8@@@@   @@@@@   O@@@@@@@     O@@@@@@8       @@@@  O@@@@                                                
                                               
 ************************************************************************************************************************************************************************/
 //**********************************************************************INCLUDE*******************************************************************************************


 //*********************************************************************VARIABLES******************************************************************************************
int estat = 0;
int opcio = 0;
int entitat = 0;
int oficina = 0;
int dcIntroduit = 0;
int numTarBuscar = 0;
unsigned  long num1Compte = 0, num2Compte = 0;
unsigned long num1Tarjeta = 0,  num2Tarjeta = 0;

 //***********************************************************************SETUP*********************************************************************************************
void setup()
{
  Serial.begin(9600);
}
//*************************************************************************LOOP**********************************************************************************************
void loop()
{
  while (Serial.available() > 0)
  {  
    switch (estat)
    {
      case 0:
        opcio = Serial.parseInt(); 
        if (opcio == 1 )
        {
          Serial.println("*** Comprovant numero de tarjeta de credit ***");
          Serial.print("Entra els primers 8 digits del numero de la tarjeta de credit: ");
          estat = 1;
        }
        else if (opcio == 2)
        {
          Serial.println("*** Comprovant numero compte bancari ***");
          Serial.print("Entra l'entitat: ");
          estat = 3;
        }
        else if (opcio == 3)
        {
          Serial.println("*** Buscant numero perdut de tarjeta de credit ***");
          Serial.print("Entra els primers 8 o 7 digits del numero de la tarjeta de credit: ");
          estat = 8;
        }
        else 
        {      
          Serial.println("Has entrat una opcio incorrecta!!!");
          imprimirMenu();
        }
        break;
      case 1:
        num1Tarjeta = Serial.parseInt();
        Serial.println(num1Tarjeta);
        Serial.print("Entra els ultims 8 digits del numero de la tarjeta de credit: ");
        estat = 2;
        break;
      case 2:
        num2Tarjeta = Serial.parseInt();
        Serial.println(num2Tarjeta);
        Serial.print("El numero de numero tarjeta de credit ");
        Serial.print(num1Tarjeta / 10000);
        Serial.print(" ");
        Serial.print(num1Tarjeta % 10000);
        Serial.print(" ");
        Serial.print(num2Tarjeta / 10000);
        Serial.print(" ");
        Serial.print(num2Tarjeta % 10000);
        tarjetaCorrecte (num1Tarjeta, num2Tarjeta);
        estat = 0;
        imprimirMenu();     
        break;
      case 3:
        entitat = Serial.parseInt();
        Serial.println(entitat);
        Serial.print("Entra l'oficina: ");
        estat = 4;
        break;
      case 4:
        oficina = Serial.parseInt();
        Serial.println(oficina);
        Serial.print("Entra el digit de control(DC): ");
        estat = 5;
        break;
      case 5:
        dcIntroduit = Serial.parseInt();
        Serial.println(dcIntroduit);
        Serial.print("Entra els primers 5 digits del numero de compte: ");
        estat = 6;
        break;
      case 6:
        num1Compte = Serial.parseInt();
        Serial.println(num1Compte);
        Serial.print("Entra els ultims 5 digits del numero de compte: ");
        estat = 7;
        break;
      case 7:
        num2Compte = Serial.parseInt();
        Serial.println(num2Compte);
        Serial.print("El numero de compte bancari ");
        Serial.print(entitat);
        Serial.print("-");
        Serial.print(oficina);
        Serial.print("-");
        Serial.print(dcIntroduit);
        Serial.print("-");
        Serial.print(num1Compte);
        Serial.print(num2Compte);
        compteCorrecte (entitat, oficina, dcIntroduit, num1Compte, num2Compte);
        estat = 0;
        imprimirMenu();
        break;
      case 8:
        num1Tarjeta = Serial.parseInt();
        Serial.println(num1Tarjeta);
        Serial.print("Entra els ultims 8 o 7 digits del numero de la tarjeta de credit: ");
        estat = 9;
        break;
      case 9:
        num2Tarjeta = Serial.parseInt();
        Serial.println(num2Tarjeta);
        Serial.print("Entra la posicio del numero que es vol trobar: ");
        estat = 10;
        break;
      case 10:
        numTarBuscar  = Serial.parseInt();
        Serial.println(numTarBuscar);
        Serial.print("El numero de tarjeta de credit ");
        buscarNumTarjeta (num1Tarjeta, num2Tarjeta,numTarBuscar);
        estat = 0;
        imprimirMenu();
        break;
      default:
        break;   
    }
  }
}

void imprimirMenu()
{
  Serial.println();
  Serial.println("Escull el numero de l'operacio que vols realitzar?");
  Serial.println("  1. Comprovar numero de tarjeta de credit");
  Serial.println("  2. Comprovar numero de compte bancari");
  Serial.println("  3. Buscar un digit perdut de tarjeta de credit");
  Serial.println();
}

void compteCorrecte (int ent, int ofi, int dc, unsigned long com1, unsigned long com2)
{
  unsigned long suma = 0;
  int entMult[] = {4, 8, 5, 10}; 
  int ofiMult[] = {9, 7, 3, 6};
  int comMult[] = {1, 2, 4, 8, 5, 10, 9, 7, 3, 6};
  int primerDigit = 0, segonDigit = 0;
  int dcCalculat = 0, residuSuma = 0;
  int i;
  
  for(i = 0; i < 4; i++)
  {
    suma = suma + (ent % 10) * entMult[3-i] + (ofi % 10) * ofiMult[3-i];
    ent = ent / 10;
    ofi = ofi / 10;  
  }
  residuSuma = suma % 11;
  primerDigit = 11 - residuSuma;
  if (primerDigit == 10)
  {
    primerDigit = 1;
  }
  else if (primerDigit == 11)
  {
    primerDigit = 0;
  }
  else
  {
  }
  suma = 0;
  for(i = 0; i < 5; i++)
  {
    suma = suma + (com2 % 10) * comMult[9-i];
    com2 = com2 / 10;
  }
  for(i = 5; i < 10; i++)
  {
    suma = suma + (com1 % 10) * comMult[9-i];
    com1 = com1 / 10;
  }
  residuSuma = suma % 11;
  segonDigit = 11 - residuSuma;
  if (segonDigit == 10)
  {
    segonDigit = 1;
  }
  else if (segonDigit == 11)
  {
    segonDigit = 0;
  }
  else
  {
  }
  dcCalculat = primerDigit * 10 + segonDigit;
  if (dcCalculat == dc)
  {
    Serial.println(" es CORRECTE");
  }
  else
  {
    Serial.println(" es INCORRECTE!!!!!!!!!!!!!");
  }
}

void tarjetaCorrecte (unsigned long tar1, unsigned long tar2)
{
  int i;
  int sumaPar = 0, sumaImpar = 0, valImpar = 0, sumaTotal = 0;
  
  for (i = 8; i > 0; i--)
  {
    if ((i % 2) == 0) //Posició parell
    {
      sumaPar = sumaPar + (tar1 % 10) + (tar2 % 10);
    }
    else //Posició imparell
    {
      valImpar = (tar1 % 10) * 2;
      if (valImpar > 9)
      {
        valImpar = (valImpar / 10) + (valImpar % 10);
      }
      sumaImpar = sumaImpar + valImpar;
      valImpar = (tar2 % 10) * 2;
      if (valImpar > 9)
      {
        valImpar = (valImpar / 10) + (valImpar % 10);
      }
      sumaImpar = sumaImpar + valImpar;
    }
    tar1 = tar1 / 10;
    tar2 = tar2 / 10;
  }
  sumaTotal = sumaPar + sumaImpar;
  if ((sumaTotal % 10) == 0)
  {
    Serial.println(" es CORRECTE");
  }
  else
  {
    Serial.println(" es INCORRECTE!!!!!!!!!!!!!");
  }
}

void buscarNumTarjeta (unsigned long tar1, unsigned long tar2, int posPerdut)
{
  int i;
  unsigned long divisor1, divisor2;
  int sumaPar = 0, sumaImpar = 0, valImpar = 0, sumaTotal = 0, sumaTotalOpcio = 0;
  
  if (tar1 > 9999999)
  {
   divisor1 = 10000000;
   divisor2 = 1000000;
  }
  else
  {
    divisor2 = 10000000;
    divisor1 = 1000000;
  }
  for (i = 1; i < 9; i++)
  {
    if (i != posPerdut)
    {
      if ((i % 2) == 0) //Posició parell
      {
        sumaPar = sumaPar + (tar1 / divisor1);
      }
      else //Posició imparell
      {
        valImpar = (tar1 / divisor1) * 2;
        if (valImpar > 9)
        {
          valImpar = (valImpar / 10) + (valImpar % 10);
        }
        sumaImpar = sumaImpar + valImpar;
      }
      Serial.print(tar1 / divisor1);
      tar1 = tar1 % divisor1;
      divisor1 = divisor1 / 10;
    }
    else
    {   
      Serial.print("X");
    }
    if ((i == 4) || (i == 8))
    {
      Serial.print(" ");
    }
  }
  for (i = 1; i < 9; i++)
  {
    if ((i + 8) != posPerdut)
    {
      if ((i % 2) == 0) //Posició parell
      {
        sumaPar = sumaPar + (tar2 / divisor2);
      }
      else //Posició imparell
      {
        valImpar = (tar2 / divisor2) * 2;
        if (valImpar > 9)
        {
          valImpar = (valImpar / 10) + (valImpar % 10);
        }
        sumaImpar = sumaImpar + valImpar;
      }
      Serial.print(tar2 / divisor2);
      tar2 = tar2 % divisor2;
      divisor2 = divisor2 / 10;
    }
    else
    {
      Serial.print("X");
    }
    if ((i == 4) || (i == 8))
    {
      Serial.print(" ");
    }
  }
  sumaTotal = sumaPar + sumaImpar;
  for (i = 0; i < 10; i++)
  {
    sumaTotalOpcio = sumaTotal;
    if ((posPerdut % 2) == 0) //Posició parell
    {
      sumaTotalOpcio = sumaTotalOpcio + i;
    }
    else //Posició imparell
    {
      valImpar = i * 2;
      if (valImpar > 9)
      {
        valImpar = (valImpar / 10) + (valImpar % 10);
      }
      sumaTotalOpcio =  sumaTotalOpcio + valImpar;
    }  
    if ((sumaTotalOpcio % 10) == 0)
    {
      Serial.print(" li falta el digit de la posicio "); 
      Serial.print(posPerdut);
      Serial.print(", aquest digit es el ");
      Serial.println(i);
      i = 10;
    }
  }
}

//***********************************************************************FUNCTIONS*******************************************************************************************
