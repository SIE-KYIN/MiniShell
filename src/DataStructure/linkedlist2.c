#include "../minishell.h"

t_list	*create_list(void)
{
	t_list	*ret;

	ret = (t_list *)malloc(sizeof(t_list));
	ret->cnt = 0;
	ret->top.var = NULL;
  ret->top.data = NULL;
  ret->top.prev = NULL;
  ret->top.next = NULL;
	return (ret);
}

void delete_list(t_list *list)
{
  if (list)
  {
    while (list->cnt > 0)
      remove_node(list, list->cnt - 1);
    free(list);
  }
}
