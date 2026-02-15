/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hudescam <hudescam@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 14:24:09 by hudescam          #+#    #+#             */
/*   Updated: 2025/08/30 14:43:54 by hudescam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*newnod;

	newnod = malloc(sizeof(t_list));
	if (!newnod)
		return (NULL);
	newnod->content = content;
	newnod->next = NULL;
	return (newnod);
}
