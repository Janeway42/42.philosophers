NAME = philo
CFLAGS	= -Wall -Werror -Wextra -g #-fsanitize=thread  #-fsanitize=address 
LFLAGS	= -pthread
UNAME = $(shell uname)

S_SRC	=	philo.c\
			init_data.c\
			threads.c\
			routine.c\
			routine_utils.c\
			surveilance.c
S_PATH	=	./src/
S_OBJ	=	$(S_SRC:%.c=$(S_PATH)%.o)

BASICS		=	ft_atoi.c\
				ft_itoa.c\
				ft_isdigit.c\
				ft_strncmp.c\
				ft_strlen.c
BASICS_PATH	=	./basics/
BASICS_OBJ	=	$(BASICS:%.c=$(BASICS_PATH)%.o)

UTILS		=	write.c\
				sleep.c\
				error.c\
				free.c
UTILS_PATH	=	./utils/
UTILS_OBJ	=	$(UTILS:%.c=$(UTILS_PATH)%.o)

OBJ_FILES = $(S_OBJ) $(BASICS_OBJ) $(UTILS_OBJ)

INCLUDES_FLAG = -Iincludes


ifeq ($(UNAME), Linux)
	MORE_FLAGS = $(CFLAGS) $(LFLAGS) 

else
	MORE_FLAGS = $(CFLAGS)

endif

all: $(NAME)

$(NAME): $(OBJ_FILES)
	@$(CC) $(MORE_FLAGS) $(OBJ_FILES) $(INCLUDES_FLAG) -o $(NAME)
	@echo "\033[0;31mphilo ready\033[0m"

%.o: %.c $(HEADER_FILES)
	@$(CC) $(MORE_FLAGS) $(INCLUDES_FLAG) -c $< -o $@ 

clean:
	@$(RM) $(OBJ_FILES)
	@echo "\033[0;31mclean completed\033[0m"

fclean: clean
	@$(RM) $(NAME)
	@echo "\033[0;31mfclean completed\033[0m"

re:
	@$(MAKE) fclean
	@$(MAKE) all

.PHONY: all clean fclean re
