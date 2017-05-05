#include <vector>
#include <string>

#define IHMISPELAAJA 0
  
#define EI_KORTTIA -1
#define PATA 0
#define RUUTU 1
#define RISTI 2
#define HERTTA 3


  
std::string arvoksi(int nmr);
int arvosta(std::string arvo);
std::string maaksi(int m);
  
struct Kortti{
  int maa;
  int arvo;
  Kortti();
  Kortti(int m,int a);
};
 
  
void sekoita(std::vector<Kortti> *pakka);
  
std::vector<Kortti> luo();
  
  
  
  
  
