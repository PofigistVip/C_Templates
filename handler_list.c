/*
** Список обработчиков - список функций
** При передаче параметра будет вызвана одна из функций списка в зависимости от полученного параметра
*/

#include <stdlib.h>
#include <string.h>

typedef struct	s_handler
{
	char			value;
	void			(*f)(void);
	struct s_handler	*next;
}				t_handler;

/*
** Добавляет новый обработчик в список
*/

t_handler		*handler_add(t_handler **root, char on_value, void (*f)(void))
{
	t_handler		*elem;

	if (root == NULL)
		return (NULL);
	if ((elem = (t_handler*)malloc(sizeof(t_handler))) == NULL)
		return (NULL);
	elem->next = *root;
	elem->value = on_value;
	elem->f = f;
	*root = elem;
	return (elem);
}

/*
** Добавляет обработчик по умолчанию
** Если обработчик по умолчанию не был добавлен этой командой им будет считаться первый добавленный обработчик списка
*/

t_handler		*handler_add_default(t_handler **root, void (*f)(void))
{
	t_handler		*elem;
	t_handler		*root_ptr;

	if (root == NULL)
		return (NULL);
	if ((elem = (t_handler*)malloc(sizeof(t_handler))) == NULL)
		return (NULL);
	elem->next = NULL;
	elem->f = f;
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
** Позволяет вызвать необходимую функцию по значению
** Вызовет обработчик по умолчанию если совпадения не было найдено
*/

void			handler_handle(t_handler *root, char value)
{
	if (root == NULL)
		return ;
	while (root->next)
	{
		if (root->value = value)
		{
			root->f();
			return ;
		}
		root = root->next;
	}
	root->f();
}

/*
** Освобождает обработчик из памяти.
** Доступна для модификации при необходимости дополнительных освобождений.
*/

void		handler_free_elem(t_handler	*elem)
{
	free(elem);
}

/*
** Полностью удаляет список обработчиков
*/

void		handler_free_all(t_handler	**root)
{
	t_handler		*root_ptr;
	t_handler		*next_elem;

	if (root == NULL || *root == NULL)
		return ;
	root_ptr = *root;
	while (root_ptr)
	{
		next_elem = root_ptr->next;
		handler_free_elem(root_ptr);
		root_ptr = next_elem;
	}
	*root = NULL;
}