
/*

mettre les points d att et de vie pour joueur et monstre

*/

#include "dunogeon.h"
#include "Arduino.h"
#define porte Serial.println(F("Quelle porte prenez-vous?"))
#define chapitre Serial.println();Serial.print(F("Chapitre ")); Serial.println(actualRoom);
#define breakTime 4000
#define ligne Serial.println(F("-_-_-_-_-_-_-_-"))

//main void
void DUNOGEON::begin(){
 //set up Arduino
 randomSeed(analogRead(A0)+analogRead(A1)+analogRead(A2));
 Serial.begin(9600);
 pinMode(LED_BUILTIN, OUTPUT);
//set dunogeon
 rooms = random(5)+5;// nombre de salle a effectué   
 for (uint8_t i = rooms ; i>0 ; i--){
  meet[i] = random(10);
 }
 //verification();
 quest();

}

void DUNOGEON::quest(){
 Serial.println(F("Bienvenu.e dans le DUNOGEON !"));
 delay(breakTime);
 Serial.println(F("Tu devras survivre dans ce donjon, allant de 5 à 10 salles."));
 delay(3000);
 Serial.println(F("La LED intégrée au Arduino et liée à la pin 13 représente tes battements de cœurs."));
 delay(3000);
 Serial.println(F("Utilise le serial pour communiquer avec le DUNOGEON."));
 delay(3000);
 Serial.println(F("Bonne chance !"));
 delay(3000);
 ligne;

 
 Serial.println(F("Après avoir passé quelques couloirs et pièces mineures, vous arrivez dans une première salle..."));
 delay(breakTime);

 while(1){
  
  if (actualRoom==rooms+1){
   Serial.println(F("Bravo,vous êtes sorti du dunogeon. A la sortie vous apercevez une rouquine qui vous accueille en vous disant : "));
Serial.println(F("- Je t'attendais…"));
delay(5000);
Serial.println(F("...félicitation!"));
delay(breakTime); 
Serial.println(F("- Car tu es admis à la plus grande des Guildes, tu vas pouvoir rejoindre les [insérer ce qui vous plaît] "));
Serial.println();
delay(breakTime);
Serial.print(F("F"));delay(breakTime);Serial.print(F("I"));delay(breakTime);Serial.println(F("N"));
delay(breakTime);
Serial.println();
Serial.println(F("Textes : Maëlle L.B. aka Roukinette"));
Serial.println(F("Codes : Julien L. aka HorriblePère"));
Serial.println();
delay(breakTime);
Serial.println(F("Licence : cc by nc sa"));
Serial.println(F("2022"));

while(1);

  }else{
    
   chapitre;
   roomDescription();
 //tableau de rencontre(de 0 à 9) : 0-1=vide ; 2-5=monstres ; 6-7 =piège ; 8-9 = trésor
   switch (meet[actualRoom]) {
  case 0 : case 1 :
   emptyRoomMeet();
   break;
  case 2 : case 3 : case 4 :case 5 :
   monsterMeet();
   break;
  case 6 : case 7 :
   trapMeet();
   break;
  case 8 : case 9 :
   tresorMeet();
   break;
  default: 
  Serial.println(F("error in void quest"));
   break;
  }
  actualRoom++;
  whatDoor();
  }
 }
}

void DUNOGEON::emptyRoomMeet(){
R=random(5);
 switch (R) {
  case 0 :
  Serial.println(F("Hormis de la poussière...Rien."));
  break;
  case 1 :
   Serial.println(F("il y a juste deux rats qui se battent avec leurs pattes."));
  break;
  case 2 :
      Serial.println(F("CHUT! Un bruit..."));
      delay(breakTime);
      Serial.println(F("Ah non, il n'y a rien.")); 
  break;
  case 3 :
     Serial.println(F("Boum!!!"));
      delay(breakTime);
     
     Serial.println(F("Un bout du plafond s'est effondré, mais vous n'êtes pas blessé"));  
  break;
  case 4 : 
   Serial.println(F("Le silence total. C'est encore plus stressant"));
  break;
   }
}

