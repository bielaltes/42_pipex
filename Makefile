CC=gcc
NAME=pipex
CFLAGS=-Wall -Wextra -Werror
LIB_DIR=libft/
LIB=libft.a
INC = pipex.h

SRC =	SRC/pipex.c		

SRC_BNS =

OBJ=$(SRC:.c=.o)

OBJ_BNS=$(SRC_BNS:.c=.o)

all: $(NAME)

$(LIB):	
	@$(MAKE) -C $(LIB_DIR)
	/bin/mv $(LIB_DIR)$(LIB) .
	/bin/cp $(LIB_DIR)libft.h .

$(NAME): $(OBJ) $(LIB) 
	@echo "Compilant $@"
	@$(CC) $(CFLAGS) $(OBJ) -I $(INC) $< -o $(NAME)

clean:
	rm -f $(OBJ) $(OBJ_BNS)

fclean: clean
	rm -f $(NAME)

re: fclean all	

.PHONY: clean fclean all re bonus