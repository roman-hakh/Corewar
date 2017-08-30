#include "vm.h"

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
	ft_printf("\n");
}

/*
** 0 - ok, 1 - error
*/
//int 		 infinit_loop(t_data *data)
//{
//	int		pause;
//
//	while (data->cycles_to_die > 0 && data->processes > 0)
//	{
//		timeout(data->ncurses_timeout);
//		pause = getch();
//		if (pause == 'a' || pause == 's')
//			ncurses_speed(data, pause);
//		if (data->one_command_mode)
//			pause = ncurses_one_cm_mode(data, pause);
//		while (pause == ' ')
//			pause = ncurses_global_cycle(data, pause);
//		pause == 'n' ? data->one_command_mode = 1 : 0;
//		if ((!data->pause || data->one_command_mode) && execute_commands(data))
//				return (1);
//		display_stats(data, data->stats_win);
//		wrefresh(data->memory_win);
//		refresh();
//	}
//	return (0);
//}

int 		 infinit_loop(t_data *data)
{
	int		pause;
	int 	next_command;

	next_command = data->pause_time - 1;
	while (data->cycles_to_die > 0 && data->processes > 0)
	{
		timeout(data->ncurses_timeout);
		pause = getch();
		if (pause == 'a' || pause == 's')
			ncurses_speed(data, pause);
		if (data->one_command_mode)
			pause = ncurses_one_cm_mode(data, pause);
		while (pause == ' ')
			pause = ncurses_global_cycle(data, pause);
		pause == 'n' ? data->one_command_mode = 1 : 0;


		if ((!data->pause || data->one_command_mode))
		{

			if (data->cycles == data->next_cycles_check)
			{
				check_for_live_bots(data);
				data->next_cycles_check = data->cycles + data->cycles_to_die;
				data->max_checks++;
				if (data->max_checks > 0 && (data->max_checks % MAX_CHECKS == 0))
				{
					if (data->last_cycles_to_die == data->cycles_to_die)
					{
						data->cycles_to_die -= CYCLE_DELTA;
						data->next_cycles_check = data->cycles + data->cycles_to_die;
					}
					data->last_cycles_to_die = data->cycles_to_die;
				}
			}

			if (next_command <= 0)
			{
				if (execute_commands(data))
					return (1);
				next_command = data->pause_time;
			}



			next_command--;
			data->cycles++;

		}

		display_stats(data, data->stats_win);
		wrefresh(data->memory_win);
		refresh();
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

	i = 1;
	ret = 0;
	while (i < (MAX_PLAYERS + 1) && i < (num + 1))
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
		bot->last_live = 0;
		bot->is_dead = 0;
		bot->prev_attr = -1;
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
	int 			r1_number = 1;

	i = 0;
	bot_number = 1;
	period = MEM_SIZE / data->bots_count;
	curr = data->bots;
	while (curr)
	{
		curr_bot = curr->data;
		curr_bot->reg[1] = r1_number;
		curr_bot->number = bot_number;
		curr_bot->pc = i;
		curr_bot->start = i;
		ft_memcpy(data->map + i, curr_bot->code->str + 4 + PROG_NAME_LENGTH + 4	 + 4 + COMMENT_LENGTH + 4, (size_t )curr_bot->size);
		i += period;
		curr = curr->next;
		r1_number++;
		bot_number++;
	}
}

int         main(int argc, char **argv)
{
	t_data	data;

	ft_bzero(&data, sizeof(t_data));
	data.cycles_to_die = CYCLE_TO_DIE;
	data.next_cycles_check = CYCLE_TO_DIE;
	data.cycles = 0;
	////done//todo:palanich process arguments and return ordered array of bots names
	//todo:hakh
	if (argc == 1)
		usage();
	if (parse_flags(&data, argc, argv))
		return (1);
	data.processes = (size_t)data.bots_count;
	ft_printf("%d\n", data.bots_count);
	if (init_bots(&data, data.players, data.bots_count))
		return (1);
	load_bots_in_memory(&data);
	nc_display_arena(&data);
	first_pause(&data);
	if (infinit_loop(&data))
		return (1);
	nc_terminate(&data);
	//print_memory(&data);
	//todo: calculate winner
	//todo:hakh free bots code (t_string)
}
