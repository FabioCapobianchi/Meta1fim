//Trabalho prático Sistemas Operativos
//Meta 1
//Celso Jordão, nº.2003008910
//Fábio Campobianchi, nº.2018915299

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <ctype.h>


#define  TAM_MAX 50
#define  SINT_MAX 8

typedef struct cliente utent_t, *utent;
struct cliente{//cliente
 pid_t pid_utent;
 char nome[TAM_MAX];
 char palavra[TAM_MAX];
 utent next;
};

typedef struct balcao balcao_t, *balc;
struct balcao{//Balcao
  int pid;
  char pnome[TAM_MAX];
  char palavra[TAM_MAX];
};

typedef struct medico medic_t, *medic;
struct medico{//Medico
  pid_t pid_medic;
  char mnome[TAM_MAX];
  char espec[TAM_MAX];
  char unome[TAM_MAX];
  char pr[TAM_MAX];
  medic next;
};

int Verifica_cliente(utent c1, char cname[]);

utent criaCliente(utent c1, utent_t copia);
