#===========================VARIABLE===============================#
SRCS			:=	main.c\
					fork.c\
					philo_on_table.c\
					routines.c\
					print_output.c\
					check_state.c\
					utils/ft_atoi.c\
					utils/ft_strncmp.c\
					utils/get_time_in_ms.c\

SRCS_D			:=	srcs/

OBJS_D			:=	objs/

OBJS			:=	$(SRCS:%.c=$(OBJS_D)%.o)

HEAD			:=	philosopher.h

HEAD_D			:=	incs/

HEAD_A			:=	$(addprefix $(HEAD_D), $(HEAD))

NAME			:=	philo

#=========================FLAG===============================#
CC				:=	cc

RM				:=	rm -rf

CFLAGS			:=	-Wall -Wextra -Werror

PTHREAD			:=	-pthread

ASAN_F			:=	-g3 -fsanitize=address

#========================EXEC===============================#
all				:	$(NAME)

$(NAME)			:	$(OBJS_D) $(OBJS)
				$(CC) $(CFLAGS) $(PTHREAD) $(ASAN_F) -o $(NAME) $(OBJS)

$(OBJS)			:	$(OBJS_D)%.o: $(SRCS_D)%.c $(HEAD_A)
				$(CC) $(CFLAGS) $(ASAN_F) -I$(HEAD_D) -c $< -o $@

$(OBJS_D)		:
				mkdir -p $(OBJS_D)
				mkdir -p $(OBJS_D)/utils

leaks			:	all
				echo "{" > valgrind_ignore_leaks.txt
				echo "leak readline" >> valgrind_ignore_leaks.txt
				echo "    Memcheck:Leak" >> valgrind_ignore_leaks.txt
				echo "    ..." >> valgrind_ignore_leaks.txt
				echo "    fun:readline" >> valgrind_ignore_leaks.txt
				echo "}" >> valgrind_ignore_leaks.txt
				echo "{" >> valgrind_ignore_leaks.txt
				echo "    leak add_history" >> valgrind_ignore_leaks.txt
				echo "    Memcheck:Leak" >> valgrind_ignore_leaks.txt
				echo "    ..." >> valgrind_ignore_leaks.txt
				echo "    fun:add_history" >> valgrind_ignore_leaks.txt
				echo "}" >> valgrind_ignore_leaks.txt
				valgrind --suppressions=valgrind_ignore_leaks.txt --leak-check=full \
					--show-leak-kinds=all --track-fds=yes \
					--show-mismatched-frees=yes --read-var-info=yes \
					-s ./${NAME}
					#--log-file=valgrind.txt \

FORCE			:

clean			:
				$(RM) $(OBJS) $(OBJS_D) $(OBJSB_D)

fclean			:	clean
				$(RM) $(NAME) $(BONUS)

re				:	fclean all

.PHONY			:	all clean fclean re FORCE
