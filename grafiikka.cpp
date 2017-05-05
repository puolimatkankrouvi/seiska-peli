#include <iostream>
#include <sstream>
#include <string>

#include "kortti.h"

using namespace std;

  void tulostaPakka(vector<Kortti> *pakka){
	cout << endl;
    for(int i = 0; i<pakka->size(); i++){
      cout << maaksi(pakka->at(i).maa) << arvoksi(pakka->at(i).arvo) << ',';
    }
    cout << endl << endl;
  }
  
void tulostaPoyta(Kortti poyta[13][4]){
  cout << endl;
  for (int i = 12; i >= 0; --i){
    cout << "|";
    for (int j = 0; j < 4; ++j){
	  if (poyta[i][j].arvo == EI_KORTTIA){
		//Jos pöydän kohdassa ei ole korttia
		cout << "         |";
	  }
	  else{
	    string maa = maaksi(poyta[i][j].maa);
	    string arvo = arvoksi(poyta[i][j].arvo);
        cout << maa << arvo;
        int valimaara = 0;
		//Sarakkeeseen tulostuu yhteensä 8 merkkiä,
		//kortin arvo ja maa, loput välilyöntejä
        while(valimaara< (8-(maa.size())-(arvo.size()))){
          cout << " ";
	      valimaara++;
        }
      cout << "|";
	}
  }
  cout << endl;
  }
}

string lueKomento(){
  string komento;
  cin >> komento;
  return komento;  
}

void tulostaSijoitus(int sijoitus,int pelaaja, int n){

	
	if(sijoitus == 1){
	  //Tulostetaan voittajan tiedot
	  switch(pelaaja){
		//Jos pelaaja oli ensimmäinen
        case 0:
	    cout << "Voitit pelin!" << endl;
        break;
	    case 1:
	    switch(n){
		  case 2:
		    //Jos pelaajien lukumäärä n on vain kaksi, tietokonepelaajan numeroa ei tulosteta
		    cout << "Tietokonepelaaja voitti." << endl;
		  break;
		  default:
		    cout << "Tietokonepelaaja " << pelaaja << " voitti." << endl;
		  break;
	    }
	    break;
        default:
        cout << "Tietokonepelaaja " << pelaaja << " voitti." << endl;	  
	  }
	}
	else{
	  switch(pelaaja){
		//Muiden kuin voittajien sijoitukset
        case 0:
	      cout << "Olit " << sijoitus << "." << endl;
        break;
	    default:
		  cout << "Tietokonepelaaja " << pelaaja << " " << "oli " << sijoitus << "."   << endl;
		break;
	  }
	}
}

void tulostaLaitto(int vuorossa, int arvo, int maa){
	
	if(maa == EI_KORTTIA){
	  cout << "Tietokonepelaaja " << vuorossa << " sanoi ohi" << endl;
	}
	else{
	  cout << "Tietokonepelaaja " << vuorossa << " pani kortin " << maaksi(maa) << arvoksi(arvo) << endl;
	}
}

void tulostaOtto(int vuorossa, int arvo, int maa){
    if(vuorossa == IHMISPELAAJA){
	  cout << "Otit edelliselta kortin " << maaksi(maa) << arvoksi(arvo) << endl;
	}
	else
	  if(vuorossa == 1){
		  //Ensimmäinen tietokonepelaaja ottaa aina ihmispelaajalta kortin
		  cout << "Tietokonepelaaja " << vuorossa << " otti sinulta kortin " << maaksi(maa) << arvoksi(arvo) << endl;
	  }
	else{
	  cout << "Tietokonepelaaja " << vuorossa << " otti edelliselta kortin" << endl;
	}
}

void tulostaOhje(){
	cout << "Kirjoita kortti, jonka haluat panna poytaan, ohi tai lopeta ja paina enteria:" << endl;
}


