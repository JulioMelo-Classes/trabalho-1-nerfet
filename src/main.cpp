#include <iostream>
#include<sstream>
#include <string.h>
#include <vector>
// #include<ctime>
// #include<cstdlib>
#include <time.h>       /* time */

using namespace std;

#define BUFSIZE 1000

using number_type = int; //<! data type for a keno hit.
using cash_type = float; //<! Defines the wage type in this application.
using set_of_numbers_type = std::vector<number_type>;
using set_of_numbers = vector<int>;

class KenoBet {
    public:
        //! Creates an empty Keno bet.
        KenoBet( ) : m_wage(0)
        { /* empty */ };

        bool add_number( number_type spot_ );
        bool set_wage( cash_type wage_ );

        //! Resets a bet to an empty state.
        void reset( void );

        //dedede
        set_of_numbers_type get_bet();

        void printBet(int counter);

        int* get_hits(int *set_bets, int* hits);
        int count_hits(int *set_bets, int* hits);

    private:
        set_of_numbers m_spots;  //<! The player's bet.
        cash_type m_wage;             //<! The player's wage
};


/*! Funções */

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

set_of_numbers KenoBet::get_bet(){
  return m_spots;
}

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

/*! Imprime o vetor com os números escolhidos pelo jogador
    @param counter A quantidade de números que o jogador escolheu. */
