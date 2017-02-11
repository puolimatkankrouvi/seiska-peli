
#include <vector>
#include "kortti.h"
#include "grafiikka.h"
#include <ctime>
#include <algorithm>



using namespace std;

/*TODO

*/

  struct Pelaaja{
    vector<Kortti> kasi;
    int nmr;
    int ristiseiska;
    int ohi;
    vector<pair<int,int> > maara;
    /*int eniten;
    int patoja;
    int ruutuja;
    int risteja;
    int herttoja;*/
    Pelaaja();
  };
  
  Pelaaja::Pelaaja(){
    kasi = vector<Kortti>();
    nmr = 0;
    ristiseiska = 0;
    ohi = 0;
    for(int maa = HERTTA; maa>=PATA; --maa){
      maara.push_back(make_pair(0,maa));
    }
  }
  
  int kellaRistiSeiska(vector<Pelaaja> pelaajat){
    
    for(int i = 0; i<pelaajat.size(); ++i){
      if(pelaajat[i].ristiseiska == 1){
        return i;
      }    
    }  
  }
  
  void laskeKortitMaittain(Pelaaja *pel){
	  
	  for(int i = 0; i < pel->kasi.size(); ++i){
		  int maa = pel->kasi[i].maa;
		  switch(maa){
			  case PATA:
              pel->maara[0].first++;
			  break;
			  case RUUTU:
			  pel->maara[1].first++;
			  break;
			  case RISTI:
			  pel->maara[2].first++;
			  break;
			  case HERTTA:
			  pel->maara[3].first++;
			  break;
		  }
	  }
	  
	  
  }
  
  int onkoLaitettu(int maa,int arvo, Kortti poyta[13][4]){
    return poyta[arvo-1][maa].maa == EI_KORTTIA ? 0 : 1;
  }
  
  int voikoLaittaa(int arvo,int maa, Kortti poyta[13][4]){
  
  
    int voiko = 0;
	
    if(arvo == 7){
      if(maa == RISTI){
        voiko = 1;
      }
      else{
        voiko = onkoLaitettu(RISTI,7,poyta);

      }
    }
    else
      if(arvo == 8){
        voiko = onkoLaitettu(maa,6,poyta);
      }
      else
      if(arvo == 6){
          voiko = onkoLaitettu(maa,7,poyta);
      }
        else
          if(arvo<6){
          voiko = onkoLaitettu(maa,arvo+1,poyta) && onkoLaitettu(maa,8,poyta);
        }
        else{
          voiko = onkoLaitettu(maa,arvo-1,poyta);
        }

    return voiko;
  }
  
  void lisaaPoytaan(Kortti kortti, Kortti poyta[13][4] ){
    poyta[(kortti.arvo)-1][kortti.maa] = kortti;
  }
  
  int siirra(int a, int m, Kortti poyta[13][4],vector<Kortti> *kasi){
	
    //Siirrä kädestä pöytään
    
    for(int i = 0; i<kasi->size(); ++i){
      
      if((*kasi)[i].arvo == a && (*kasi)[i].maa == m){
        
        kasi->erase(kasi->begin()+i);
      lisaaPoytaan(Kortti(m,a),poyta);
      return 1;
      
      }
      
    }
    return 0;
  }

Kortti otaKortti(vector<Pelaaja> *pelaajat,int vuorossa){
	
	Kortti otettu;
	int edellinen;
	if(vuorossa == IHMISPELAAJA){
	  edellinen = (*pelaajat).size()-1;
	}
	else{
	  edellinen =  vuorossa-1;
	}
	
	int randomi = rand()%((*pelaajat)[edellinen].kasi.size());
	otettu = (*pelaajat)[edellinen].kasi[randomi];
	(*pelaajat)[edellinen].kasi.erase((*pelaajat)[edellinen].kasi.begin()+randomi);
	(*pelaajat)[vuorossa].kasi.push_back(otettu);
	
	return otettu;
	
}

  
void sleep(unsigned int s){
	clock_t goal = s * 1000 + clock();
	while(goal>clock());
}


