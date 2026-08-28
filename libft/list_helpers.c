/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guthybarnakoppany <guthybarnakoppany@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 13:08:42 by dabdulla          #+#    #+#             */
/*   Updated: 2026/08/28 16:12:36 by guthybarnak      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_envs **lst, t_envs *new)
{
	t_envs	*tmp;

	if (!new || !lst)
		return ;
	if (!*lst)
	{
		*lst = new;
        return ;
	}
	tmp = ft_lstlast(*lst);
	tmp->next = new;
}
void	ft_lstdelone(t_envs *lst, void (*del)(void *))
{
    if (!lst || !del)
        return ;
    del(lst->value);
    free(lst);
    lst = NULL;
}
void	ft_lstclear(t_envs **lst, void (*del)(void *))
{
    t_envs *tmp;
    t_envs *next;

    if (!lst || !*lst || !del)
        return ;
    tmp = *lst;
    while (tmp)
    {
        next = tmp->next;
        del(tmp->value);
        free(tmp);
        tmp = next;
    }
    *lst = NULL;
}
void	ft_lstiter(t_envs *lst, void (*f)(void *))
{
    if(!lst || !f)
        return ;
    while (lst)
    {
        f(lst->value);
        lst = lst->next;
    }
}
t_envs	*ft_lstmap(t_envs *lst, void *(*f)(void *), void (*del)(void *))
{
    t_envs *new_list;
    t_envs *new_node;
    
    new_list = NULL;
    if(!lst || !f || !del)
        return (NULL);
    while (lst)
    {
        new_node = ft_lstnew(f(lst->value));
        if (!new_node)
        {
            ft_lstclear(&new_list, del);
            return (NULL);
        }
        ft_lstadd_back(&new_list, new_node);
        lst = lst->next;
    }
    return (new_list);
}