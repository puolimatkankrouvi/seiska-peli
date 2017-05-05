
#include "kortti.h"
#include <time.h>

using namespace std;


  string arvoksi(int nmr){
	//Muuttaa kortin arvon
	//int -> string
    string a;
	switch(nmr){
	  case 1:
	    a = "A";
	    break;
	  case 2:
	    a = "2";
	    break;
	  case 3:
	    a = "3";
	    break;
	  case 4:
	    a = "4";
	    break;
	  case 5:
	    a = "5";
	    break;
	  case 6:
	    a = "6";
	    break;
	  case 7:
	    a = "7";
	    break;
	  case 8:
	    a = "8";
	    break;
	  case 9:
	    a = "9";
	    break;
	  case 10:
	    a = "10";
	    break;
	  case 11:
	    a = "J";
	    break;
	  case 12:
	    a = "D";
	    break;
	  case 13:
	    a = "K";
	    break;
	}
	
	return a;
  }
  
  int arvosta(string arvo){
	//Muuttaa kortin arvon
	//string -> int
    int a;
	
	if(arvo.compare("A")==0){
	    a = 1;
	}
	else
	if(arvo.compare("10")==0){
	    a = 10;
	}
	else
	if(arvo.compare("J")==0){
	    a = 11;
	}
	else
	if(arvo.compare("D")==0){
	    a = 12;
	}
	else
	if(arvo.compare("K")==0){
	    a = 13;
	}
	else{
	  a = atoi(arvo.c_str());
	}
    return a;	
  }

  string maaksi(int m){
    //Muuttaa maan int arvon väliltä 0-3
    //string:ksi
    string maa = "";
    switch(m){
      case 0: maa = "pat"; break;
      case 1: maa = "ruut"; break;
      case 2: maa = "ris"; break;
      case 3: maa = "hert"; break;	  
    }
    return maa;
  }

  Kortti::Kortti() {
    maa = EI_KORTTIA;
	arvo = 0;
  }
  Kortti::Kortti(int m, int a)
  {
    maa = m;
    arvo = a;
  }
  
  void sekoita(vector<Kortti> *pakka){
    //Fischer-Yates algoritmi
	  
	//Satunnainen seed nykyisestä ajanhetkestä
	//Tekee sekoituksesta satunnaisen
	srand(time(NULL));
	//Pakka käydään lopusta alkuun
	for(int i=pakka->size()-1; i > 0; i--){
	  int j = rand()%i;
	  //Vaihdetaan kortin i ja satunnaisen kortin j paikkaa
	  Kortti tmp = pakka->at(i);
	  pakka->at(i) = pakka->at(j);
	  pakka->at(j) = tmp;
	}
	
	
  }
  
  vector<Kortti> luo(){
  
    vector<Kortti> pakka;
  
    for(int i = PATA; i<=HERTTA; i++){
	  for(int j = 1; j<14;j++){
	    char  a = j;
	    Kortti *uusiKortti = new Kortti(i,a);
        pakka.push_back(*uusiKortti);
	  }
	}
    return pakka;
  }

