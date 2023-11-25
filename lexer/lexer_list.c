/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelmrabe <nelmrabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 15:47:37 by nelmrabe          #+#    #+#             */
/*   Updated: 2023/11/22 15:58:42 by nelmrabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_elems *list_new(char *content, t_token type)
{
    t_elems *new;

    new = (t_elems *)malloc(sizeof(t_elems));
    if (!new)
        return (NULL);
    new->content = ft_strdup(content);
    new->type = type;
    new->state = DEFAULT;
    new->next = NULL;
    return (new);
}

void    list_add_back(t_elems **head, t_elems *new)
{
    t_elems *tmp;

    if (!head || !new)
        return ;
    if (!*head)
    {
        *head = new;
        return ;
    }
    tmp = *head;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new;
}
