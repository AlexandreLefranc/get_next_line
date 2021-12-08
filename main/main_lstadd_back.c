#include "../get_next_line.h"
#include <stdio.h>

int main()
{
	t_list *lst;

	lst = NULL;
	char *str = strdup("Hello");
	ft_lstadd_back(&lst, *str);

	char *str = strdup("Salut");
	ft_lstadd_back(&lst, *str);

	char *str = strdup("Bonjourno");
	ft_lstadd_back(&lst, *str);

	char *str = strdup("Ni hao");
	ft_lstadd_back(&lst, *str);

	while (lst != NULL)
	{
		printf("%s\n", lst->content);
		lst = lst->next;
	}
}
