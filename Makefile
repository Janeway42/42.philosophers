NAME = philo
CFLAGS	= -Wall -Werror -Wextra -g -fsanitize=address
LFLAGS	= -lpthread
UNAME = $(shell uname)

S_SRC	=	philo.c\
			init_data.c\
			threads.c\
			routine.c
S_PATH	=	src/
S_OBJ	=	$(S_SRC:%.c=$(S_PATH)%.o)

LIB		=	ft_atoi.c\
			ft_strlen.c
LIB_PATH	=	lib/
LIB_OBJ	=	$(LIB:%.c=$(LIB_PATH)%.o)

UTILS		=	write.c\
				sleep.c\
				death.c\
				error.c\
				free.c
UTILS_PATH	=	utils/
UTILS_OBJ	=	$(UTILS:%.c=$(UTILS_PATH)%.o)

OBJ_FILES = $(S_OBJ) $(LIB_OBJ) $(UTILS_OBJ)

INCLUDES_FLAG = -Iincludes


ifeq ($(UNAME), Linux)
	MORE_FLAGS = $(CFLAGS) $(LFLAGS)

else
	MORE_FLAGS = $(CFLAGS)

endif

all: $(NAME)

$(NAME): $(OBJ_FILES)
	$(CC) $(MORE_FLAGS) $(OBJ_FILES) $(INCLUDES_FLAG) -o $(NAME)

%.o: %.c $(HEADER_FILES)
	$(CC) $(MORE_FLAGS) $(INCLUDES_FLAG) -c $< -o $@ 

clean:
	$(RM) $(OBJ_FILES)

fclean: clean
	$(RM) $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all

.PHONY: all clean fclean re
