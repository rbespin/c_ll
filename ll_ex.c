#include "ll_ex.h"

#define DEBUG_PRINT 0


void ll_init(ll_t *self)
{
#if DEBUG_PRINT
  printf("[ll_ex] Initializing ll_t: [%p]\n", self);
#endif
  self->num_elements = 0;
  self->front = NULL;
  self->back = NULL;
}

void ll_destroy(ll_t *self)
{
#if DEBUG_PRINT
  printf("[ll_destroy] Destroying ll_t: [%p]\n",self);
#endif
  ll_node_t *iter = self->back;
  ll_node_t *tmp;
  while(iter != NULL)
  {
#if DEBUG_PRINT
    printf("[ll_destroy] Destroying: [%p]\n", iter);
#endif
    tmp = iter;
    iter = iter->prev;
    free(tmp);
  }
}

int ll_size(ll_t *self)
{
  return self->num_elements;
}

/* Places an item to the beginning of the list */
void ll_append(ll_t *self, ll_item item)
{
  ll_node_t *node;
  node = (ll_node_t *)malloc(sizeof(ll_node_t));
  node->item = item;
#if DEBUG_PRINT
  printf("[ll_append] Adding node: [%p]\n", node);
#endif

  /* If list is empty, this node becomes front & back */
  if(self->num_elements == 0)
  {
    node->next = NULL;
    node->prev = NULL;
    self->front = node;
    self->back = node;
  }

  /* If list is of size one, this node becomes new front 
   * and old front becomes back */
  else if(self->num_elements == 1)
  {
    node->next = self->front;
    node->prev = NULL;
    self->back = self->front;
    self->back->prev = node;
    self->back->next = NULL;
    self->front = node;
  }
  
  else
  {
    node->next = self->front;
    node->prev = NULL;
    self->front->prev = node;
    self->front = node;
  }

  self->num_elements++;

}

void ll_print(ll_t *self)
{
  printf("[ll_print] Total size: [%d]", ll_size(self));
}


ll_item ll_peek_front(ll_t *self)
{
  return (void *)self->front->item;
}

ll_item ll_peek_back(ll_t *self)
{
  return (void *)self->back->item;
}

ll_item ll_pop(ll_t *self)
{
  ll_node_t *node;
  ll_node_t *tmp;
  ll_item item;

  /* return NULL for empty list */
  if(ll_size(self) == 0)
  {
    self->front = NULL;
    self->back = NULL;
    return NULL;
  }
  else if(ll_size(self) == 1)
  {
    node = self->front;
    self->front = NULL;
    self->back = NULL;
    self->num_elements = 0;
    item = node->item;
    free(node);
    return item;
  }
  else
  {
    node = self->front;
    self->front = self->front->next;
    self->front->prev = NULL;
    self->num_elements--;
    item = node->item;
    free(node);
    return item;
  }
}

/* Puts an item to the end of the list */
void ll_push(ll_t *self, ll_item item)
{
  ll_node_t *node;
  node = (ll_node_t *)malloc(sizeof(ll_node_t));
  node->item = item;
#if DEBUG_PRINT
  printf("[ll_push] Adding node: [%p]\n", node);
#endif

  /* If list is empty, this node becomes front & back */
  if(self->num_elements == 0)
  {
    node->next = NULL;
    node->prev = NULL;
    self->front = node;
    self->back = node;
  }

  /* If list is of size one, this node becomes new back */
  else if(self->num_elements == 1)
  {
    node->next = NULL;
    node->prev = self->front;
    self->front->next = node;
    self->back = node;
  }
  
  else
  {
    node->prev = self->back;
    node->next = NULL;
    self->back->next = node;
    self->back = node;
  }

  self->num_elements++;
}
