.SILENT:

CC				=	cc
CFLAGS 			= -Wall -Wextra -Werror -I$(INC_DIR)
RM				=	rm -rf

SRC_DIR			= ./src
OBJ_DIR 		= ./obj
INC_DIR			= ./inc
BIN_DIR			= ./bin
LIB_DIR			= ./lib
NAME			=	${BIN_DIR}/philo
NAME_BONUS		=	${BIN_DIR}/philo_bonus


SRC			=		${SRC_DIR}/philo.c ${SRC_DIR}/philo_aux.c 								\
					${SRC_DIR}/parser/parser.c ${SRC_DIR}/parser/custom_atol.c 				\
					${SRC_DIR}/threads/error_handler.c ${SRC_DIR}/threads/threads_aux.c 	\
					${SRC_DIR}/threads/write_output.c ${SRC_DIR}/threads/write_aux.c		\
					${SRC_DIR}/mutex/error_handler.c ${SRC_DIR}/mutex/safe_accessors.c  	\
					${SRC_DIR}/philo/philo.c   												\
					${SRC_DIR}/table/table.c   												\



SRC_BONUS	=
OBJS 		= 		${patsubst ${SRC_DIR}/%.c, ${OBJ_DIR}/%.o, ${SRC}}
OBJS_BONUS	= 		${patsubst ${SRC_DIR}/%.c, ${OBJ_DIR}/%.o, ${SRC_BONUS}}

all:			$(NAME)



$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c
				printf "Compiling $(NAME) objects... %-33.33s\r" $(notdir $@)
				@mkdir -p $(dir $@)
				$(CC) $(CFLAGS) -c $< -o $@
				

$(BIN_DIR):
				@mkdir -p $(BIN_DIR)

bonus: 			$(NAME_BONUS)


$(NAME):		$(OBJS) | $(BIN_DIR)
				printf 'Compiling $(NAME)\n'
				$(CC) $(CFLAGS) $(OBJS) -o $@ 

$(NAME_BONUS):	$(OBJS_BONUS) | $(BIN_DIR)
				printf 'Compiling $(NAME_BONUS)\n'
				$(CC) $(CFLAGS) $(OBJS_BONUS) -o $@ 


clean:
				@if [ -d $(OBJ_DIR) ]; then $(RM) $(OBJ_DIR); fi
				@if [ -f $(NAME) ]; then $(RM) $(NAME); fi
				@if [ -f $(NAME_BONUS) ]; then $(RM) $(NAME_BONUS); fi

fclean:			clean
				$(RM) $(NAME)
				$(RM) $(NAME_BONUS)

re:				fclean all

debug:
	@echo "SRC: $(SRC)"
	@echo "OBJS: $(OBJS)"

.PHONY:			all clean fclean re
