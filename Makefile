# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/04 17:42:13 by jmertane          #+#    #+#              #
#    Updated: 2024/06/18 07:28:03 by jmertane         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		:=	cub3d
ERRLOG		:=	error.txt
TESTMAP 	:=	maps/map.cub

ROOTDIR		:=	mandatory
OBJSDIR		:=	build
INCSDIR		:=	incs
SRCSDIR		:=	srcs
DEPSDIR		:=	.deps

LIBFTDIR	:=	libft
LIBFTBIN	:=	libft.a
LIBFT		:=	$(LIBFTDIR)/$(LIBFTBIN)

RM			:=	rm -rf
AR			:=	ar -rcs
SCREENCLR	:=	printf "\033c"

CC			:=	cc
CFLAGS		:=	-Wall -Werror -Wextra
OFLAGS		=	-Ofast
DBGFLAGS	=	-g #-fsanitize=address
DEPFLAGS	=	-c -MT $$@ -MMD -MP -MF $(DEPSDIR)/$$*.d

VLG			:=	valgrind
VLGLOG		:=	vglog.txt
VLGSUPP		:=	mlx.supp
VLGFLAGS	:=	--leak-check=full \
				--show-leak-kinds=all \
				--track-origins=yes \
				--track-fds=yes \
				--gen-suppressions=all \
				--suppressions=$(VLGSUPP) \
				--log-file=$(VLGLOG) \
				--verbose \
				--quiet

MLXDIR		:=	mlx
MLXBIN		:=	libmlx42.a
MLXBREW		=	-L "$(HOME)/.brew/opt/glfw/lib/"
MLXFLAGS	=	-ldl -lglfw -pthread -lm
LIBMLX		:=	$(MLXDIR)/$(OBJSDIR)/$(MLXBIN)

ifeq ($(shell uname), Darwin)
	MLXFLAGS += $(MLXBREW)
endif

F			=	=================================
B			=	\033[1m
T			=	\033[0m
G			=	\033[32m
V			=	\033[35m
C			=	\033[36m
R			=	\033[31m
Y			=	\033[33m

MODULES		:=	main \
				parse \
				thread \
				hook \
				draw \
				utils

SOURCES 	:= 	main.c \
				infile.c \
				element.c \
				mapinfo.c \
				checker.c \
				utils.c \
				thread.c \
				mutex.c \
				synchro.c \
				getset.c \
				move.c \
				rotate.c \
				action.c \
				mouse.c \
				walls.c \
				floor.c \
				minimap.c \
				animation.c \
				render.c \
				rays.c \
				color.c \
				pixel.c \
				error.c \
				free.c \
				load.c \
				safe.c \
				string.c \

SOURCEDIR	:=	$(addprefix $(SRCSDIR)/, $(MODULES))
BUILDDIR	:=	$(addprefix $(OBJSDIR)/, $(MODULES))
DEPENDDIR	:=	$(addprefix $(DEPSDIR)/, $(MODULES))

SRCS		:=	$(foreach source, $(SOURCES), $(shell find $(SOURCEDIR) -name $(source)))
OBJS		:=	$(patsubst $(SRCSDIR)/%.c, $(OBJSDIR)/%.o, $(SRCS))
DEPS		:=	$(patsubst $(SRCSDIR)/%.c, $(DEPSDIR)/%.d, $(SRCS))

INCS	 	:=	$(foreach header, $(INCSDIR), -I $(header))
INCS	 	+=	$(foreach header, $(LIBFTDIR)/$(INCSDIR), -I $(header))
INCS	 	+=	$(foreach header, $(MLXDIR)/include/MLX42, -I $(header))

vpath %.c $(SOURCEDIR)

define build_cmd
$1/%.o: %.c | $(BUILDDIR) $(DEPENDDIR)
	@if ! $(CC) $(CFLAGS) $(OFLAGS) $(INCS) $(DEPFLAGS) $$< -o $$@ 2> $(ERRLOG); then \
		printf "$(R)$(B)\nERROR!\n$(F)$(T)\n"; \
		printf "$(V)Unable to create object file:$(T)\n\n"; \
		printf "$(R)$(B)$$@$(T)\n"; \
		printf "$(Y)\n"; sed '$$d' $(ERRLOG); \
		printf "$(R)$(B)\n$(F)\nExiting...$(T)\n"; exit 1 ; \
	else \
		printf "$(C)$(B)☑$(T)$(V) $(CC) $(CFLAGS) $(OFLAGS) $$<$ \n   $(C)⮑  $(G)$(B)$$@$(T)\n"; \
	fi
endef

all: $(LIBMLX) $(LIBFT) $(NAME)

$(LIBMLX):
	@$(SCREENCLR)
ifeq ("$(wildcard $(MLXDIR))", "")
	@echo "$(G)$(B)$(MLXDIR)$(T)$(V) not found, commencing download.$(T)\n"
	@git clone https://github.com/codam-coding-college/MLX42.git $(MLXDIR)
else
	@echo "\n$(V)Skipping download, $(G)$(B)$(MLXDIR)$(T)$(V) exists.$(T)"
endif
	@echo "\n$(V)Building $(G)$(B)MLX42$(T)$(V) binary...$(T)\n"
	@cmake $(MLXDIR) -B $(MLXDIR)/build && make -C $(MLXDIR)/build -j4

$(LIBFT):
	@make --quiet -C $(LIBFTDIR) all
	@make --quiet title

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OFLAGS) $(INCS) $^ $(LIBFT) $(LIBMLX) $(MLXFLAGS) -o $@
	@make --quiet finish

re: fclean all

db: CFLAGS += $(DBGFLAGS)
db: re

vg: db
	@$(VLG) $(VLGFLAGS) ./$(NAME) $(TESTMAP)

run: all
	./$(NAME) $(TESTMAP)

clean:
	@make --quiet -C $(LIBFTDIR) clean
	@$(RM) $(OBJSDIR) $(DEPSDIR) $(ERRLOG)

fclean: clean
	@make --quiet -C $(LIBFTDIR) fclean
	@$(RM) $(MLXDIR)/$(OBJSDIR)
	@$(RM) $(NAME)

vclean: fclean
	@$(RM) $(VLGLOG)

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

.PHONY: all clean fclean vclean re db vg run nm title finish
