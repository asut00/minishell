# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thelaine <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/02 12:33:11 by thelaine          #+#    #+#              #
#    Updated: 2024/07/11 16:31:07 by thelaine         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ---------------------------------- VARS ------------------------------------ #

NAME		=	minishell

SRC			=	minishell.c \
				ft_putchar_fd.c \
				ft_strcat.c \
				ft_calloc.c\
				ft_strchr.c\
				ft_strcmp.c\
				ft_strjoin.c\
				ft_strlcat.c\
				ft_substr.c\
				ft_strlcpy.c\
				ft_strlen.c\
				ft_itoa.c\
				ft_split.c \
				ft_putnbr_fd.c \
				ft_putstr_fd.c \
				ft_lstnew_env_var.c \
				ft_lstadd_front.c \
				ft_strdup_spe.c \
				ft_strisnumber.c \
				ft_atoi.c \
				ft_is.c \
				ft_atoll.c \
				ft_is_whitespace.c \
				exec_builtin.c \
				ft_cd.c \
				ft_echo.c \
				ft_pwd.c \
				ft_exit.c\
				exec.c\
				create_env_for_exec.c\
				garbage_management.c \
				memory_management.c\
				clear_all_and_exit.c\
				split_line_memory.c\
				readline_memory.c\
				var_management.c \
				ft_export.c \
				ft_export_one.c\
				ft_env_export.c\
				ft_unset.c \
				lexing.c \
				expand.c \
				add_expanded.c \
				command_list_manipulator.c\
				parsing.c\
				check_command_error_1.c\
				check_command_error_2.c\
				heredoc.c \
				check_quotes.c\
				pre_expand.c\
				init_cmd_array.c \
				pipex_init.c \
				pipex_exec.c \
				pipex_exec_inits_and_wait.c \
				pipex_open_and_dup_fds.c \
				pipex_exec_get_filefds.c \
				handle_path.c\
				pipex_exec_get_cmdpath.c \
				pipex_exec_handle_errors.c \
				pipex_exec_close.c \
				signal_handlers.c \
				signal_handlers_2.c

VPATH       =   src src/libft_spe src/builtins src/exec src/garbage_collector \
				src/var_management src/parsing src/pipex_init \
				src/pipex src/signal \

INCL_DIR    =   inc/

OBJECTS     =   $(SRC:%.c=$(OBJ_DIR)/%.o)

OBJ_DIR     =   build

CC          =   cc

RDL_INC		=	-I /opt/homebrew/opt/readline/include

RDL_LIB		=	-L /opt/homebrew/opt/readline/lib

CFLAGS      =   -Wall -Wextra -Werror -g3 -I $(INCL_DIR) $(RDL_INC)

LDFLAGS     =   -L /usr/local/lib $(RDL_LIB)

LIBS        =   -lreadline

# ---------------------------------- RULES ----------------------------------- #

.c.o:
				$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

$(NAME):    $(OBJ_DIR) $(OBJECTS)
				$(CC) $(CFLAGS) $(LDFLAGS) $(LIBS) -o $(NAME) $(OBJECTS)

$(OBJ_DIR):
				mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o:     %.c
				$(CC) $(CFLAGS) -c $< -o $@

all:        $(NAME)

clean:
				rm -f $(OBJECTS)
				rm -f -r $(OBJ_DIR)

fclean:     clean
				rm -f $(NAME)

re:         fclean all

htest:
	valgrind -q --leak-check=full --show-leak-kinds=all --trace-children=yes --track-fds=yes ./minishell

test: re clean
	valgrind -q --trace-children=yes --track-fds=yes ./minishell

.PHONY:     all clean fclean re htest test
