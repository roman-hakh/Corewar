#include "main.h"

int			is_error_zjmp(t_main *main, t_array_string *lex_str, char op)
{
	if (op == (char)0x80)
		return (0);
	print_syntax_error("wrong argument in line", lex_str, main);
	return (1);
}

void		build_args_zjmp(t_main *main, t_array_string *lex_str, int *args, int i)
{
	args[0] = get_arg(main, lex_str, &i);
}

void		command_zjmp(t_main *main, t_array_string *lex_str)
{
	int 	i;
	int 	args[3];

	char    op;
	int     ret;

	i = 0;
	ft_bzero(args, sizeof(int) * 3);

	if (lex_str->i >= 1 && !ft_strcmp(lex_str->arr[1], ":") && !is_command(lex_str->arr[0]))
		i = 2;

	op = 0;
	ret = get_op_code(lex_str, &op, i + 1, 1);
	print_string(lex_str);
	ft_printf("ret = %d, OP_CODE = %x\n", ret, op);

	if (ret == 0 || is_error_zjmp(main, lex_str, op))
		return ;

	build_args_zjmp(main, lex_str, args, i + 1);
	add_bcode(&main->bcode, new_bcode(9, op, args));
	main->pc += 3;
}

