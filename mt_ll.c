#include <stdio.h>
#include "ll_ex.h"
#include <pthread.h>
#include <unistd.h>
#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"

/* Tests initialization of linked list and size to be zero */
int test1(void)
{
  ll_t *ll = (ll_t *)malloc(sizeof(ll_t));
  ll_init(ll);
  int sz = ll_size(ll);
  ll_destroy(ll);
  free(ll);
  return (sz==0);
}

/* Tests that appending a single item to linked list will be size 1 */
int test2(void)
{
  ll_t *ll = (ll_t *)malloc(sizeof(ll_t));
  ll_init(ll);
  ll_item item = NULL;
  ll_append(ll,item);
  int sz = ll_size(ll);
  ll_destroy(ll);
  free(ll);
  return sz == 1;
}

/* Tests that appending two items to linked list will be size 2 */
int test3(void)
{
  ll_t *ll = (ll_t *)malloc(sizeof(ll_t));
  ll_init(ll);
  ll_item item1 = NULL;
  ll_item item2 = NULL;
  ll_append(ll,item1);
  ll_append(ll,item2);
  int sz = ll_size(ll);
  ll_destroy(ll);
  free(ll);
  return sz == 2;
}

/* Tests that appending 100 items to linked list will be size 100 */
int test4(void)
{
  ll_t *ll = (ll_t *)malloc(sizeof(ll_t));
  ll_init(ll);
  int i;
  for(i = 0; i < 100; i++)
  {
    ll_item item = NULL;
    ll_append(ll,item);
  }
  int sz = ll_size(ll);
  ll_destroy(ll);
  free(ll);
  return sz == 100;
}

/* Tests that appending 1000 items to linked list will be size 1000 */
int test5(void)
{
  ll_t *ll = (ll_t *)malloc(sizeof(ll_t));
  ll_init(ll);
  int i;
  for(i = 0; i < 1000; i++)
  {
    ll_item item = NULL;
    ll_append(ll,item);
  }
  int sz = ll_size(ll);
  ll_destroy(ll);
  free(ll);
  return sz == 1000;
}

/* Tests that we are appropriately adding items to the front by 
 * testing that the first item goes to the back */
int test6(void)
{
  ll_t *ll = (ll_t *)malloc(sizeof(ll_t));
  ll_init(ll);
  ll_item back_item = (void *)malloc(100);
  ll_append(ll,back_item);

  int i;
  for(i = 0; i < 1000; i++)
  {
    ll_item item = NULL;
    ll_append(ll,item);
  }

  int sz = ll_size(ll);
  int cmp = ll_peek_back(ll) == back_item;
  ll_destroy(ll);
  free(ll);
  free(back_item);
  return sz == 1001 && cmp;
}

/* Tests that we pop off correctly */
int test7(void)
{
  ll_t *ll = (ll_t *)malloc(sizeof(ll_t));
  ll_init(ll);
  int i;
  int cmp = 1;
  for(i = 0; i < 1000; i++)
  {
    ll_item item = (void *)malloc(1);
    ll_append(ll,item);
    ll_item pop_item = ll_pop(ll);
    cmp *= (pop_item == item);
    free(item);
  }

  int sz = ll_size(ll);
  ll_destroy(ll);
  free(ll);
  return sz == 0 && cmp;
}

/* Tests that we get null on an empty pop */
int test8(void)
{
  ll_t *ll = (ll_t *)malloc(sizeof(ll_t));
  ll_init(ll);
  ll_item pop_item = ll_pop(ll);
  int sz = ll_size(ll);
  ll_destroy(ll);
  free(ll);
  return sz == 0 && pop_item == NULL;
}

/* Tests that we get null on an empty pop after adding and popping */
int test9(void)
{
  ll_t *ll = (ll_t *)malloc(sizeof(ll_t));
  ll_init(ll);
  int i;
  for(i = 0; i < 1000; i++)
  {
    ll_append(ll,(void *)malloc(1000));
  }
  for(i = 0; i < 1000; i++)
  {
    ll_item pop_item = ll_pop(ll);
    free(pop_item);
  }
  ll_item pop_item = ll_pop(ll);
  int sz = ll_size(ll);
  ll_destroy(ll);
  free(ll);
  return sz == 0 && pop_item == NULL;
}

