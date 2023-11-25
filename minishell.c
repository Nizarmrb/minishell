/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelmrabe <nelmrabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 16:02:05 by nelmrabe          #+#    #+#             */
/*   Updated: 2023/11/25 18:43:29 by nelmrabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main(int ac, char **av)
{
    char *line;
    while(1)
    {
        line = readline("minishell$ ");
        if (line == NULL)
            break;
        if (line[0] != '\0')
        {
            add_history(line);
            printf("%s\n", line);
        }
        free(line);
    }
}
