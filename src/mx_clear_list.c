#include "libmx.h"

void mx_clear_list(t_list **list, bool is_free)
{
	if (!list)
		return;

	while (*list)
	{
		t_list *temp = (*list)->next;
		if (is_free)
			free((*list)->data);
		free(*list);
		*list = temp;
	}
}