void DUNOGEON::monsterMeet(){
 R=random(5);
 switch (R) {
  case 0 :
  Serial.println(F("Un squelette s'avance vers vous... Le regard vide."));
  delay(breakTime);
  monsterFight(1,1);
   break;
  case 1 :
  Serial.println(F("Une tombe, disimulée dans le sol, s’ouvre et un mort-vivant en sort."));
  delay(breakTime);
  monsterFight(2,1);
   break;
  case 2 :
    Serial.println(F("Un vampire s'apprête à vous sauter dessus pour vous mordre au cou!"));
    delay(breakTime);
    monsterFight(2,2);
   break;
  case 3 :
Serial.print(F("GRRRRRR!!!"));
delay(breakTime);    
Serial.println(F("Un loup-garou surgit devant vous en grognant!"));
delay(breakTime);
   monsterFight(2,2);
   break;
  case 4 : 
Serial.println(F("La créature la plus terrible que vous connaissiez s'avance vers vous..."));
delay(breakTime);  
Serial.println(F("Votre père!" ));
delay(breakTime);  
Serial.println(F("Il répète cette phrase en boucle : ")); 
delay(breakTime);  
Serial.println(F("FAIS LE LAVE-VAISSELLE, FAIS LE LAVE-VAISSELLE... "));
delay(breakTime);
  monsterFight(5,3);
   break;
   }
}

void DUNOGEON::trapMeet(){
R=random(5);
 switch (R) {
  case 0 :
  Serial.println(F("Une trappe s'ouvre sous vos pieds."));
  playerLife-=1;
   break;
  case 1 :
  Serial.println(F("Des pierres tombent du plafond fissuré."));
  playerLife-=1;
   break;
  case 2 :
    Serial.println(F("De nombreuses flèches jaillissent de nulle part"));
    playerLife-=2;
   break;
  case 3 : 
  Serial.println(F("Le plafond tout entier s'écrase sur votre tête et une hache vous coupe un bras!"));
  Serial.println(F("Par 'chance' vous aviez un casque et vous êtes ambidextre."));
  playerLife-=3;;
   break;
   }
   playerInfos();
}

void DUNOGEON::tresorMeet(){
R=random(5);
 switch (R) {
  case 0 :
  Serial.println(F("Vous trouvez une fraise TAGADA au sol. Vous la ramassez et l'engloutissez."));
  playerLife+=2;
   break;
  case 1 :
  Serial.println(F("Vous voyez quelque chose brillez par terre, une pomme juteuse."));
  playerLife+=5;
   break;
  case 2 :
    Serial.println(F("Vous trouvez une potion jaunâtre, peu ragoûtante. Vous décidez de la boire malgré tout.")); 
    Serial.println(F("Vous sentez vos forces se régénérerent"));
  playerLife+=10;
   break;
  case 3 :
    Serial.println(F("Vous trouvez une épée avec une gravure : "));
delay(3000);
Serial.println(F("ROUKINOUX UN JOUR"));
delay(3000);
Serial.println(F("ROUKINOUX TOUJOURS"));
   if (playerAttack < 2)
   {playerAttack = 2;}else{Serial.println(F("Pas intéressant pour vous."));}
   break;
  case 4 : 
  Serial.println(F("Vous trouvez une simple pomme... en métal?"));
  Serial.println(F(" Un mécanisme se met en marche. le fruit se métamorphose en un sabre laser [de la couleur de votre choix]. "));
  playerAttack = 3;
   break;
   }
   if (playerLife>10){playerLife=10;};
   playerInfos();
}

void DUNOGEON::roomDescription(){
 R=random(5);
 Serial.print(F("C'est une salle "));
 switch (R) {
  case 0 :
  Serial.println(F("avec une cheminée et une grande table avec le couvert dressé "));
   break;
  case 1 :
  Serial.println(F("qui resemble à un petit salon, très poussiéreux"));
   break;
  case 2 :
  Serial.println(F("plus grande que les autres. Il y a une énorme bibliothèque avec toutes sortes d'ouvrages "));
   break;
  case 3 :
  Serial.println(F("remplie de miroirs. Il y en a dans tous les sens"));
   break;
  case 4 : 
  Serial.println(F("remplie d'un nuage de fumée opaque et grise."));
   break;
   }
}

void DUNOGEON::whatDoor(){
R=random(4);
 switch (R) {
  case 0 :
  Serial.println(F("Il y a une porte à GAUCHE et une à DROITE."));
  porte;
  quid("gauche","gauche","droite");
   break;
  case 1 :
  Serial.println(F("Il y a une porte à GAUCHE et une DEVANT."));
  porte;
  quid("gauche","gauche","devant");
   break;
  case 2 :
    Serial.println(F("Il y a une porte à DROITE, et une DEVANT."));
  porte;
  quid("droite","droite","devant");
   break;
  case 3 :
    Serial.println(F("Il y a une porte à DROITE, une à GAUCHE et une DEVANT."));
  porte;
  quid("droite","gauche","devant");
   break;
  default: 
  Serial.println(F("error in void whatDoor"));
   break;
   }
}

