/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrea <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 18:40:08 by fgrea             #+#    #+#             */
/*   Updated: 2021/11/09 17:45:09 by fgrea            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*dst;
	t_list	*ret;

	dst = NULL;
	ret = dst;
	while (lst)
	{
		dst = ft_lstnew(f(lst->content));
		if (!dst)
		{
			ft_lstclear(&dst, (*del));
			return (NULL);
		}
		ft_lstadd_back(&ret, dst);
		lst = lst->next;
	}
	return (ret);
}
