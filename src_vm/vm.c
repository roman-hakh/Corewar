#include "vm.h"

/*
** 0 - ok , 1 - error
*/
int 		listen_keybord(t_data *data)
{
	//todo sbondar
	//if space was pressed then data->pause must be stalled in 1
	//if space was pressed again then data->pause = 0
	//if right-arrow was pressed then data->one_command_mode = 1
	// Do this implement this function using sockets,
	// fork process at the start and then send from child to parent code of
	// pressed button
	return (0);
}

/*
** 0 - ok, 1 - error
*/
int 		 infinit_loop(t_data *data)
{
	//todo:hakh execute bots commands
	//todo:bondar synchronized output using ncurses

	while (1)
	{
		if (listen_keybord(data))
			return (1);
		if (!data->pause || data->one_command_mode)
		{
			if (execute_commands(data))
				return (1);
			//todo calculate cycles and winner
			data->one_command_mode = 0;
		}
		break; //delete this
	}
	return (0);
}

/*
** 0 - ok, 1 - error
*/
int 		init_bots(t_data *data, char *argv[MAX_PLAYERS + 1], int num)
{
	//todo:hakh write bots code to t_string, validate it, load into map
	int 		i;
	int 		ret;
	t_string	*curr;
	t_bot		*bot;

	i = 0;
	ret = 0;
	while (i < MAX_PLAYERS && i < num)
	{
		curr = string_new(30);
		(read_bot(curr, argv[i])) ? (ret = 1) : 0;
		(bot = bot_new(i + 1, curr)) ? 0 : (ret = 1);
		if (ret)
		{
			list_del(&(data->bots), bot_del);
			string_del(&curr);
			return (1);
		}
		list_push_back(&(data->bots), bot);
		i++;
	}
	if (validate_bots(data))
	{
		list_del(&(data->bots), bot_del);
		return (1);
	}
	return (0);
}

void		load_bots_in_memory(t_data *data)
{
	t_linked_list	*curr;
	t_bot			*curr_bot;
	int 			period;
	int 			i;
	int 			bot_number;
	int 			curr_number = 2147483647;

	i = 0;
	bot_number = 0;
	period = MEM_SIZE / data->bots_count;
	curr = data->bots;
	while (curr)
	{
		curr_bot = curr->data;
		curr_bot->reg[1] = curr_number;
		curr_bot->number = bot_number;
		ft_memcpy(data->map + i, curr_bot->code->str + 4 + PROG_NAME_LENGTH + 4 + 4 + COMMENT_LENGTH + 4, (size_t )curr_bot->size);
		i += period;
		curr = curr->next;
		curr_number--;
		bot_number++;
	}
}

void		print_memory(t_data *data)
{
	int 	i;

		i = 0;
		ft_printf("{yellow}Memory dump:\n{eoc}");
		while (i < MEM_SIZE)
		{
			if (i % 64 == 0)
				ft_printf("\n");
			if (data->map[i] == 0)
				ft_printf("%0.2hhx ", data->map[i]);
			else
				ft_printf("{green}%0.2hhx {eoc}", data->map[i]);
			i++;
		}
}

int         main(int argc, char **argv)
{
	t_data	data;

	ft_bzero(&data, sizeof(t_data));
	//todo:palanich process arguments and return ordered array of bots names
	//todo:hakh
//	argv[0] = "../champs/jumper.cor";
	//argv[0] = "../test_comment.ror";
	//argv[0] = "../test_sti.cor";// argv[0] = "../champs/Survivor.cor";
	argv[0] = "../champs/Car.cor";
	// argv[0] = "../champs/toto.cor";
	// argv[0] = "../test_comment.ror";
	if (argc == 1)
	usage();
	parse_flags(&data, argc, argv);if (init_bots(&data, data.players, data.bots_count))
		return (1);
	load_bots_in_memory(&data);
	ft_display_arena(&data);
	if (infinit_loop(&data)){
		return (1);
	}
	// print_memory(&data);
	//todo: calculate winner
	//todo:hakh free bots code (t_string)
}
