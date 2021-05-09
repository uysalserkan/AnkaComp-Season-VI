#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <time.h>

int total = 0;
int *arr;
int counter = 0;
sem_t mutex;

void *thread_1_adding(void *val)
{
  int SIZE;
  SIZE = *((int *)val);

  while (1)
  {
    sem_wait(&mutex);

    if (counter != SIZE)
    {
      total = total + arr[counter];

      printf("Thread1 %d değerini okudu toplam %d \n", arr[counter], total);

      counter++;
    }
    else
    {
      printf("Thread1 okunacak değer bulunamadı.\n");

      sem_post(&mutex);

      break;
    }

    sem_post(&mutex);
  }
  return NULL;
}

void *thread_2_adding(void *val)
{
  int SIZE;
  SIZE = *((int *)val);

  while (1)
  {
    sem_wait(&mutex);

    if (counter != SIZE)
    {
      total = total + arr[counter];

      printf("Thread2 %d değerini okudu toplam = %d \n", arr[counter], total);

      counter++;
    }
    else
    {
      printf("Thread2 okunacak değer bulunamadı. \n");

      sem_post(&mutex);

      break;
    }

    sem_post(&mutex);
  }
  return NULL;
}

void generateRandoms();

int main()
{
  srand(time(0));

  int size;
  scanf("%d", &size);

  arr = malloc(size * sizeof(int));

  generateRandoms(0, 9, size);
  printf("Random Dizi => ");
  for (int i = 0; i < size; i++)
  {
    printf("%d ", arr[i]);
  }
  printf("\n");

  sem_init(&mutex, 0, 1);

  pthread_t t[2];

  pthread_create(&t[0], NULL, thread_1_adding, (void *)&size);
  pthread_create(&t[1], NULL, thread_2_adding, (void *)&size);

  pthread_join(t[0], NULL);
  pthread_join(t[1], NULL);
  sem_destroy(&mutex);
  free(arr);

  return 0;
}

void generateRandoms(int lower, int upper, int count)
{
  for (int i = 0; i < count; i++)
  {
    int num = (rand() % (upper - lower + 1)) + lower;
    arr[i] = num;
  }
}