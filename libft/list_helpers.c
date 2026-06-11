/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabdulla <dabdulla@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 13:08:42 by dabdulla          #+#    #+#             */
/*   Updated: 2026/02/21 15:40:57 by dabdulla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*tmp;

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
void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
    if (!lst || !del)
        return ;
    del(lst->content);
    free(lst);
    lst = NULL;
}
void	ft_lstclear(t_list **lst, void (*del)(void *))
{
    t_list *tmp;
    t_list *next;

    if (!lst || !*lst || !del)
        return ;
    tmp = *lst;
    while (tmp)
    {
        next = tmp->next;
        del(tmp->content);
        free(tmp);
        tmp = next;
    }
    *lst = NULL;
}
void	ft_lstiter(t_list *lst, void (*f)(void *))
{
    if(!lst || !f)
        return ;
    while (lst)
    {
        f(lst->content);
        lst = lst->next;
    }
}
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
    t_list *new_list;
    t_list *new_node;
    
    new_list = NULL;
    if(!lst || !f || !del)
        return (NULL);
    while (lst)
    {
        new_node = ft_lstnew(f(lst->content));
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