/* Tests that we get add & pop in correct order, even after
 * fully popping & appending */
int test10(void)
{
  ll_t *ll = (ll_t *)malloc(sizeof(ll_t));
  ll_init(ll);
  
  ll_item items[1000];
  int i;
  int cmp = 1;
  for(i = 0; i < 1000; i++)
  {
    items[i] = (void *)malloc(1000);
  }

  for(i = 0; i < 1000; i++)
  {
    ll_append(ll,items[i]);
  }

  for(i = 0; i < 1000; i++)
  {
    ll_item pop_item = ll_pop(ll);
    cmp *= (pop_item == items[1000-i-1]);
    free(pop_item);
  }

  for(i = 0; i < 500; i++)
  {
    items[i] = (void *)malloc(1000);
  }

  for(i = 0; i < 500; i++)
  {
    ll_append(ll,items[i]);
  }

  for(i = 0; i < 500; i++)
  {
    ll_item pop_item = ll_pop(ll);
    cmp *= (pop_item == items[500-i-1]);
    free(pop_item);
  }

  ll_item pop_item = ll_pop(ll);
  int sz = ll_size(ll);
  ll_destroy(ll);
  free(ll);
  return sz == 0 && cmp && pop_item == NULL;
}

/* Tests that we get add & pop in correct order, even after
 * fully popping & pushing */
int test11(void)
{
  ll_t *ll = (ll_t *)malloc(sizeof(ll_t));
  ll_init(ll);
  
  ll_item items[1000];
  int i;
  int cmp = 1;
  for(i = 0; i < 1000; i++)
  {
    items[i] = (void *)malloc(1000);
  }

  for(i = 0; i < 1000; i++)
  {
    ll_push(ll,items[i]);
  }

  for(i = 0; i < 1000; i++)
  {
    ll_item pop_item = ll_pop(ll);
    cmp *= (pop_item == items[i]);
    free(pop_item);
  }

  for(i = 0; i < 500; i++)
  {
    items[i] = (void *)malloc(1000);
  }

  for(i = 0; i < 500; i++)
  {
    ll_push(ll,items[i]);
  }

  for(i = 0; i < 500; i++)
  {
    ll_item pop_item = ll_pop(ll);
    cmp *= (pop_item == items[i]);
    free(pop_item);
  }

  ll_item pop_item = ll_pop(ll);
  int sz = ll_size(ll);
  ll_destroy(ll);
  free(ll);
  return sz == 0 && cmp && pop_item == NULL;
}

/* Tests that appending a single item to linked list will be size 1 */
int test12(void)
{
  ll_t *ll = (ll_t *)malloc(sizeof(ll_t));
  ll_init(ll);
  ll_item item = NULL;
  ll_push(ll,item);
  int sz = ll_size(ll);
  ll_destroy(ll);
  free(ll);
  return sz == 1;
}

/* Tests that appending two items to linked list will be size 2 */
int test13(void)
{
  ll_t *ll = (ll_t *)malloc(sizeof(ll_t));
  ll_init(ll);
  ll_item item1 = NULL;
  ll_item item2 = NULL;
  ll_push(ll,item1);
  ll_push(ll,item2);
  int sz = ll_size(ll);
  ll_destroy(ll);
  free(ll);
  return sz == 2;
}

/* Tests that pushing 100 items to linked list will be size 100 */
int test14(void)
{
  ll_t *ll = (ll_t *)malloc(sizeof(ll_t));
  ll_init(ll);
  int i;
  for(i = 0; i < 100; i++)
  {
    ll_item item = NULL;
    ll_push(ll,item);
  }
  int sz = ll_size(ll);
  ll_destroy(ll);
  free(ll);
  return sz == 100;
}

