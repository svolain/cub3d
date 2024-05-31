# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/04 17:42:13 by jmertane          #+#    #+#              #
#    Updated: 2024/05/27 19:16:02 by jmertane         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		:=	cub3d
ERRTXT		:=	error.txt
OBJSDIR		:=	build
INCSDIR		:=	incs
SRCSDIR		:=	srcs
DEPSDIR		:=	.deps
LIBFTDIR	:=	libft
LIBFTBIN	:=	$(LIBFTDIR)/libft.a

RM			:=	rm -rf
AR			:=	ar -rcs
CC			:=	cc
CFLAGS		:=	-Wall -Werror -Wextra
DEBUGFLAGS	=	-g -fsanitize=address
DEPFLAGS	=	-c -MT $$@ -MMD -MP -MF $(DEPSDIR)/$$*.d
SCREENCLR	:=	printf "\033c"
SLEEP		:=	sleep .1

MLXDIR		:=	mlx
MLXLIB		:=	$(MLXDIR)/$(OBJSDIR)/libmlx42.a
MLXBREW		=	-L "$(HOME)/.brew/opt/glfw/lib/"
MLXFLAGS	=	-ldl -lglfw -pthread -lm

ifeq ($(shell uname), Darwin)
	MLXFLAGS += $(MLXBREW)
endif

MODULES		:=	main \
				parse \
				hook \
				draw \
				utils

SOURCES 	:= 	main.c \
				infile.c \
				element.c \
				mapinfo.c \
				checker.c \
				action.c \
				mouse.c \
				move.c \
				loop.c \
				rays.c \
				walls.c \
				minimap.c \
				pixel.c \
				rotate.c \
				error.c \
				free.c \
				load.c \
				safe.c \
				utils.c

SOURCEDIR	:=	$(addprefix $(SRCSDIR)/, $(MODULES))
BUILDDIR	:=	$(addprefix $(OBJSDIR)/, $(MODULES))
DEPENDDIR	:=	$(addprefix $(DEPSDIR)/, $(MODULES))
SRCS		:=	$(foreach file, $(SOURCES), $(shell find $(SOURCEDIR) -name $(file)))
OBJS		:=	$(patsubst $(SRCSDIR)/%.c, $(OBJSDIR)/%.o, $(SRCS))
DEPS		:=	$(patsubst $(SRCSDIR)/%.c, $(DEPSDIR)/%.d, $(SRCS))
INCS	 	:=	$(foreach header, $(INCSDIR), -I $(header))
INCS	 	+=	$(foreach header, $(LIBFTDIR)/$(INCSDIR), -I $(header))
INCS	 	+=	$(foreach header, $(MLXDIR)/include/MLX42, -I $(header))

F			=	=================================
B			=	\033[1m
T			=	\033[0m
G			=	\033[32m
V			=	\033[35m
C			=	\033[36m
R			=	\033[31m
Y			=	\033[33m

vpath %.c $(SOURCEDIR)

define build_cmd
$1/%.o: %.c | $(BUILDDIR) $(DEPENDDIR)
	@if ! $(CC) $(CFLAGS) $(INCS) $(DEPFLAGS) $$< -o $$@ 2> $(ERRTXT); then \
		printf "$(R)$(B)\nERROR!\n$(F)$(T)\n"; \
		printf "$(V)Unable to create object file:$(T)\n\n"; \
		printf "$(R)$(B)$$@$(T)\n"; \
		printf "$(Y)\n"; sed '$$d' $(ERRTXT); \
		printf "$(R)$(B)\n$(F)\nExiting...$(T)\n"; exit 1 ; \
	else \
		printf "$(C)$(B)☑$(T)$(V) $(CC) $(CFLAGS) $$<$ \n    $(C)⮑\t$(G)$(B)$$@$(T) \t\n"; \
	fi
endef

all: $(MLXLIB) $(LIBFTBIN) $(NAME)

$(MLXLIB):
	@$(SCREENCLR)
ifeq ("$(wildcard $(MLXDIR))", "")
	@echo "$(G)$(B)$(MLXDIR)$(T)$(V) not found, commencing download.$(T)\n"
	@git clone https://github.com/codam-coding-college/MLX42.git $(MLXDIR)
else
	@echo "\n$(V)Skipping download, $(G)$(B)$(MLXDIR)$(T)$(V) exists.$(T)"
endif
	@echo "\n$(V)Building $(G)$(B)MLX42$(T)$(V) binary...$(T)\n"
	@cmake $(MLXDIR) -B $(MLXDIR)/build && make -C $(MLXDIR)/build -j4

$(LIBFTBIN):
	@make --quiet -C $(LIBFTDIR) all
	@make title

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(INCS) $^ $(LIBFTBIN) $(MLXLIB) $(MLXFLAGS) -o $@
	@make finish

db: CFLAGS += $(DEBUGFLAGS)
db: re

clean:
	@make --quiet -C $(LIBFTDIR) clean
	@$(RM) $(OBJSDIR) $(DEPSDIR) $(ERRTXT)

fclean: clean
	@make --quiet -C $(LIBFTDIR) fclean
	@$(RM) $(MLXDIR)/$(OBJSDIR)
	@$(RM) $(NAME)

re: fclean all

nm:
	@$(foreach header, $(INCSDIR), norminette -R CheckDefine $(header))
	@$(foreach source, $(SRCSDIR), norminette -R CheckForbiddenSourceHeader $(source))

title:
	@$(SCREENCLR) && printf "\n"
	@printf "$(C)╔═╗╦ ╦╔╗ ╔═╗╔╦╗$(T)\n"
	@printf "$(C)║  ║ ║╠╩╗║╣  ║║  by svolain$(T)\n"
	@printf "$(C)╚═╝╚═╝╚═╝╚═╝═╩╝   & jmertane$(T)\n"
	@printf "$(G)$(B)$(F)\n$(T)\n"

finish:
	@printf "\n$(G)$(B)$(F)$(T)\n"
	@printf "$(C)╔═╗╦╔╗╔╦╔═╗╦ ╦╔═╗╔╦╗        $(V)$(B)$(NAME)$(T)\n"
	@printf "$(C)╠╣ ║║║║║╚═╗╠═╣║╣  ║║$(T)\n"
	@printf "$(C)╚  ╩╝╚╝╩╚═╝╩ ╩╚═╝═╩╝$(T)\n\n"

$(BUILDDIR) $(DEPENDDIR):
	@mkdir -p $@

$(DEPS):
	include $(wildcard $(DEPS))

$(foreach build, $(BUILDDIR), $(eval $(call build_cmd, $(build))))

.PHONY: all clean fclean re db nm title finish
