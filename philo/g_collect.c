#include "philo.h"

void	gc_free(t_gc_e *hd)
{
	t_gc_e	*h;
	t_gc_e	*tmp;

	h = hd;
	if (!hd)
		return ;
	while (h)
	{
		tmp = h->next;
		free(h->ptr);
		free(h);
		h = tmp;
	}
	h = NULL;
	tmp = NULL;
	hd = NULL;
}

void	set_zero(void *s, int size)
{
	int		i;
	char	*b;

	i = 0;
	b = (char *)s;
	while (i < size)
	{
		b[i] = 0;
		i++;
	}
}

t_gc_e	*gc_new(int size)
{
	t_gc_e	*nd;

	nd = (t_gc_e *)malloc(sizeof(t_gc_e));
	if (!nd)
		return (NULL);
	nd->ptr = malloc(size);
	nd->next = NULL;
	return (nd);
}

void	gc_add_back(t_gc_e **lst, t_gc_e *new)
{
	t_gc_e	*temp;

	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	temp = *lst;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}

void	*ft_allocate(int flag, int size)
{
	static t_gc_e	*hd;
	t_gc_e			*nd;

	if (flag == 36)
	{
		gc_free(hd);
		hd = NULL;
		return (NULL);
	}
	else
	{
		nd = gc_new(size);
		set_zero(nd->ptr, size);
		gc_add_back(&hd, nd);
		return (nd->ptr);
	}
}
