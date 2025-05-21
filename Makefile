NAME = philo
CFLAGS = -Wall -Werror -Wextra -g -pthread

MAINFILES		=	init			main			quit
ROUTINEFILES	=	grim_routine	philo_routine	philo_routine_methods
PARSERFILES		=	parser
UTILSFILES		=	printmessages

MAINFILES_FULL     = $(addprefix SRCS/MAIN/, $(addsuffix .c, $(MAINFILES)))
ROUTINEFILES_FULL  = $(addprefix SRCS/ROUTINE/, $(addsuffix .c, $(ROUTINEFILES)))
PARSERFILES_FULL   = $(addprefix SRCS/PARSER/, $(addsuffix .c, $(PARSERFILES)))
UTILSFILES_FULL    = $(addprefix SRCS/UTILS/, $(addsuffix .c, $(UTILSFILES)))

CFILES = $(MAINFILES_FULL) $(ROUTINEFILES_FULL) $(PARSERFILES_FULL) $(UTILSFILES_FULL)
OFILES = $(CFILES:.c=.o)

all: $(NAME)

$(NAME): $(OFILES)
	@cc $(CFLAGS) $(OFILES) -o $(NAME)
	@printf "\033[34m          Compiled $(NAME) successfully!\033[0m\n\n"

%.o: %.c
	@printf "\r\033[K\033[34mCompiling: $<\033[0m"
	@cc $(CFLAGS) -I INCLUDES -c $< -o $@
	@printf "\r\033[K"

clean:
	@rm -f $(OFILES)
	@echo "    \033[32m$(NAME) object files cleaned\n\033[0m"

fclean: clean
	@rm -f $(NAME)
	@echo "    \033[32m$(NAME) cleaned.\n\033[0m"

re: fclean
	@$(MAKE) -s all

norm:
	@norminette | grep -E --color=always "Error" || echo "\e[32mNorminette is fine!\e[0m"
