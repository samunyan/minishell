# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: samunyan <samunyan@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/04 13:28:03 by samunyan          #+#    #+#              #
#    Updated: 2022/04/04 13:28:06 by samunyan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#Logo
define HEADLOGO
  (        (       )     (      (        )             (     (     
 (  )     )\ )   ( /(   )\ )   )\ )     ( /(         )\ )   )\ )  
 )\))(   (()/(   )\()) (()/(  (()/(     )\())  (    (()/(  (()/(  
((_)()\   /(_)) ((_)\   /(_))  /(_))   ((_)\   )\   /(_))  /(_)) 
(_()((_) (_))   ( _((_) (_))   (_) )   ( _((_) ((_) (_))   (_))   
|  \/  | |_ _|  | \| | |_ _|  / __|    | || | | __| | |    | |    
| |\/| |  | |   |  ` |  | |   \__ \  _ | __ | | _|  | |__  | |__  
|_|  |_| |___|  |_|\_| |___|  |___/ (_)|_||_| |___| |____| |____|

endef
export HEADLOGO

# Executable
NAME			= minishell

#Libs
LIBFT_DIR		=	./libft
LIBFT			= 	libft.a
# Define brew if it's installed
BREW			:= $(shell brew -v 2> /dev/null)
# Define path to readline dir if brew is installed
ifdef BREW
	READLINE_DIR	:= $(shell brew --prefix readline)
endif
LIBS = ft readline
LIB_PATHS = $(LIBFT_DIR) $(READLINE_DIR)/lib

#Directories
OBJ_DIR			= 	./objs
SRC_DIR			=	./srcs
HEAD_DIRS		=	./include $(LIBFT_DIR)/include $(READLINE_DIR)/include

#Files
FILES			= 		lexer/lexer.c \
						lexer/lex_utils.c \
						lexer/lex_space.c \
						lexer/lex_redir.c \
						lexer/lex_quotes.c \
						lexer/lex_pipe.c \
						lexer/lex_null.c \
						lexer/lex_init.c \
						lexer/lex_char.c \
						parser/parser.c \
					 	parser/parse_arg.c \
						parser/parse_heredoc1.c \
						parser/parse_heredoc2.c \
						parser/parse_heredoc3.c \
						parser/parse_init.c \
						parser/parse_pipe.c \
						parser/parse_redir.c \
						parser/parse_redir_append.c \
						parser/parse_redir_input.c \
						parser/parse_redir_output.c \
						parser/parse_utils.c \
						signals/signals.c \
                        main.c \
                        expander/expander.c \
                        expander/expand_heredoc.c \
                        expander/heredoc_utils.c \
                        expander/heredoc_utils_2.c \
                        expander/heredoc_utils_3.c \
						executor/execute.c \
						utils/utils_envars_1.c \
						utils/utils_envars_2.c \
						utils/utils_envars_3.c \
						executor/utils_execute_1.c \
						executor/utils_execute_2.c \
						executor/execute_builtin.c \
						executor/execute_simple_command.c \
						executor/do_piped_command.c \
						executor/do_simple_command.c \
						executor/redirect_piped_command.c \
						executor/redirect_simple_command.c \
						executor/do_pipeline.c \
						utils/utils_cmd.c \
						utils/utils_token.c \
						builtins/msh_env.c \
						builtins/msh_exit.c \
						builtins/msh_cd.c \
						builtins/msh_echo.c \
						builtins/msh_export.c \
						builtins/msh_export_noarg.c \
						builtins/msh_unset.c \
						builtins/msh_export_arg.c \
                     	builtins/msh_pwd.c \
						utils/exitcode.c \
						utils/shlvl.c \
						utils/error.c \
						executor/redirect_in.c \
						executor/redirect_out.c \
						parser/parse_add_cmd.c
SRCS	= 	$(addprefix $(SRC_DIR)/, $(FILES))
OBJS	= 	$(addprefix $(OBJ_DIR)/, $(FILES:.c=.o))

#Compiler
SYSTEM		 := $(shell uname)
ifeq ($(SYSTEM),Linux)
CC			=	clang
else
CC			= 	gcc
endif
CFLAGS	=	-Wall -Werror -Wextra $(HEAD_DIRS:%=-I %)
LDFLAGS	=	$(foreach lib_path, $(LIB_PATHS), -L$(lib_path)) $(foreach lib, $(LIBS), -l$(lib))
ifeq ($(SANITIZER), 1)
		CFLAGS	+=	-g -fsanitize=address
		LDFLAGS	+=	-g -fsanitize=address
endif
ifeq ($(DEBUG), 1)
		CFLAGS	+=	-g
		LDFLAGS	+=	-g
endif

.PHONY:		all FORCE clean fclean re sanitizer debug

all:	    $(NAME)
		
$(NAME):	$(LIBFT) $(OBJS)
			@$(CC) $(CFLAGS) $(SRCS) $(LDFLAGS) -o $(NAME)
			@test -z '$(filter %.o,$?)' || (echo ✅ $(BBlue) [$(NAME)]"\t"$(BGreen)Compilation done. \
				Usage: ./$(NAME) && \
				echo $(White)"\t\t\t"Compiler flags: $(CFLAGS)$(Color_Off))

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c
			@mkdir -p $(dir $@)
			@echo ⌛ $(BBlue)[$(NAME)]"\t"$(Yellow)Compiling $<$(Color_Off)
			@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT): FORCE
			@make -C $(LIBFT_DIR)

FORCE:

clean:
			@if [ -d $(OBJ_DIR) ]; then \
  					rm -rf $(OBJ_DIR); \
  					echo 🗑$(BBlue)[$(NAME)]"\t"$(BGreen)Object files removed.$(Color_Off); \
  			fi
			@make -C $(LIBFT_DIR) clean

fclean:		clean
			@if [ -f $(NAME) ]; then \
					rm -rf $(NAME); \
					rm -rf *.dSYM; \
					echo 🗑$(BBlue)[$(NAME)]"\t"$(BGreen)Executable removed.$(Color_Off); \
			fi
			@make -C $(LIBFT_DIR) fclean

re:			fclean all

sanitizer:
			@SANITIZER=1 make re

debug:
			@DEBUG=1 make re

# Colors
## Reset
Color_Off='\033[0m'       # Text Reset
## Regular Colors
Black='\033[0;30m'        # Black
Red='\033[0;31m'          # Red
Green='\033[0;32m'        # Green
Yellow='\033[0;33m'       # Yellow
Blue='\033[0;34m'         # Blue
Purple='\033[0;35m'       # Purple
Cyan='\033[0;36m'         # Cyan
White='\033[0;37m'        # White
## Bold
BBlack='\033[1;30m'       # Black
BRed='\033[1;31m'         # Red
BGreen='\033[1;32m'       # Green
BYellow='\033[1;33m'      # Yellow
BBlue='\033[1;34m'        # Blue
BPurple='\033[1;35m'      # Purple
BCyan='\033[1;36m'        # Cyan
BWhite='\033[1;37m'       # White
## Underline
UBlack='\033[4;30m'       # Black
URed='\033[4;31m'         # Red
UGreen='\033[4;32m'       # Green
UYellow='\033[4;33m'      # Yellow
UBlue='\033[4;34m'        # Blue
UPurple='\033[4;35m'      # Purple
UCyan='\033[4;36m'        # Cyan
UWhite='\033[4;37m'       # White
## Background
On_Black='\033[40m'       # Black
On_Red='\033[41m'         # Red
On_Green='\033[42m'       # Green
On_Yellow='\033[43m'      # Yellow
On_Blue='\033[44m'        # Blue
On_Purple='\033[45m'      # Purple
On_Cyan='\033[46m'        # Cyan
On_White='\033[47m'       # White
## Bold High Intensity
BIBlack='\033[1;90m'      # Black
BIRed='\033[1;91m'        # Red
BIGreen='\033[1;92m'      # Green
BIYellow='\033[1;93m'     # Yellow
BIBlue='\033[1;94m'       # Blue
