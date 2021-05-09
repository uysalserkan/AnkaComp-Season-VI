#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <time.h>

int total = 0;
int *arr;
int counter = 0;
sem_t mutex;

void generateRandoms();
void *thread_1_adding(void *val); // 0 to size
void *thread_2_adding(void *val); // size to 0

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

void *thread_1_adding(void *val)
{
  int SIZE;
  int forward = 0;
  SIZE = *((int *)val);

  while (1)
  {
    sem_wait(&mutex);

    if (counter != SIZE)
    {
      total = total + arr[forward];

      printf("Thread1 %d değerini okudu toplam = %d \n", arr[forward], total);
      forward++;
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
  int arr_size;
  int reverse = 1;
  arr_size = *((int *)val);

  while (1)
  {
    sem_wait(&mutex);

    if (counter != arr_size)
    {
      total = total + arr[arr_size - reverse];

      printf("Thread2 %d değerini okudu toplam = %d \n", arr[arr_size - reverse], total);

      counter++;
      reverse++;
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
