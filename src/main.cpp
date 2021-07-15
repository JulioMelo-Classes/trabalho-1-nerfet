#include <iostream>
#include<sstream>
#include <string.h>
#include <vector>
#include <time.h>
#include <fstream>

#include "keno.h"

using namespace std;

/*
Avaliação
Processamento do Arquivo de Entrada: 0,75 (faltou testar a quantidade de linhas)
Execução correta: 0,8 (20% de penalidade pela implementação no .h)
Interfcace Textual: 0,8
Documentação: 1
Compilação automatizada: 0 (não fez)
Organização em src, include, build, data: 1 (considerei mesmo o lugar do diretório data estando errado)

Comentários
- movi o diretorio data para fora do build, para melhorar a organização
- já que você não conseguiu (não entendi o motivo) usar um Makefile ou Cmake, o mínimo que poderia ter
feito era uma compilação usando scripts (no windows ou no linux, desde que ficasse claro no readme)
- como conversamos na entrevista, a ideia da disciplina é que você use e aprenda c++. Assim eu sugiro
nos próximos trabalhos que você implemente vetores usando std::vector ou array, além de evitar o máximo que der
ponteiros para tipos básicos (int*, char*, float*, etc).
- Provavelmente por não ter tentado usar C++ você também não implementou outras classes, neste problema caberiam pelo menos mais 2
uma responsável pela interface textual e outra responsável pelo processamento e validação do arquivo, tente pensar (não precisa fazer)
como você modelaria o problema desta forma, veja que o main ficaria bem mais enxuto.
- Outro ponto que tem que ser revisto é que você adicionou as implementações inline no .h. Você sabe de ITP que isso é uma má prática
todo .h precisa de um .cpp correspondente. Assim eu vou remover pontos da parte de código do trablaho por isso (20% a menos).
*/

/* Main */
int main(int argc, char *argv[]){
	
  //Payoff table de Keno
  float keno_table[][16] = {   {0, 3},
								 {0, 1, 9},
								 {0, 1, 2, 16},
								 {0, 0.5, 2, 6, 12},
								 {0, 0.5, 1, 3, 15, 50},
								 {0, 0.5, 1, 2, 3, 30, 75},
								 {0, 0.5, 0.5, 1, 6, 12, 36, 100},
								 {0, 0.5, 0.5, 1, 3, 6, 19, 90, 720},
								 {0, 0.5, 0.5, 1, 2, 4, 8, 20, 80, 1200},
								 {0, 0, 0.5, 1, 2, 3, 5, 10, 30, 600, 1800},
								 {0, 0, 0.5, 1, 1, 2, 6, 15, 25, 180, 100, 3000},
								 {0, 0, 0, 0.5, 1, 2, 4, 24, 72, 250, 500, 2000, 4000},
								 {0, 0, 0, 0.5, 0.5, 3, 4, 5, 20, 80, 240, 500, 3000, 6000},
								 {0, 0, 0, 0.5, 0.5, 2, 3, 5, 12, 50, 150, 500, 1000, 2000, 7500},
								 {0, 0, 0, 0.5, 0.5, 1, 2, 5, 15, 50, 150, 300, 600, 1200, 2500, 10000}};

  /* Inicializa uma seed aleatória */
  srand (time(NULL));

  KenoBet bet1;

  /*! Créditos, número de rounds e vetor para números escolhidos pelo jogador. */
  cash_type credits=0;
  int rounds=0;
  int betsInt[15]={0};
  
  fstream file;
  
  string filename = argv[1];
  
  file.open(filename, ios::in);
  
  if(!file){
	cout<<"Erro ao abrir arquivo";
    return 0;
  }else{
	cout<<">>> Lendo arquivos de aposta "<< filename << ". Por favor aguarde." << endl;
    cout<<"------------------------------------------------------------"<< endl;
  }
  
  int newline=0;
  string line;
  int counter;
  
  while(getline(file, line)){
    istringstream iss(line);
    if(newline==0){
        credits=stof(line);
        cout<<"Creditos: " << credits << endl;
        if(bet1.set_wage(credits)==false){
          cout<<"Aposta inválida pois não possui créditos o suficiente. Encerrando."<<endl;
          return 0;
        }
    }
      if(newline==1){
        rounds=stof(line);
        cout<<"Rodadas: " << rounds << endl;
    }
      if(newline==2){
        istringstream ss(line);
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
      if(newline>=3){
        cout<<endl<<"Arquivo de aposta não está no formato correto. Encerrando."<<endl;
        return 0;
      }
      newline++;
  }
  file.close();

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
    cout<<"Sua taxa de retorno é de: "<<keno_table[counter-1][qtd_hits]<<", assim, você sai com: $"<<betsPerRound*keno_table[counter-1][qtd_hits]<<endl;

    credits+=(betsPerRound*keno_table[counter-1][qtd_hits]);
    gained+=(betsPerRound*keno_table[counter-1][qtd_hits]);

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