/* Tests that we are appropriately adding items to the back by 
 * testing that the first item goes to the front */
int test15(void)
{
  ll_t *ll = (ll_t *)malloc(sizeof(ll_t));
  ll_init(ll);
  ll_item front_item = (void *)malloc(100);
  ll_push(ll,front_item);

  int i;
  for(i = 0; i < 1000; i++)
  {
    ll_item item = NULL;
    ll_push(ll,item);
  }

  int sz = ll_size(ll);
  int cmp = ll_peek_front(ll) == front_item;
  ll_destroy(ll);
  free(ll);
  free(front_item);
  return sz == 1001 && cmp;
}

/* Tests that we get add & pop in correct order, even after
 * fully popping & pushing & appending */
int test16(void)
{
  ll_t *ll = (ll_t *)malloc(sizeof(ll_t));
  ll_init(ll);
  
  ll_item items[1000];
  int i;
  int cmp = 1;
  for(i = 0; i < 1000; i++)
  {
    items[i] = (void *)malloc(1000);
  }

  for(i = 0; i < 1000; i++)
  {
    ll_push(ll,items[i]);
  }

  for(i = 0; i < 1000; i++)
  {
    ll_item pop_item = ll_pop(ll);
    cmp *= (pop_item == items[i]);
    free(pop_item);
  }

  for(i = 0; i < 500; i++)
  {
    items[i] = (void *)malloc(1000);
  }

  for(i = 0; i < 500; i++)
  {
    ll_append(ll,items[i]);
  }

  for(i = 0; i < 500; i++)
  {
    ll_item pop_item = ll_pop(ll);
    cmp *= (pop_item == items[500-1-i]);
    free(pop_item);
  }

  ll_item pop_item = ll_pop(ll);
  int sz = ll_size(ll);
  ll_destroy(ll);
  free(ll);
  return sz == 0 && cmp && pop_item == NULL;
}

void test(int (*fn_ptr)(void), char *fn_name)
{
  if(fn_ptr())
  {
    printf("[%s] %sPassed.%s\n",fn_name,BLU,RESET);
  }
  else
  {
    printf("[%s] %sFailed.%s\n",fn_name,RED,RESET);
  }
}

typedef struct consumer_t
{
  int thread_id;
  ll_t *ll;
  int times_added;
  int call_limit;
  pthread_mutex_t *ll_mtx;
  pthread_cond_t *ll_cond;
}consumer_t;

typedef struct producer_t
{
  int thread_id;
  ll_t *ll;
  int times_popped;
  int call_limit;
  pthread_mutex_t *ll_mtx;
  pthread_cond_t *ll_cond;
}producer_t;

void consumer_thread_func(void *args)
{
  consumer_t *c_arg = (consumer_t *)args;

  int lock_return = -1;
  int num_elements = 0;
  ll_item pop_item;

  while(c_arg->times_added < c_arg->call_limit)
  {
#if 1
    printf("[consumer_thread_func] function called! thread_id: [%d],[%p],[%p],[%p], times_called: [%d]\n",
           c_arg->thread_id,&(c_arg->thread_id), c_arg->ll,c_arg->ll_mtx,c_arg->times_added);
#endif

    /* Obtain resource lock */
    lock_return = pthread_mutex_lock(c_arg->ll_mtx);
    if(lock_return == -1)
    {
      printf("[producer_thread_func] Error with pthread_mutex_lock()!\n");
      return;
    }

    /* We have resource lock. If resource linked list is empty, 
     * wait until there is something in it */
    while((num_elements = ll_size(c_arg->ll)) <= 0)
    {
      pthread_cond_wait(c_arg->ll_cond,c_arg->ll_mtx);
    }

    pop_item = ll_pop(c_arg->ll);
    free(pop_item);
    c_arg->times_added++;
    pthread_mutex_unlock(c_arg->ll_mtx);
  }

  return;
}

