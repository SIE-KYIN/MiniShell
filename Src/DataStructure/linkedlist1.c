#include "../../Inc/minishell.h"

void add_node(t_list* list, int position, char *var, char *data){
    t_list_node* pre_node = NULL;
    t_list_node* new_node = NULL;
    t_list_node* next_node = NULL;
    if (0 <= position && position <= list->cnt)
    {
        new_node = (t_list_node *)malloc(sizeof(t_list_node));
        new_node->var = var;
        new_node->data = data;
        new_node->next = NULL;
        pre_node = get_node(list, position);
        if (pre_node->next)
            next_node = pre_node->next;
        pre_node->next = new_node;
        new_node->prev = pre_node;
        if (next_node){
            new_node->next = next_node;
            next_node->prev = new_node;
        }
        list->cnt++;
      }
}


t_list_node* get_node(t_list* list, int position){
  int i = -1;
  t_list_node* node;
  if(list){
    node = &(list->top);
    while(++i < position)
      node = node->next;
    return node;
  }
  else 
    return NULL;
}

void remove_node(t_list* list, int position)
{
  t_list_node* pre_node;
  t_list_node* curr_node;

  if(list){
    if(0<=position && position<=list->cnt)
    {
      pre_node = get_node(list, position);
      curr_node = pre_node->next;
      pre_node->next=curr_node->next;
      if (curr_node->next)
        curr_node->next->prev= pre_node;
      free(curr_node);
      list->cnt--;
    }
  }
}


void displayDoublyList(t_list* pList){
  int i = 0;
    printf("\x1b[0m현재 원소 개수 : %d\n", pList->cnt);
    for (i = 0; i < pList->cnt; i++)
      printf("[%d]: %s=%s\n", i, get_node(pList, i + 1)->var,get_node(pList, i + 1)->data);

}

int get_position(t_list *list, char *str)
{
  int i;
  t_list_node* node;

  i = 0;
  node = &(list->top);
  while(1)
  {
    node = node->next;
    if (is_same(node->var, str))
      break;
    i++;
  }
  return i + 1;
}