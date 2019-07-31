/*
** Двунаправленный связный список
*/

#include <stdlib.h>
#include <string.h>

typedef struct	s_dlist
{
	char			data;
	struct s_dlist	*prev;
	struct s_dlist	*next;
}				t_dlist;

/*
** Создаёт новый элемент в начале списка и возвращает ссылку на него
*/

t_dlist		*dlist_new_at_start(t_dlist **root)
{
	t_dlist		*elem;

	if (root == NULL)
		return (NULL);
	if ((elem = (t_dlist*)malloc(sizeof(t_dlist))) == NULL)
		return (NULL);
	elem->prev = NULL;
	elem->next = *root;
	if (elem->next)
		elem->next->prev = elem;
	*root = elem;
	return (elem);
}

/*
** Создаёт новый элемент в конце списка и возвращает ссылку на него
*/

t_dlist		*dlist_new_at_end(t_dlist **root)
{
	t_dlist		*elem;
	t_dlist		*root_ptr;

	if (root == NULL)
		return (NULL);
	if ((elem = (t_dlist*)malloc(sizeof(t_dlist))) == NULL)
		return (NULL);
	elem->prev = NULL;
	elem->next = NULL;
	if (*root)
	{
		root_ptr = *root;
		while (root_ptr->next)
			root_ptr = root_ptr->next;
		root_ptr->next = elem;
		elem->prev = root_ptr;
	}
	else
		*root = elem;
	return (elem);
}

/*
** Возвращает i-ый элемент списка. Список начинается с нуля
*/

t_dlist		*dlist_get(t_dlist	*root, unsigned int i)
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

void		dlist_free_elem(t_dlist	*elem)
{
	free(elem);
}

/*
** Удаляет i-ый элемент списка. Список начинается с нуля
** Unnormed version
*/

void		dlist_free(t_dlist **root, unsigned int i)
{
	t_dlist		*prev_elem;
	t_dlist		*root_ptr;

	if (root == NULL || *root == NULL)
		return ;
	root_ptr = *root;
	if (i == 0)
	{
		*root = root_ptr->next;
		if (*root)
			(*root)->prev = NULL;
		dlist_free_elem(root_ptr);
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
			if (root_ptr->next)
				root_ptr->next->prev = prev_elem;
			dlist_free_elem(root_ptr);
		}
	}
}

/*
** Normed version (25 lines)
void		dlist_free(t_dlist **root, unsigned int i)
{
	t_dlist		*prev_elem;
	t_dlist		*root_ptr;

	if (root == NULL || *root == NULL)
		return ;
	root_ptr = *root;
	if (i == 0)
	{
		*root = root_ptr->next;
		if (*root)
			(*root)->prev = NULL;
		dlist_free_elem(root_ptr);
		return ;
	}
	while (i-- != 0 && root_ptr->next)
	{
		prev_elem = root_ptr;
		root_ptr = root_ptr->next;
	}
	if (i != 0)
		return ;
	prev_elem->next = root_ptr->next;
	if (root_ptr->next)
		root_ptr->next->prev = prev_elem;
	dlist_free_elem(root_ptr);
}*/


/*
** Удаляет связный список целиком
*/

void		dlist_free_all(t_dlist	**root)
{
	t_dlist		*root_ptr;
	t_dlist		*next_elem;

	if (root == NULL || *root == NULL)
		return ;
	root_ptr = *root;
	while (root_ptr)
	{
		next_elem = root_ptr->next;
		dlist_free_elem(root_ptr);
		root_ptr = next_elem;
	}
	*root = NULL;
}