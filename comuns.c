//Trabalho prático Sistemas Operativos
//Meta 1
//Celso Jordão, nº.2003008910
//Fábio Campobianchi, nº.2018915299

#include "comuns.h"

<<<<<<< HEAD
//Função de verificação da existência de clientes
=======
>>>>>>> 022b32152d55aa19978b36b4b0cd69b781df2b42
int Verifica_cliente(utent c1, char cname[]){
  utent aux;
  aux=c1;

  while(aux != NULL){
    if(strcmp(aux->nome,cname)==0){
      return 0;
    }
    aux = aux->next;
  }

  return 1;
}

<<<<<<< HEAD
//Função de escrita dos dados de cada cliente
=======
>>>>>>> 022b32152d55aa19978b36b4b0cd69b781df2b42
utent criaCliente(utent c1, utent_t copia){
  utent novo;

  novo=malloc(sizeof(utent_t));

  if(novo==NULL){
    return NULL;
  }else{
    novo->pid_utent = copia.pid_utent;
    strcpy(novo->nome, copia.nome);
    strcpy(novo->palavra, copia.palavra);
    novo->next= NULL;

    if(c1==NULL)
    c1 = novo;
    else
    { novo->next = c1;
      c1 = novo;
    }
  }
  if(c1!=NULL)
    fprintf(stderr,"\nCliente %s gravado\n", novo->nome);

  return c1;
}
