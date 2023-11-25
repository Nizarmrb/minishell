/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelmrabe <nelmrabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 15:58:57 by nelmrabe          #+#    #+#             */
/*   Updated: 2023/11/25 18:45:36 by nelmrabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int is_special_char(char c)
{
    if (c == ' ' || c == '\t' || c == '\v' || c == '\'' || c == '\"' ||
        c == '|' || c == '<' || c == '>' || c == '$' || c == '\0' || c == '\n')
        return (1);
    return (0);
}

void    set_word(char *line, int *i, t_elems **head)
{
    int j;
    char *word;

    j = 0;
    while (!is_special_char(line[*i + j]))
        j++;
    word = ft_substr(line, *i, j);
    token_list_add(head, list_new(word, WORD));
    *i += j;
}

bool is_valid_var_char(char c, int position)
{
    return (ft_isalnum(c) || c == '_' ||
            (c == '?' && position == 0) ||
            (c == '@' && position == 0) ||
            (ft_isdigit(c) && position == 0));
}

bool should_break_var(char c, int position)
{
    return ((c == '@' || c == '?' || ft_isdigit(c)) && position == 0);
}

void    set_var(char *line, int *i, t_elems **head)
{
    int j;
    char *var;

    j = 0;
    while (is_valid_var_char(line[*i + j], j))
        j++;
    var = ft_substr(line, *i, j);
    token_list_add(head, list_new(var, VAR));
    *i += j;
}

void set_redir(char *line, int *i, t_elems **head)
{
    int j;
    char *redir;

    j = 0;
    while (line[*i + j] == '<' || line[*i + j] == '>')
        j++;
    redir = ft_substr(line, *i, j);
    token_list_add(head, list_new(redir, REDIR_IN));
    *i += j;
}

void	set_token_redir(char *line, t_elems *elem, int *i)
{
	if (line[*i] == '<')
	{
		if (line[*i + 1] == '<')
		{
			token_list_add(&elem, token_new("<<", 2, HERE_DOC, DEFAULT));
			*(i) += 1;
		}
		else
			token_list_add(&elem, token_new("<", 1, REDIR_IN, DEFAULT));
	}
	else if (line[*i] == '>')
	{
		if (line[*i + 1] == '>')
		{
			token_list_add(&elem, token_new(">>", 2, AREDIR_OUT, DEFAULT));
			*(i) += 1;
		}
		else
			token_list_add(&elem, token_new(">", 1, REDIR_OUT, DEFAULT));
	}
}

t_elems *lexer(char *line)
{
    int i;
    t_elems *head;
    
    i = 0;
    head = NULL;
    while (line[i]);
    {
        if (line[i] == ' ' || line[i] == '\t' || line[i] == '\v')
            token_list_add(&head, list_new(" ", _SPACE));
        else if (line[i] == '\'')
            token_list_add(&head, list_new("\'", QUOTE));
        else if (line[i] == '\"')
            token_list_add(&head, list_new("\"", DQUOTE));
        else if (line[i] == '|')
            token_list_add(&head, list_new("|", PIPE));
        else if (line[i] == '<' || line[i] == '>')
            set_redir(line, &i, &head);
        else if (line[i] == '$')
            token_list_add(&head, list_new("$", VAR));
        else
            set_word(line, &i, &head);
        i++;
    }
    return (head);
}
