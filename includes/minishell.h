#ifndef HEADER_UTILS_H
# define HEADER_UTILS_H

# include <dirent.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdbool.h>

typedef enum e_token
{
	WORD,
	HERE_DOC,
	AREDIR_OUT,
	QUOTE = '\'',
	DQUOTE = '\"',
	_SPACE = ' ',
	VAR = '$',
	PIPE = '|',
	REDIR_IN = '<',
	REDIR_OUT = '>',
}					t_token;

typedef enum e_state
{
	IN_DQUOTE,
	IN_QUOTE,
	DEFAULT,
}					t_state;

typedef struct s_elems
{
	char			*content;
	enum e_token	type;
	enum e_state	state;
	struct s_elems	*next;
}					t_elems;

#endif