void KenoBet::printBet(int counter){
  cout<<"[ ";
	for(int i=0; i<counter; i++){
    cout<<m_spots[i]<<" ";
  }
  cout<<"]";
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

void initialize_keno_table(float *keno_table);

/* Main */
int main(int argc, char *argv[]){
  //Payoff table de Keno
  float keno_table[16][16];

  for(int i=0; i<16; i++){
    for(int j=0;j<16;j++){
      keno_table[i][j]=0;
    }
  }

  keno_table[1][1]=3;

  keno_table[1][2]=1;
  keno_table[2][2]=9;

  keno_table[0][3]=0;
  keno_table[1][3]=1;
  keno_table[2][3]=2;
  keno_table[3][3]=16;

  keno_table[1][4]=0.5;
  keno_table[2][4]=2;
  keno_table[3][4]=6;
  keno_table[4][4]=12;

  keno_table[1][5]=0.5;
  keno_table[2][5]=1;
  keno_table[3][5]=3;
  keno_table[4][5]=15;
  keno_table[5][5]=50;

  keno_table[1][6]=0.5;
  keno_table[2][6]=1;
  keno_table[3][6]=2;
  keno_table[4][6]=3;
  keno_table[5][6]=30;
  keno_table[6][6]=75;

  keno_table[1][7]=0.5;
  keno_table[2][7]=0.5;
  keno_table[3][7]=1;
  keno_table[4][7]=6;
  keno_table[5][7]=12;
  keno_table[6][7]=36;
  keno_table[7][7]=100;

  keno_table[1][8]=0.5;
  keno_table[2][8]=0.5;
  keno_table[3][8]=1;
  keno_table[4][8]=3;
  keno_table[5][8]=6;
  keno_table[6][8]=19;
  keno_table[7][8]=90;
  keno_table[8][8]=720;

  keno_table[1][9]=0.5;
  keno_table[2][9]=0.5;
  keno_table[3][9]=1;
  keno_table[4][9]=2;
  keno_table[5][9]=4;
  keno_table[6][9]=8;
  keno_table[7][9]=20;
  keno_table[8][9]=80;
  keno_table[9][9]=1200;

  keno_table[2][10]=0.5;
  keno_table[3][10]=1;
  keno_table[4][10]=2;
  keno_table[5][10]=3;
  keno_table[6][10]=5;
  keno_table[7][10]=10;
  keno_table[8][10]=30;
  keno_table[9][10]=600;
  keno_table[10][10]=1800;

  keno_table[2][11]=0.5;
  keno_table[3][11]=1;
  keno_table[4][11]=1;
  keno_table[5][11]=2;
  keno_table[6][11]=6;
  keno_table[7][11]=15;
  keno_table[8][11]=25;
  keno_table[9][11]=180;
  keno_table[10][11]=1000;
  keno_table[11][11]=3000;

  keno_table[3][12]=0.5;
  keno_table[4][12]=1;
  keno_table[5][12]=2;
  keno_table[6][12]=4;
  keno_table[7][12]=24;
  keno_table[8][12]=72;
  keno_table[9][12]=250;
  keno_table[10][12]=500;
  keno_table[11][12]=2000;
  keno_table[12][12]=4000;

  keno_table[3][13]=0.5;
  keno_table[4][13]=0.5;
  keno_table[5][13]=3;
  keno_table[6][13]=4;
  keno_table[7][13]=5;
  keno_table[8][13]=20;
  keno_table[9][13]=80;
  keno_table[10][13]=240;
  keno_table[11][13]=500;
  keno_table[12][13]=3000;
  keno_table[13][13]=6000;

  keno_table[3][14]=0.5;
  keno_table[4][14]=0.5;
  keno_table[5][14]=2;
  keno_table[6][14]=3;
  keno_table[7][14]=5;
  keno_table[8][14]=12;
  keno_table[9][14]=50;
  keno_table[10][14]=150;
  keno_table[11][14]=500;
  keno_table[12][14]=1000;
  keno_table[13][14]=2000;
  keno_table[14][14]=7500;

  keno_table[3][15]=0.5;
  keno_table[4][15]=0.5;
  keno_table[5][15]=1;
  keno_table[6][15]=2;
  keno_table[7][15]=5;
  keno_table[8][15]=15;
  keno_table[9][15]=50;
  keno_table[10][15]=150;
  keno_table[11][15]=300;
  keno_table[12][15]=600;
  keno_table[13][15]=1200;
  keno_table[14][15]=2500;
  keno_table[15][15]=10000;

  /* Inicializa uma seed aleatória */
  srand (time(NULL));


  KenoBet bet1;

  /*! Créditos, número de rounds e vetor para números escolhidos pelo jogador. */
  cash_type credits=0;
  int rounds=0;
  int betsInt[15]={0};
  
  FILE *f;
  f = fopen(argv[1], "r");

  if(f==NULL)
  {
    cout<<"Erro ao abrir arquivo";
    return 0;
  }else{
    cout<<">>> Lendo arquivos de aposta "<< argv[1] << ". Por favor aguarde." << endl;
    cout<<"------------------------------------------------------------"<< endl;
  }

  char buff[BUFSIZE];
  int newline=0;
  int counter;

  /*! Laço irá ler o arquivo passado como argumento e preencher as informações. */
  while(fgets(buff, BUFSIZE - 1, f) != NULL) 
  {
    if(newline==0){
      string fs(buff);
      credits=stof(fs);
      cout<<"Creditos: " << credits << endl;
      bet1.set_wage(credits);
   }
    if(newline==1){
      string fs(buff);
      rounds=stof(fs);
      cout<<"Rodadas: " << rounds << endl;
   }
    if(newline==2){
      istringstream ss(buff);
      string del;
      counter=0;
      while(getline(ss, del, ' ')) {
        string fs(del);
        if(bet1.add_number(stof(del))==false){
          cout<<"Aposta inválida pois '"<<stof(del)<<"' não é um número válido. Encerrando."<<endl;
          return 0;
        }
        if(verificar_repeticao(betsInt, stof(del))==true){
          cout<<"Aposta inválida pois '"<<stof(del)<<"' se repete. Encerrando."<<endl;
          return 0;
        }
        betsInt[counter]=stof(del);
        counter++;
        if(counter>15){
          cout<<"Aposta inválida pois existem excessivos números de aposta. Encerrando."<<endl;
          return 0;
        }
      }
      cout<<"Apostas: ";
      bet1.printBet(counter);
   }
    newline++;
  }

  fclose(f);

  /*! Define o valor da aposta por round*/
  cash_type betsPerRound = credits/rounds;
  cout<<endl<<"------------------------------------------------------------"<< endl;

  cout<<endl<<">>> Aposta lida com sucesso!"<< endl;
  cout<<"Você apostará um total de $"<< credits << " créditos." << endl;
  cout<<"Jogará um total de "<<rounds<< " rodadas apostando $"<< betsPerRound <<" por rodada"<< endl;

  cout<<"Sua aposta tem "<<counter<< " números, eles são: ";
  bet1.printBet(counter);
  cout<<endl<<"------------------------------------------------------------"<< endl << endl;

  int* num_sorteados;
  int* spots_hit;
  int qtd_hits;
  int gained=0;
  int spent=0;
  
  for(int i=1; i<=rounds;i++){
    cout<<"Essa é a rodada #"<<i<<" de "<< rounds<<", sua aposta é $"<< betsPerRound<<". Boa sorte!."<<endl;

    credits-=betsPerRound;
    spent+=betsPerRound;

    num_sorteados = sortear_num();
    cout<<"Os números sorteados são: [ ";
    for(int i=0;i<20;i++){
      cout<<num_sorteados[i]<<" ";
    }
    cout<<" ]"<< endl;
    spots_hit = bet1.get_hits(betsInt, num_sorteados);
    qtd_hits = bet1.count_hits(betsInt, num_sorteados);
    cout<<"Você acertou os números: [ ";
    for(int i=0;i<qtd_hits;i++){
      cout<<spots_hit[i]<<" ";
    }
    cout<<"]"<< ", um total de "<<qtd_hits<< " hits de "<<counter<<endl;
    cout<<"Sua taxa de retorno é de: "<<keno_table[qtd_hits][counter]<<", assim, você sai com: $"<<betsPerRound*keno_table[qtd_hits][counter]<<endl;

    credits+=(betsPerRound*keno_table[qtd_hits][counter]);
    gained+=(betsPerRound*keno_table[qtd_hits][counter]);

    cout<<"Você possui um total de: $"<<credits<<" créditos."<<endl;
    if(i==counter){
      cout<<">>> Fim das rodadas!"<< endl;
    }
    cout<<"------------------------------------------------------------"<< endl << endl;
  }
  
  cout<<"======= Sumário ======="<<endl;
  if((gained-spent)>0){
    cout<<">>> Você ganhou $"<<gained-spent<<"."<<endl;
  }else if((gained-spent)<0){
    cout<<">>> Você perdeu $"<<spent-gained<<"."<<endl;
  }else if((gained-spent)==0){
    cout<<">>> Você não ganhou ou perdeu nada."<<"."<<endl;
  }
  
  cout<<">>> Você está saindo com um total de $"<<credits<<".";

  return 0;
}

