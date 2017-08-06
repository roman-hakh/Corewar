#include "vm.h"

t_bot		*bot_new(int number, t_string *code)
{
	t_bot	*bot;

	if ((bot = (t_bot *)malloc(sizeof(t_bot))) == NULL)
		return (NULL);
	ft_bzero(bot, sizeof(t_bot));
	bot->code = code;
	bot->number = number;
	return (bot);
}

void		bot_del(t_bot **pbot)
{
	t_bot	*bot;

	if (pbot && *pbot)
	{
		bot = *pbot;
		if (bot->name)
			free(bot->name);
		if (bot->comment)
			free(bot->comment);
		if (bot->code)
			string_del(&(bot->code));
		*pbot = NULL;
	}
}

void		print_bcode(const char *code, int len)
{
	int 	i;

	i = 0;
	if (code)
	{
		ft_printf("{yellow}BCode = {\n{eoc}");
		while (i < len)
		{
			ft_printf("%0.2hhx ", code[i]);
			i++;
		}
		ft_printf("\n{yellow}}{eoc}");
	}
}

int 		read_bot(t_string *code, char *file_name)
{
	int		fd;
	int 	len;
	char	buff[BUFF_SIZE + 1];

	fd = open(file_name, O_RDONLY);
	ft_bzero(buff, BUFF_SIZE + 1);
	if (fd > 0)
	{
		while ((len = (int)read(fd, buff, BUFF_SIZE)) > 0)
		{
			string_append(code, buff, len);
			ft_bzero(buff, len + 1);
		}
		if (len == 0)
			return (0);
		else
			return (1);
	}
	return (1);
}

int 		get_number_from_bcode(const unsigned char *code, int num_size)
{
	int 			i;
	int 			num;
	unsigned char	*pnum;

	num = 0;
	pnum = (unsigned char *)(&num);
	i = 0;
	code += sizeof(int) - 1;
	while (i < num_size)
	{
		*pnum = *code;
		code--;
		pnum++;
		i++;
	}
	return (num);
}

int 		validate_magic_number(t_bot *bot)
{
	int 	mag_num;

	mag_num = get_number_from_bcode((const unsigned char *)bot->code->str, sizeof(int));
	if (mag_num == COREWAR_EXEC_MAGIC)
		return (0);
	return (1);
}

int 		validate_bot_size(t_bot *bot)
{
	int		size1;
	int 	size2;

	size1 = get_number_from_bcode((unsigned char *)bot->code->str + 4 + PROG_NAME_LENGTH + 4, sizeof(int));
	size2 = (int)bot->code->len - sizeof(int) - PROG_NAME_LENGTH - 4 - sizeof(int) - COMMENT_LENGTH - sizeof(int);
	if (size1 != size2)
	{
		ft_printf("{red}Error:{eoc} declared and actual size are not equal %d != %d\n", size1, size2);
		return (1);
	}
	if (size1 > CHAMP_MAX_SIZE)
	{
		ft_printf("{red}Error:{eoc} champ size is too big, max size = %d\n", CHAMP_MAX_SIZE);
		return (1);
	}
	bot->size = size1;
	return (0);
}

/*
** 0 - ok, 1 - error
*/
int 		validate_bots(t_data *data)
{
	t_linked_list	*curr;
	t_bot			*curr_bot;

	curr = data->bots;
	while (curr)
	{
		curr_bot = (t_bot *)curr->data;
		if (validate_magic_number(curr_bot))
			return (1);
		if (validate_bot_size(curr_bot))
			return (1);
		curr_bot->name = ft_strndup(curr_bot->code->str + sizeof(int), PROG_NAME_LENGTH);
		curr_bot->comment = ft_strndup(curr_bot->code->str + sizeof(int) + PROG_NAME_LENGTH + 4 + sizeof(int), COMMENT_LENGTH);
		curr = curr->next;
	}
	return (0);
}