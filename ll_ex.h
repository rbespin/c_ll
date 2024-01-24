#include <stdio.h>
#include <stdlib.h>

typedef void *ll_item;

typedef struct ll_node_t 
{
  ll_item item;
  struct ll_node_t *next;
  struct ll_node_t *prev;
}ll_node_t;

typedef struct ll_t{
  int num_elements;
  ll_node_t *front;
  ll_node_t *back;
}ll_t;

void ll_init(ll_t *self);

void ll_append(ll_t *self, ll_item item);

ll_item ll_peek_front(ll_t *self);

ll_item ll_peek_back(ll_t *self);

void ll_push(ll_t *self, ll_item item);

int ll_size(ll_t *self);

void ll_destroy(ll_t *self);

ll_item ll_pop(ll_t *self);

