# Trabalho-1
Repositório contendo as especificações do Trabalho 1 da disciplina de LP1

# Para compilar no Windows

Para compilar o programa no Windows será necessário um compilador de c++. Para isso eu instalei o Mingw-w64 para utilizar o g++ para compilar o projeto direto do prompt de comando.

Uma vez que o g++ esteja instalado, você deve abrir o CMD e ir para o diretório onde estão os arquivos. (Aqui é trabalho-1-nerfet).
Para compilar execute o comando "g++ -o build/keno src/main.cpp". Isso irá compilar o arquivo main.cpp e criar um executavel "keno.exe" dentro da pasta build. 

# Execuntando o programa e utilizando os testes

Agora, para executar o programa só precisamos entrar no diretório build e usar o comando "keno.exe". Se fizer isso, o programa mostrará um erro pois nenhum arquivo  de dados foi passado como argumento. Esses aquivos estão no diretório "data" dentro de "build", portanto para utiliza-los basta executar o programa usando, por exemplo: "keno.exe data/aposta.dat". Existem 6 arquivos de teste dentro da pasta data, esses são:
    aposta.dat
    aposta2.dat
    aposta3.dat
    apostaErro.dat
    apostaErro2.dat
    apostaErro3.dat
As aposta que possuem erro não serão executadas e o programa mostrará o que há de errado com elas.

# Limitações 

O programa não explica o erro que ocorre quando uma string é passada entre os números no arquivo de aposta. Ele também não organiza os números dos vetores em ordem crescente.