bool vertaile(pair<int,int> i,pair<int,int> j){
	return (i.first>j.first);
}
  
  int peli(vector<Pelaaja> pelaajat){
    
	/*Luo pöytätaulukko*/
	Kortti poyta[13][4];

	int loppu = 0;
	int voittaja = -1;
	/*Pelin kierrokset*/
	
	/*Aloittaja se, jolla on ristiseiska*/
  int aloittaja = kellaRistiSeiska(pelaajat);
	
  int komentoOk = 0;
	
	int vuorossa = aloittaja;
	
	int sijoitus = 1;
	
	while(!loppu){
	
	  vector<int> mahd;
	  for(int a = 0; a<pelaajat[vuorossa].kasi.size();++a){
	    if(voikoLaittaa( pelaajat[vuorossa].kasi[a].arvo,pelaajat[vuorossa].kasi[a].maa, poyta)){
		  mahd.push_back(a);
		}
	  }
	  
	  if(vuorossa == IHMISPELAAJA){
		
		tulostaPoyta(poyta);
	    tulostaPakka(&(pelaajat[IHMISPELAAJA].kasi));
		tulostaOhje();
		
		/*Komento on taulukko, jossa eka maa-int ja toka arvo-int*/
		int komentoOk = 0;
		int ohi = 0;

		do{
		  string rivi= lueKomento();

          string maaTeksti = "";
          string arvoTeksti = "";
          int arvo = 0;
		  int maa = EI_KORTTIA;
		  
  
          size_t found = (rivi.find_first_of("hertupaisol"));
          while(found != string::npos){
            maaTeksti = maaTeksti + rivi[found];
	        found = rivi.find_first_of("hertupaisol",found+1);
          }
		  
	      if(maaTeksti.compare("ohi")==0){
	         ohi = 1;
			 if(pelaajat[IHMISPELAAJA].ohi == 1){
			   Kortti otettu = otaKortti(&pelaajat,vuorossa);
			   tulostaOtto(vuorossa,otettu.arvo,otettu.maa);
			 }
			 pelaajat[IHMISPELAAJA].ohi = 1;
	      }
		  else
		    if(maaTeksti.compare("lopeta")==0){
			  loppu = 1;
		    }
            else
	          if(maaTeksti.compare("pat")==0){
	             maa = PATA;
	          }
	          else
	            if(maaTeksti.compare("ruut")==0){
	              maa = RUUTU;
	            }
	            else
	              if(maaTeksti.compare("ris")==0){
	                maa = RISTI;
	              }
	              else
	                if(maaTeksti.compare("hert")==0){
	                  maa = HERTTA;
	                }
				    else{
		              maa = EI_KORTTIA;
		            }
				  
		  if(!ohi && !loppu){
            found = (rivi.find_first_of("0123456789AJDK"));
            while(found != string::npos){
              arvoTeksti = arvoTeksti + (char)(rivi[found]);
	          found = rivi.find_first_of("0123456789",found+1);
            }
  
  
            stringstream(arvoTeksti) >> arvo;
		    if(arvoTeksti == "A" || "J" || "D" || "K"){
				arvo = arvosta(arvoTeksti);
			}

		    //Tarkista, voiko korttia laittaa

		    if( (PATA<=arvo<=HERTTA) && maa !=EI_KORTTIA){
		     int voiLaittaa = voikoLaittaa(arvo,maa, poyta);
		   
		     if(voiLaittaa){
		       voiLaittaa = siirra(arvo, maa, poyta,&(pelaajat[vuorossa].kasi));
		     }
			 komentoOk = voiLaittaa;
		    }
		   }
		}
		while(!komentoOk && !ohi && !loppu);
		
	  }
	  else{
	    //Tietokonepelaaja
		
		laskeKortitMaittain(&pelaajat[vuorossa]);
		
		if(mahd.size()>0){
		  int randomi = rand()%mahd.size();
		  int ind = mahd[randomi];
		  
		  /*Sorttaa pelaajat[vuorossa].maara laskevaan järkkään*/
		  sort(pelaajat[vuorossa].maara.begin(),pelaajat[vuorossa].maara.end(), vertaile);
		  
		  for(int h = 0; h < pelaajat[vuorossa].maara.size(); ++h){
			  for(int u = 0; u < mahd.size(); ++u){
				  //Verrataan mahdollisen kortin maata määrien maahan
				  if(pelaajat[vuorossa].kasi[ mahd[u] ].maa == pelaajat[vuorossa].maara[h].second){
					  ind = u;
					  goto pois;
				  }
			  }
		  }
		  pois:
		  tulostaLaitto(vuorossa, pelaajat[vuorossa].kasi[ind].arvo, pelaajat[vuorossa].kasi[ind].maa);
		  siirra(pelaajat[vuorossa].kasi[ind].arvo,pelaajat[vuorossa].kasi[ind].maa, poyta,&(pelaajat[vuorossa].kasi));
		}
		else{
			
		  
		  if(pelaajat[vuorossa].ohi == 1){
			  Kortti otettu = otaKortti(&pelaajat,vuorossa);
			  tulostaOtto(vuorossa,otettu.arvo,otettu.maa);
		  }
		  else{
	      tulostaLaitto(vuorossa,0,-1);
        pelaajat[vuorossa].ohi = 1;
		  }
		}
		
	  }



	  for(int p = IHMISPELAAJA; p < pelaajat.size(); ++p){
		  if(pelaajat[p].kasi.size() == 0){
			  tulostaSijoitus(sijoitus,pelaajat[p].nmr-1,pelaajat.size());
			  ++sijoitus;
			  if(p==IHMISPELAAJA){
			    loppu = 1;
			    tulostaPoyta(poyta);
			  }
			  else{
			    pelaajat.erase(pelaajat.begin()+p);
				p--;
			    if(pelaajat.size()==1){
			      tulostaSijoitus(sijoitus,IHMISPELAAJA,pelaajat.size());
				  loppu = 1;
			      tulostaPoyta(poyta);
			    }
			  }

		  }
	  }
	  vuorossa >= pelaajat.size()-1 ? vuorossa = IHMISPELAAJA : ++vuorossa;
	}
	
	return voittaja;
  }
  
 void jaaKortit(vector<Kortti> *pakka, vector<Pelaaja> *pelaajat){
    
	int i = 0;
	
    while(!pakka->empty()){
      Pelaaja *pel = &((*pelaajat)[i]);
	  
	  Kortti jaettava = pakka->back();
	  pakka->pop_back();
	  if(jaettava.maa == RISTI && jaettava.arvo == 7){
	    pel->ristiseiska = 1;
	  }
	  (*pel).kasi.push_back(jaettava);
	  i == pelaajat->size()-1 ? i = 0 : ++i;
	}
	
  }

  
vector<Pelaaja> luoPelaajat(int maara){

  	vector<Pelaaja> *pelaajat = new vector<Pelaaja>();
	
	for(int i = 0; i < maara; ++i){
	  pelaajat->push_back(Pelaaja());
	  (*pelaajat)[i].nmr = i+1;
	}
	
	return *pelaajat;

}



  void aloita(){
  
    cout << "Peli alkaa:" << endl;
    sleep(1);
  
    /*Luodaan ja sekoitetaan pakka*/
    vector<Kortti> pakkaTaulukko = luo();
    vector<Kortti> *pakka = &pakkaTaulukko;
    sekoita(pakka);
	
    /*Luodaan pelaajat*/
    vector<Pelaaja> pelaajat = luoPelaajat(4);
	
    /*Jaetaan kortit*/
    jaaKortit(pakka, &pelaajat);
	
	
    peli(pelaajat);
	
    string loppu = lueKomento();
	
    return;
  }


