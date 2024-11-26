.SILENT:

CC				=	cc
CFLAGS 			= -Wall -Wextra -Werror -I$(INC_DIR) -I$(MLX_PATH) 
RM				=	rm -rf

SRC_DIR			= ./src
OBJ_DIR 		= ./obj
INC_DIR			= ./inc
BIN_DIR			= ./bin
LIB_DIR			= ./lib
NAME			=	${BIN_DIR}/philo
NAME_BONUS		=	${BIN_DIR}/philo_bonus


SRC			=		

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


$(NAME):		libs $(OBJS) | $(BIN_DIR)
				printf 'Compiling $(NAME)\n'
				$(CC) $(CFLAGS) $(OBJS) -o $@ 

$(NAME_BONUS):	libs $(OBJS_BONUS) | $(BIN_DIR)
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

.PHONY:			all clean fclean re
