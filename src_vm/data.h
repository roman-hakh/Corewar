/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtelega <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 20:07:47 by dtelega           #+#    #+#             */
/*   Updated: 2017/09/13 20:11:45 by dtelega          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H

# include "op.h"
# include <ncurses.h>
# include "../new_libft/srcs/libft.h"

typedef struct		s_bot
{
	char			*name;
	char			*comment;
	int				size;
	int				r1_number;
	int				number;
	int				reg[REG_NUMBER + 1];
	int				carry;
	int				pc;
	int				start;
	int				pause_time;
	t_string		*code;
	int				prev_live;
	int				prev_st;
	int				is_dead;
	int				live_count;
	int				last_live;
	int				throw_live;
	chtype			prev_attr;
	char			command;
	char			opcode;
	int				args[3];
}					t_bot;

/*
** c_to_die means cycles to die
** bot_score[bot_number] <- here will be stored bot's score bu its number
*/

typedef struct		s_data
{
	unsigned char	map[MEM_SIZE];
	int				bots_last_live[MAX_PLAYERS + 1];
	int				bots_live[MAX_PLAYERS + 1];
	char			bots_names[MAX_PLAYERS + 1][PROG_NAME_LENGTH + 1];
	char			debug_strs[12][62];
	int				debug_level;
	int				mute;
	int				cycles_to_die;
	int				next_cycles_check;
	int				max_checks;
	int				last_max_checks;
	int				processes[MAX_PLAYERS + 1];
	int				last_cycles_to_die;
	int				cycles;
	t_linked_list	*bots;
	t_linked_list	*bots_tail;
	int				bots_count;
	int				one_command_mode;
	int				pause;
	int				dump;
	char			*players[MAX_PLAYERS + 1];
	char			visual;
	int				pause_time;
	WINDOW			*memory_win;
	WINDOW			*stats_win;
	WINDOW			*debug_win;
	int				ncurses_timeout;
}					t_data;

typedef struct		s_op
{
	char			*name;
	int				n_arg;
	char			type_arg[3];
	char			command_number;
	int				cycles_to_done;
	char			*description;
	char			have_opcode;
	char			dir_as_label;
}					t_op;

extern t_op			g_tab[17];

#endif
