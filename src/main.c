/* Numeros primos multithread
 *
 * Este programa recebera valores inteiros como entrada.
 * Ao receber um caractere fim de linha ('\n'), deve imprimir na tela o
 * numero de valores primos encontrados e, apos, encerrar.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

#define THREADS 4

#define NUMEROS 10000000

pthread_mutex_t chave;

int numerodivisores = 0, qtdprimos = 0;
int numeros[NUMEROS];
int completos[NUMEROS];
char c;
int i, r;

int primo(int a) {
  int n, numeroprimo = 0;
  numerodivisores = 0;
    if(a >= 2){ 
	
	  for(n = a; n >= 1; n--){
	    if(a%n == 0) numerodivisores++;    
  }
    /*printf("Num de divisores de %d\n = %d\n", a, numerodivisores);*/
    if(numerodivisores == 2)  numeroprimo = 1; 
    else numeroprimo = 0; 
  
  }
  return numeroprimo;
}

void* thread(void *arg) {
 
  int indice = 0;
  int *N = (int*)(arg);
  int M = (*N);
  while (1) {
    
    
    
    pthread_mutex_lock(&chave);
    /* Busca por uma instancia do problema que ainda nao foi resolvida */
    while ( (completos[indice] != 0) && (indice <= i)) {
      //printf("Thread %d testou instancia %d\n", M, instancia);
      indice++;
    }
    //printf("Thread %d tentando tomar intancia %d\n", M, instancia);
    if (indice > i) { /* Acabaram as instancias */
      pthread_mutex_unlock(&chave);
      break;
    }
    completos[indice] = 1; /* Proponho-me a resolver a instancia */
    
    
    if(primo(numeros[indice])) qtdprimos++;
    pthread_mutex_unlock(&chave);
    /*printf("A thread %d trata o numero %d\n", M, numeros[indice]);
    printf("Qtd de num primos = %d\n", qtdprimos);*/
}
  return NULL;
}

int main() {
  
  pthread_t threads[THREADS];
  int thread_id[THREADS];
  int j, k, h;
  i = 0;
  while ((c = getchar()) != '\n')
  {
    if (c != ' ') {
      
      if(c == ',');
      
      else numeros[i] = numeros[i] * 10 + c - '0'; 
    }
    
    else
        i++;
  }
  
  for(r = 0; r <= i; r++){
    completos[r] = 0;
  }
  
  
  /*Identificando threads*/
  for (h = 0; h < THREADS; h++) {
    thread_id[h] = h;
  }
  
  /*Criando threads*/
  for (h = 0; h < THREADS; h++) {
    pthread_create(&(threads[h]), NULL, thread, (void*)(&thread_id[h]));
  }
  
  /*Impondo espera às threads*/
  for (h = 0; h < THREADS; h++) {
    pthread_join(threads[h], NULL);
  }

  
  
  /*Teste inicial sem uso de threads*/
  /*for(j = 0; j <= i; j++){
    primo(numeros[j]);
  }*/
 
  printf("%d\n", qtdprimos);
  
  /*for(j = 0; j <= i; j++){
    printf("%d ", numeros[j]);
  }
  printf("\n");
  
  for(j = 0; j <= i; j++){
    printf("%d ",completos[j]);
  }
  printf("\n");*/
  return 0;
}
