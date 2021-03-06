/**
 * TP2 - EXO1 - Création de threads
 *
 * @author Ilyas LaCamora <lacamoraproduction@gmail.com>
 * @copyright (c) 2014, LaCamora
 *
 * @version 1.0
 * @package LaCamora/M1/PR
 */

#ifndef _XOPEN_SOURCE
#define _XOPEN_SOURCE 700
#endif

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#ifndef N
#define N 5
#endif

/**
 * Fonction executée par les threads créés
 * Affiche son numéro d'ordre et son tid
 * se termine en retournant son num*2
 */
void *thread_rand(void *arg)
{
  int i = *(int *)arg;
  printf("Thread num%d, tid%d\n",i, (int) pthread_self());
  pthread_exit((void*)(i * 2));
  return NULL;
}

/**
 * Fonction principale
 */
int main(int argc, char** argv)
{
  pthread_t tid[N];
  int i = -1;
  int *pt_ind;
  char* arg;
  while ( ++i < N ){
    pt_ind = (int*) malloc(sizeof(i));
    *pt_ind = i;
    if ( pthread_create(&(tid[i]), NULL, thread_rand, (void *)pt_ind)){
      perror("error : pthread_create\n");
      exit(1);
    }
  }
  i = -1;
  int s_retour;
  while ( ++i < N ){
    if ( pthread_join(tid[i], (void **)&s_retour) ){
      perror("error : pthread_join\n");
      exit(1);
    }
    printf("Main : thread %d terminé, status = %d\n",i,s_retour);
  }
  printf("Tous les threads sont terminés\n");
  return EXIT_SUCCESS;
}
