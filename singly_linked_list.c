/*
** Однонаправленный связный список
*/

#include <stdlib.h>
#include <string.h>

typedef struct	s_slist
{
	char			data;
	struct s_slist	*next;
}				t_slist;

/*
** Создаёт новый элемент в начале списка и возвращает ссылку на него
*/

t_slist		*slist_new_at_start(t_slist **root)
{
	t_slist		*elem;

	if (root == NULL)
		return (NULL);
	if ((elem = (t_slist*)malloc(sizeof(t_slist))) == NULL)
		return (NULL);
	elem->next = *root;
	*root = elem;
	return (elem);
}

/*
** Создаёт новый элемент в конце списка и возвращает ссылку на него
*/

t_slist		*slist_new_at_end(t_slist **root)
{
	t_slist		*elem;
	t_slist		*root_ptr;

	if (root == NULL)
		return (NULL);
	if ((elem = (t_slist*)malloc(sizeof(t_slist))) == NULL)
		return (NULL);
	elem->next = NULL;
	if (*root)
	{
		root_ptr = *root;
		while (root_ptr->next)
			root_ptr = root_ptr->next;
		root_ptr->next = elem;
	}
	else
		*root = elem;
	return (elem);
}

/*
** Возвращает i-ый элемент списка. Список начинается с нуля
*/

t_slist		*slist_get(t_slist	*root, unsigned int i)
{

	if (!root)
		return (NULL);
	while (i-- != 0 && root->next)
		root = root->next;
	return ((i == 0) ? root : NULL);
}

/*
** Освобождает элемент из памяти.
** Доступна для модификации при необходимости дополнительных освобождений.
*/

void		slist_free_elem(t_slist	*elem)
{
	free(elem);
}

/*
** Удаляет i-ый элемент списка. Список начинается с нуля
*/

void		slist_free(t_slist **root, unsigned int i)
{
	t_slist		*prev_elem;
	t_slist		*root_ptr;

	if (root == NULL || *root == NULL)
		return ;
	root_ptr = *root;
	if (i == 0)
	{
		*root = root_ptr->next;
		slist_free_elem(root_ptr);
	}
	else
	{
		while (i-- != 0 && root_ptr->next)
		{
			prev_elem = root_ptr;
			root_ptr = root_ptr->next;
		}
		if (i == 0)
		{
			prev_elem->next = root_ptr->next;
			slist_free_elem(root_ptr);
		}
	}
}

/*
** Удаляет связный список целиком
*/

void		slist_free_all(t_slist	**root)
{
	t_slist		*root_ptr;
	t_slist		*next_elem;

	if (root == NULL || *root == NULL)
		return ;
	root_ptr = *root;
	while (root_ptr)
	{
		next_elem = root_ptr->next;
		slist_free_elem(root_ptr);
		root_ptr = next_elem;
	}
	*root = NULL;
}