void DUNOGEON::quid(String reponseAttendu1, String reponseAttendu2, String reponseAttendu3) 
 {
  bool reponseOk =false;
  while(!reponseOk){ 
 
 reponseEnvoyee = false;
 delay(1);
 // Vider le buffer Serial s'il reste des caractères...
while (Serial.available()) 
    {
     Serial.read();
     }  
// en attente de réponse
while (!reponseEnvoyee) {
 playerLed();
  if (Serial.available() > 0) {
   reponse = Serial.readStringUntil('\n');
   //si reponse à trop de caractère
  if (reponse.length() > maxCaraPourLaReponse ){
   Serial.println(F("~~~~"));
    Serial.println(F("Je suis désolé, mais l'écriture se limite à 10 caractères et ceci de manière totalement arbitraire."));
    
    //offense();
    }else{
   //longueur correcte
   Serial.println("");
   Serial.print("> ");
   Serial.println(reponse);
   reponseEnvoyee = true;
   }
   delay (10);
  }
}
  // si réponses attendues absentes
  if ( reponse != reponseAttendu1 && reponse != reponseAttendu2 && reponse != reponseAttendu3) {
   wrongAnswer();
  }else{
   reponseOk =true;
  }

 }
 }

void DUNOGEON::verification(){
  Serial.print(F("nombre de salle : "));
  Serial.print(rooms);
  Serial.println();
  Serial.print(F("rencontres : "));
 for (uint8_t i=rooms;i>0;i--){
  Serial.print(meet[i]);
 }  
 Serial.println();

}

void DUNOGEON::wrongAnswer(){
 byte R = random(5);
 switch (R) {
  case 0 :
   Serial.println(F("Je ne peux utiliser cette réponse"));
   break;
  case 1 :
   Serial.println(F("Je n'ai pas compris."));
   break;
  case 2 :
   Serial.println(F("Lecture impossible, recommencez"));
   break;
  case 3 :
   Serial.println(F("Valeur non prise en compte"));
   break;
  case 4 :
   Serial.println(F("Non valide"));
   break;
  default :
   Serial.println(F("Malheureusement je suis limité dans ma compréhension des intentions humaines"));   
   break;
 }
}

void DUNOGEON::monsterFight(byte varMonsterLife, byte varMonsterAttack){

 Serial.println();
 Serial.println(F("FIGHT!"));
 Serial.println();
 int8_t monsterLife=varMonsterLife;
 byte monsterAttack=varMonsterAttack;
 byte playerMoves;
 while(playerLife>0 && monsterLife>0){
  playerInfos();
  Serial.print(F("Monstre > Santée: "));Serial.print(monsterLife);Serial.print(F(" - Dégâts: "));Serial.println(monsterAttack);
 Serial.println(F("Quelle attaque faite vous, une ATTAQUE directe, une PARADE, une CHARGE ?"));
 quid("attaque", "charge", "parade");
 if(reponse=="attaque"){playerMoves=0;}
 if(reponse=="charge"){playerMoves=1;}
 if(reponse=="parade"){playerMoves=2;}
 R=random(3);
 if(playerMoves == R){
  Serial.println(F("Même mouvement, aucun de vous ne touche l'autre."));}
else if ((playerMoves==0 && R==2) ||playerMoves>R){
  monsterLife -= playerAttack;
  Serial.println(F("Bravo, vous l'avez blessé."));
 }else{ 
 playerLife -= monsterAttack;
 Serial.println(F("Oh, ça fait mal!!!"));
 }
 if(monsterLife<1){
  Serial.println(F("Victoire !"));
  }
 }
 Serial.println(F("Fin du combat."));
}

void DUNOGEON::playerLed(){ 
  bool etatLed = chronoDandD(playerLife*100);

  digitalWrite(LED_BUILTIN, etatLed);
}
void DUNOGEON::playerInfos(){
 Serial.print("Joueur > Santé: ");Serial.print(playerLife);Serial.print("/10 - Dégâts: ");Serial.print(playerAttack);
 Serial.println();
 if ( playerLife < 1 ){
 Serial.println(F("Dommage, vous êtes mort!")); 
 while(1);
}}

// return 0 ou 1 alternativement en fonction de la durée d'une frequence attribué (long frequence) 
// utilisé pour la led 
bool DUNOGEON::chronoDandD(long frequency){
 static bool chronoTop;
 unsigned long millisNow = millis();
 static unsigned long millisOld;
if ((millisNow-millisOld) >frequency ){
  millisOld=millis();
  chronoTop = !chronoTop;
  }
  return chronoTop;
  
}
