//Trabalho prático Sistemas Operativos
//Meta 1
//Celso Jordão, nº.2003008910
//Fábio Campobianchi, nº.2018915299

#include "comuns.h"
#include <sys/wait.h>

int b_fifo_fd;
int c_fifo_fd;
int m_fifo_fd;

int main(int argc, char **argv, char **envp){

  int bal_to_cla[2];
  int cla_to_bal[2];
  pipe(bal_to_cla);
  pipe(cla_to_bal);//
  int id,res;
  utent_t utent;
  balcao_t balc;
  char c_fifo_fname[50];
  char m_fifo_fname[50];

  fprintf(stdout,"\nMEDICALso\n");

  res = mkfifo(getenv("BALC_FIFO"), 0777);//Criação do FIFO do balcao

  if (res == -1){
    perror("\nNao foi possivel abrir o Balcao");
    exit(EXIT_FAILURE);
  }

  fprintf(stderr, "\nBalcao de Atendimento criado\n");

  b_fifo_fd = open(getenv("BALC_FIFO"), O_RDWR);//Abertura para leitura/escrita do FIFO do balcão

  if (b_fifo_fd == -1){
    perror("\nErro ao abrir Balcao");
    exit(EXIT_FAILURE);
  }

  fprintf(stderr, "\n Bom Dia\n Balcao aberto para atendimento");

  memset(utent.palavra, '\0', TAM_MAX);

  while (1){

    res = read(b_fifo_fd, & utent, sizeof(utent));
    if(res < sizeof(utent)){
      fprintf(stderr,"\nMensagem ilegivel");
      continue;
    }

    fprintf(stderr,"\nRecebido de %s sintoma %s\n",utent.nome, utent.palavra);

    if(!strcasecmp(utent.palavra, "fimb\n")){
      close(b_fifo_fd);
      close(c_fifo_fd);
      unlink(getenv("BALC_FIFO"));
      break;
    }

    if(!strcmp(utent.palavra, "fim\n")){
      close(c_fifo_fd);
      fprintf(stderr,"\nFIFO utente %s fechado\n",utent.nome);
    }

    strcpy(balc.palavra,utent.palavra);
    strcpy(balc.pnome,utent.nome);
    balc.pid = utent.pid_utent;
    fprintf(stderr, "\nutente %s sintoma %s\n",balc.pnome, balc.palavra);

    sprintf(c_fifo_fname, getenv("CLIENT_FIFO"), utent.pid_utent);

    c_fifo_fd = open(c_fifo_fname, O_WRONLY); //Abertura para leitura do FIFO do cliente

    if(c_fifo_fd == -1)
    perror("O Cliente nao esta disponivel");
    else{
      fprintf(stderr, "\nO Cliente esta pronto");

      res = write(c_fifo_fd, & balc, sizeof(balc)); //Escrita dos dados recebidos do cliente para o balcão

      if(res == sizeof(balc))
      fprintf(stderr,"\nescreveu ao Cliente %s\n",utent.palavra);
      else
      perror("\nerro a escrever ao Cliente");

      close(c_fifo_fd);
      fprintf(stderr,"\nFIFO utente fechado\n");
    }
  }

  fprintf(stdout,"\nBalcao de atendimento\n");
  printf("Insira os sintomas:\n");

//Pipe entre o balcão e o classificador
  id=fork();

  if(id == 0){
    dup(cla_to_bal[1]);
    close(cla_to_bal[1]);
    close(cla_to_bal[0]);

    dup(bal_to_cla[0]);
    close(bal_to_cla[0]);
    close(bal_to_cla[1]);

    execl("classificador", "classificador",NULL);

  }else{

    dup(cla_to_bal[0]);
    close(cla_to_bal[0]);
    close(cla_to_bal[1]);

    dup(bal_to_cla[1]);
    close(bal_to_cla[1]);
    close(bal_to_cla[0]);

    wait(NULL);

  }

  close(b_fifo_fd);
  unlink(getenv("BALC_FIFO"));

  return 0;
}
