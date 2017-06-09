#include "main.h"

void		set_labels(t_main *main)
{
	int 	i;

	i = 0;
	while (main->lex_strings[i] != NULL)
	{
		if (main->lex_strings[i]->i > 1)
			if (main->lex_strings[i]->arr[1] != NULL && !strcmp(main->lex_strings[i]->arr[1], ":") && !is_command(main->lex_strings[i]->arr[0]))
				add_label_to_table(&main->table, new_label_table(main->lex_strings[i]->arr[0], 0));
		i++;
	}
}

void		create_com_line(t_main *main, t_array_string *lex_str)
{
	char 	*str;

	str = lex_str->arr[0];
	if (!ft_strcmp(lex_str->arr[1], ":") && !is_command(lex_str->arr[0]))
	{
		if (lex_str->i >= 3)
			str = lex_str->arr[2];
		else
			return;
	}
	(ft_strcmp(str, "live")) ? 0 : (command_live(main, lex_str));
	(ft_strcmp(str, "ld")) ? 0 : (command_ld(main, lex_str));
	(ft_strcmp(str, "st")) ? 0 : (command_st(main, lex_str));
	(ft_strcmp(str, "add")) ? 0 : (command_add(main, lex_str));
	(ft_strcmp(str, "sub")) ? 0 : (command_sub(main, lex_str));
	(ft_strcmp(str, "and")) ? 0 : (command_and(main, lex_str));
	(ft_strcmp(str, "or")) ? 0 : (command_or(main, lex_str));
	(ft_strcmp(str, "xor")) ? 0 : (command_xor(main, lex_str));
	(ft_strcmp(str, "zjmp")) ? 0 : (command_zjmp(main, lex_str));
	(ft_strcmp(str, "ldi")) ? 0 : (command_ldi(main, lex_str));
	(ft_strcmp(str, "sti")) ? 0 : (command_sti(main, lex_str));
	(ft_strcmp(str, "fork")) ? 0 : (command_fork(main, lex_str));
	(ft_strcmp(str, "lld")) ? 0 : (command_lld(main, lex_str));
	(ft_strcmp(str, "lldi")) ? 0 : (command_lldi(main, lex_str));
	(ft_strcmp(str, "lfork")) ? 0 : (command_lfork(main, lex_str));
	(ft_strcmp(str, "aff")) ? 0 : (command_aff(main, lex_str));

}

void		build_bcode(t_main *main)
{
	int 	i;
	t_label_table	*link;

	i = 0;
	while (main->lex_strings[i] != NULL)
	{
		if (main->lex_strings[i]->i >= 2)
		{
			if (1 < main->lex_strings[i]->i && !ft_strcmp(main->lex_strings[i]->arr[1], ":") && !is_command(main->lex_strings[i]->arr[0]))
			{
				link = find_label_by_name(main->table, main->lex_strings[i]->arr[0]);
				link->offset = main->pc;
			}
			create_com_line(main, main->lex_strings[i]);
		}
		else
		{
			ft_printf("{red}Error:{eoc} {yellow}wrong command or label: {eoc}");
			print_string(main->lex_strings[i]);
			ft_printf("\n");
		}
		i++;
	}
}

void		syntax_analyze(t_main *main)
{
	set_labels(main);

	build_bcode(main);
	del_bcode(&main->bcode);
	main->pc = 0;

	build_bcode(main);
	print_bcode(main->bcode);
	print_label_table(main->table);
}
