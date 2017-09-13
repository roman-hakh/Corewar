#include "main.h"

int 				is_comment(char *str)
{
	while (*str <= 32 && *str != 0)
		str++;
	if (*str == '#')
		return (1);
	return (0);
}

t_array_string		**lex_analyze(t_main *main, t_data *code)
{
	t_array_string	**lex_strs;
	int 			i;
	int 			k;
	int 			ret;

	k = 0;
	i = -1;
	if ((lex_strs = (t_array_string **)
						malloc(sizeof(t_array_string *) * code->i)) == NULL)
		return (NULL);
	while (++i < code->i)
	{
		if (!is_empty_line(code->arr[i]) && !is_comment(code->arr[i]))
		{
			ret = check_bot_params(main->name, main->comment, code->arr[i]);
			(ret == 2) ? (main->name_exist = 1) : 0;
			(ret == 3) ? (main->comm_exist = 1) : 0;
			if (!ret)
			{
				lex_strs[k] = split_line(code->arr[i]);
				k++;
			}
		}
	}
	lex_strs[k] = NULL; //todo here may be leak
	return (lex_strs);
}

void				print_lex(t_array_string **lex_strs)
{
	int 			i;

	i = 0;
	while (lex_strs[i] != NULL)
	{
		print_array_string(lex_strs[i]);
		i++;
	}
}

void				del_lex_strs(t_array_string ***str)
{
	int 			i;

	i = 0;
	if (*str == NULL)
		return ;
	while ((*str)[i] != NULL)
	{
		del_array_string((*str) + i);
		i++;
	}
	free(*str);
	*str = NULL;
}