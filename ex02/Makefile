NAME		= PmergeMe
CC			= c++
CFLAGS		= -Wall -Wextra -Werror -std=c++17
DEBUGFLAGS	= -DDEBUG

SRC_FILES	= main.cpp PmergeMe.cpp PmergeMe_vec.cpp PmergeMe_deq.cpp
OBJ_FILES	= $(SRC_FILES:.cpp=.o)

all:		$(NAME)

$(NAME):	$(OBJ_FILES)
			$(CC) $(CFLAGS) -o $(NAME) $(OBJ_FILES)

%.o:		%.cpp
			$(CC) $(CFLAGS) -c $< -o $@

debug:  CFLAGS += $(DEBUGFLAGS)
debug:  clean $(NAME)  

clean:
			rm -f $(OBJ_FILES)

fclean:		clean
			rm -f $(NAME)

re:			fclean all

.PHONY:		all clean fclean re