void producer_thread_func(void *args)
{
  producer_t *p_arg = (producer_t *)args;

  int lock_return = -1;
  int num_elements = 0;
  ll_item push_item;

  while(p_arg->times_popped < p_arg->call_limit)
  {
#if 1
    printf("[producer_thread_func] function called! thread_id: [%d],[%p],[%p],[%p], times_called: [%d]\n",
           p_arg->thread_id,&(p_arg->thread_id), p_arg->ll,p_arg->ll_mtx,p_arg->times_popped);
#endif
    /* Obtain resource lock */
    lock_return = pthread_mutex_lock(p_arg->ll_mtx);
    if(lock_return == -1)
    {
      printf("[producer_thread_func] Error with pthread_mutex_lock()!\n");
      return;
    }
    /* There is at least one element, pop it, release mutex */
    push_item = (void *)malloc((((float)rand())/RAND_MAX)*1000);
    if((((float)rand())/RAND_MAX) > 0.5)
    {
      ll_append(p_arg->ll,push_item);
    }
    else
    {
      ll_push(p_arg->ll,push_item);
    } 
    p_arg->times_popped+=1;
    pthread_cond_broadcast(p_arg->ll_cond);
    pthread_mutex_unlock(p_arg->ll_mtx);
    if((((float)rand())/RAND_MAX) > 0.01)
    {
      usleep(100);
    }
  }
  return;
}

int main(int argc, char **argv)
{
#if 1
  test(&test1,  "test1");
  test(&test2,  "test2");
  test(&test3,  "test3");
  test(&test4,  "test4");
  test(&test5,  "test5");
  test(&test6,  "test6");
  test(&test7,  "test7");
  test(&test8,  "test8");
  test(&test9,  "test9");
  test(&test10, "test10");
  test(&test11, "test11");
  test(&test12, "test12");
  test(&test13, "test13");
  test(&test14, "test14");
  test(&test15, "test15");
  test(&test16, "test16");
#endif

  int NUM_THREADS = 100;
  int CALL_LIMIT = 500;

  srand(time(NULL));
  pthread_t consumers[NUM_THREADS];
  pthread_t producers[NUM_THREADS];
  consumer_t *c_arg[NUM_THREADS];

  pthread_mutex_t ll_mtx = PTHREAD_MUTEX_INITIALIZER;
  pthread_cond_t ll_cond = PTHREAD_COND_INITIALIZER;
  producer_t *p_arg[NUM_THREADS];

  int i;
  ll_t *ll_master = (ll_t *)malloc(sizeof(ll_t));
  ll_init(ll_master);
  for(i = 0; i < NUM_THREADS; i++)
  {
    c_arg[i] = (consumer_t *)malloc(sizeof(consumer_t));
    c_arg[i]->thread_id = i; 
    c_arg[i]->ll = ll_master;
    c_arg[i]->times_added = 0;
    c_arg[i]->ll_mtx = &ll_mtx;
    c_arg[i]->ll_cond = &ll_cond;
    c_arg[i]->call_limit = CALL_LIMIT;

    p_arg[i] = (producer_t *)malloc(sizeof(producer_t));
    p_arg[i]->thread_id = i; 
    p_arg[i]->ll = ll_master;
    p_arg[i]->times_popped = 0;
    p_arg[i]->ll_mtx = &ll_mtx;
    p_arg[i]->ll_cond = &ll_cond;
    p_arg[i]->call_limit = CALL_LIMIT;

    pthread_create(&consumers[i], NULL, (void *)&consumer_thread_func, (void *)(c_arg[i]));
    pthread_create(&producers[i], NULL, (void *)&producer_thread_func, (void *)(p_arg[i]));
  }
  for(i = 0; i < NUM_THREADS; i++)
  {
    pthread_join(consumers[i],NULL);
    pthread_join(producers[i],NULL);
  }

  /* Clean up args & linked list */
  for(i = 0; i < NUM_THREADS; i++)
  {
    free(p_arg[i]);
    free(c_arg[i]);
  }
  ll_destroy(ll_master);
  free(ll_master);

  return 0;

}
