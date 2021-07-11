#include <iostream>
#include<sstream>
#include <string.h>
#include <vector>
#include <time.h>

using namespace std;

using number_type = int; //<! data type for a keno hit.
using cash_type = float; //<! Defines the wage type in this application.
using set_of_numbers_type = std::vector<number_type>;
using set_of_numbers = vector<int>;

class KenoBet {
    public:

        bool add_number( number_type spot_ );
        bool set_wage( cash_type wage_ );

        set_of_numbers_type get_bet();

        void printBet(int counter);

        int* get_hits(int *set_bets, int* hits);
        int count_hits(int *set_bets, int* hits);

    private:
        set_of_numbers m_spots;  //<! The player's bet.
        cash_type m_wage;             //<! The player's wage
};


/*! Funções */

/*! Adiciona um número ao vetor dos numeros escolhidos pelo jogador.
    @param spot_ O número que queremos inserir.
    @return Retorna True se o numero foi inserido, False se o contrário. */
bool KenoBet::add_number(number_type spot_){
  if(spot_ <= 0 || spot_ >80){
    return false;
  }else{
    m_spots.push_back(spot_);
    return true;
  }
}

/*! Verifica a quantidade de dinheiro que o jogador está apostando.
    @param wage_ A aposta.
    @return True se a aposta for maior que 0; do contrário retorna False. */
bool KenoBet::set_wage(cash_type wage_){
  if(wage_>0){
    return true;
  }else{
    return false;
  }
}

set_of_numbers KenoBet::get_bet(){
  return m_spots;
}

/*! Imprime o vetor com os números escolhidos pelo jogador
    @param counter A quantidade de números que o jogador escolheu. */
void KenoBet::printBet(int counter){
  cout<<"[ ";
	for(int i=0; i<counter; i++){
    cout<<m_spots[i]<<" ";
  }
  cout<<"]";
}

/*! Determina quantos números o jogador acertou.
    @param *set_bets O vetor com os números que o jogador escolheu.
    @param *hits O vetor com os números escolhidos aleatoriamente pelo computador.
    @return Retorna um vetor com os números que o jogador acertou. */
int* KenoBet::get_hits(int *set_bets, int* hits){
  static int spothits[15];
  int counter=0;
  for(int i=0; i<20; i++){
    for(int j=0; j<sizeof(set_bets);j++){
      if(hits[i] == set_bets[j]){
        spothits[counter]=hits[i];
        counter++;
      }
    }
  }
  return spothits;
}

/*! Conta quantos números o jogador acertou.
    @param *set_bets O vetor com os números que o jogador escolheu.
    @param *hits O vetor com os números escolhidos aleatoriamente pelo computador.
    @return Retorna quantos números que o jogador acertou. */
int KenoBet::count_hits(int *set_bets, int* hits){
  int counter=0;
  for(int i=0; i<20; i++){
    for(int j=0; j<sizeof(set_bets);j++){
      if(hits[i] == set_bets[j]){
        counter++;
      }
    }
  }
  return counter;
}

/*! Sorteia 20 números aleatórios. 
    @return vetor com os números sorteados. */
int* sortear_num(){
 static int sorteados[20];
 bool check=false;

 for(int i=0;i<20;i++){
   int num_toAdd=rand() % 80 + 1;
   for(int j=0; j<20;j++){
     if(num_toAdd == sorteados[j]){
       check=true;
       break;
     }else{
       check=false;
     }
   }
   if(check==true){
     i--;
   }else{
    sorteados[i]=num_toAdd;
   }
 }
 
 return sorteados;
}

/*! Verifica se existe repetição nos números escolhidos pelo jogador.
    @param *bets Vetor dos numeros escolhidos.
    @param spot_ Número a ser adicionado.
    @return True se houver repetição; false se não houver. */
bool verificar_repeticao(int *bets,number_type spot_){
  for(int i=0; i<sizeof(bets); i++){
    if(spot_ == bets[i]){
      return true;
    }
  }
  return false;
}