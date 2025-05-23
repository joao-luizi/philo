

CC				=	cc
CFLAGS 			= -Wall -Wextra -Werror -g  -I$(INC_DIR)
CFLAGS_BO 		= -Wall -Wextra -Werror -g  -I$(INC_DIR_BO)
RM				=	rm -rf

SRC_DIR			= ./philo
SRC_DIR_BO		= ./philo_bonus
OBJ_DIR 		= ./obj
OBJ_DIR_BO 		= ./obj_bo
INC_DIR			= ./philo/inc
INC_DIR_BO		= ./philo_bonus/inc
BIN_DIR			= ./bin
NAME			=	${BIN_DIR}/philo
NAME_BONUS		=	${BIN_DIR}/philo_bonus


SRC			=		${SRC_DIR}/philo.c ${SRC_DIR}/philo_aux.c ${SRC_DIR}/philo_mem.c 				\
					${SRC_DIR}/parser/parser.c ${SRC_DIR}/parser/custom_atol.c 						\
					${SRC_DIR}/philo_monitor.c ${SRC_DIR}/philo_life.c ${SRC_DIR}/philo_states.c	\
					${SRC_DIR}/table.c ${SRC_DIR}/mutex_helpers.c	 								\

SRC_BONUS	=		${SRC_DIR_BO}/philo.c ${SRC_DIR_BO}/philo_aux.c ${SRC_DIR_BO}/philo_mem.c 		\
					${SRC_DIR_BO}/parser/parser.c ${SRC_DIR_BO}/parser/custom_atol.c 				\
					${SRC_DIR_BO}/philo_monitor.c ${SRC_DIR_BO}/philo_life.c ${SRC_DIR_BO}/philo_states.c	\
					${SRC_DIR_BO}/table.c ${SRC_DIR_BO}/mutex_helpers.c	 								\

OBJS 		= 		${patsubst ${SRC_DIR}/%.c, ${OBJ_DIR}/%.o, ${SRC}}
OBJS_BONUS	= 		${patsubst ${SRC_DIR_BO}/%.c, ${OBJ_DIR_BO}/%.o, ${SRC_BONUS}}

all:			$(NAME)

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c
				@mkdir -p $(dir $@)
				$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR_BO)/%.o:	$(SRC_DIR_BO)/%.c
				@mkdir -p $(dir $@)
				$(CC) $(CFLAGS_BO) -c $< -o $@
				

$(BIN_DIR):
				@mkdir -p $(BIN_DIR)

bonus: 			$(NAME_BONUS)


$(NAME):		$(OBJS) | $(BIN_DIR)
				$(CC) $(CFLAGS) $(OBJS) -o $@ 

$(NAME_BONUS):	$(OBJS_BONUS) | $(BIN_DIR)
				$(CC) $(CFLAGS_BO) $(OBJS_BONUS) -o $@ 


clean:
	@$(RM) $(OBJ_DIR) $(OBJ_DIR_BO)
	@$(RM) $(NAME) $(NAME_BONUS)

fclean: clean
	@$(RM) $(BIN_DIR)

re:				fclean all


.PHONY:			all clean fclean re
