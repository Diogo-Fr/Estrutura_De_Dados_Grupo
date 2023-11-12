#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matriz.h"

//é definido ponteiros para matrizes e arquivos de forma global para facilitar a passagem de uma função para outra
Matriz *m1, *m2, *mr;
FILE *f1, *f2;

// Abre os arquivos necessários
// Pré-condição: a função que chamou definir um n 
// Pós-condição: abre um ou dois arquivos
void abrirArquivos(int n){
  char fn[100];
  //abre o primeiro arquivo de matriz
  printf("Entre com o nome do arquivo da matriz: ");
  scanf("%[^\n]%*c", fn);
  f1 = fopen(fn, "r");
  //abre o segundo arquivo de matriz
  if(n == 2){
    printf("Entre com o nome do arquivo da segunda matriz: ");
    scanf("%[^\n]%*c", fn);
    f2 = fopen(fn, "r");
  }
}

// Fecha os arquivos abertos e desaloca as matrizes conforme necessário
// Pré-condição: a função que chamou definir um n 
// Pós-condição: fecha o(s) arquivo(s) e desaloca a(s) matriz(es) 
void limpa(int n){
  fclose(f1);
  excluir(m1);
  if(n >= 2) excluir(mr);
  if(n >= 3) excluir(m2);
  if(n == 4) fclose(f2);
}

// Executa as operações que tem como input duas matrizes
// Pré-condição: o usuário escolher 1 ou 2  no menu
// Pós-condição: executa a operação
void duasMat(int o){
  abrirArquivos(2); //abre dois arquivos de matrizes
  m1 = lerMatriz(f1); //é definida a primeira matriz com base no primeiro arquivo
  m2 = lerMatriz(f2); //é definida a segunda matriz com base no segundo arquivo
  //executa a operação escolhida pelo usuário
  if(o == 1) mr = soma(m1,m2); 	
  if(o == 2) mr = multiplica(m1,m2);
  imprimir(mr); //imprime a matriz resultante
  limpa(4);//fecha f1 e f2, e libera m1, m2 e mr
}


// Imprime o menu do programa
// Pré-condição: nenhuma
// Pós-condição: nenhuma
void imprimeOpcoes(){
  printf("Escolha uma opcao:\n\n");
  printf("1 - Somar duas matrizes\n");
  printf("2 - Multiplicar duas matrizes\n");
  printf("3 - Sair\n\n");
}

int main(void) {
  int opc = 0;
  printf("Trabalho de Estrutura de dados\n\n");
  printf("Matrizes Esparsas\n\n");
  while(opc != 3){
    imprimeOpcoes(); 
    scanf("%d%*c", &opc);
    //analisa o que o usuário quer fazer
    if(opc == 1 || opc == 2) duasMat(opc); else
    if(opc != 3) printf("Opção inválida!\n\n");
  }
  return 0;
}
