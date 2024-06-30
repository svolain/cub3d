# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/04 17:42:13 by jmertane          #+#    #+#              #
#    Updated: 2024/06/30 11:47:21 by jmertane         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#    VARIABLES
# **************************************************************************** #

NAME 		:=	cub3d
ERRORLOG	:=	error.txt
ROOTDIR 	:=	mandatory
FILETYPE	:=	.c
BONUSGOAL	:=	b
_b			:=

MAPSDIR		:=	maps
TESTMAP 	:=	map.cub

OBJSDIR		:=	build
INCSDIR		:=	incs
SRCSDIR		:=	srcs
DEPSDIR		:=	.deps

LIBFTDIR	:=	libft
LIBFTBIN	:=	libft.a
LIBFT		:=	$(LIBFTDIR)/$(LIBFTBIN)

# **************************************************************************** #
#    COMMANDS
# **************************************************************************** #

RM			:=	rm -rf
AR			:=	ar -rcs
SCREENCLR	:=	printf "\033c"

# **************************************************************************** #
#    COMPILATION
# **************************************************************************** #

CC			:=	cc
CFLAGS		:=	-Wall -Werror -Wextra -Ofast
DBGFLAGS	=	-g -fsanitize=address
DEPFLAGS	=	-c -MT $$@ -MMD -MP -MF $(DEPSDIR)/$$*.d

MLXDIR		:=	mlx
MLXBIN		:=	libmlx42.a
MLXBREW		=	-L "$(HOME)/.brew/opt/glfw/lib/"
MLXFLAGS	=	-ldl -lglfw -pthread -lm
LIBMLX		:=	$(MLXDIR)/$(OBJSDIR)/$(MLXBIN)

ifeq ($(shell uname), Darwin)
	MLXFLAGS += $(MLXBREW)
endif

# **************************************************************************** #
#    VALGRIND
# **************************************************************************** #

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

# **************************************************************************** #
#    SOURCES
# **************************************************************************** #

MODULES		:=	main \
				parser \
				hook \
				render \
				utils

SOURCES 	:= 	main \
				parse_infile \
				parse_element \
				parse_mapinfo \
				parse_checker \
				parse_utils \
				hook_move \
				hook_rotate \
				draw_walls \
				draw_calc_ray \
				draw_pixel_utils \
				free_exit \
				free_str \
				safe_mlx \
				safe_str \
				load_scene_asset \
				error_handler

BONUS_MODS	:=	thread \
				gameplay

BONUS_SRCS 	:= 	thread \
				mutex \
				getset_map \
				getset_cam \
				getset_plr \
				getset_frm \
				getset_stat \
				render_hud \
				render_world \
				hook_action \
				hook_mouse \
				draw_floor \
				draw_sprite \
				anim_weapon \
				anim_utils \
				draw_minimap \
				draw_fov \
				draw_hud_fx \
				draw_calc_wall \
				draw_calc_sprite \
				draw_color_utils \
				draw_map_utils \
				free_thread \
				free_asset \
				load_custom_asset \
				gameplay_player

# **************************************************************************** #
#    GOALS
# **************************************************************************** #

ifeq ($(MAKECMDGOALS), bonus)
	_b = $(BONUSGOAL)
else ifeq ($(MAKECMDGOALS), re$(BONUSGOAL))
	_b = $(BONUSGOAL)
else ifeq ($(MAKECMDGOALS), db$(BONUSGOAL))
	_b = $(BONUSGOAL)
else ifeq ($(MAKECMDGOALS), vg$(BONUSGOAL))
	_b = $(BONUSGOAL)
else ifeq ($(MAKECMDGOALS), rn$(BONUSGOAL))
	_b = $(BONUSGOAL)
else ifeq ($(MAKECMDGOALS), nm$(BONUSGOAL))
	_b = $(BONUSGOAL)
endif

ifeq ($(_b), $(BONUSGOAL))
	ROOTDIR := bonus
	FILETYPE := _bonus.c
	MODULES += $(BONUS_MODS)
	SOURCES += $(BONUS_SRCS)
endif

# **************************************************************************** #
#    TARGETS
# **************************************************************************** #

SOURCES		:=	$(addsuffix $(FILETYPE), $(SOURCES))
SOURCEDIR	:=	$(addprefix $(ROOTDIR)/$(SRCSDIR)/, $(MODULES))
BUILDDIR	:=	$(addprefix $(OBJSDIR)/, $(MODULES))
DEPENDDIR	:=	$(addprefix $(DEPSDIR)/, $(MODULES))

SRCS	:=	$(foreach source, $(SOURCES), $(shell find $(SOURCEDIR) -name $(source)))
OBJS	:=	$(patsubst $(ROOTDIR)/$(SRCSDIR)/%.c, $(OBJSDIR)/%.o, $(SRCS))
DEPS	:=	$(patsubst $(OBJSDIR)/%.o, $(DEPSDIR)/%.d, $(OBJS))

INCS	:=	$(foreach header, $(ROOTDIR)/$(INCSDIR), -I $(header))
INCS	+=	$(foreach header, $(LIBFTDIR)/$(INCSDIR), -I $(header))
INCS	+=	$(foreach header, $(MLXDIR)/include/MLX42, -I $(header))

vpath %.c $(SOURCEDIR)

# **************************************************************************** #
#    RULES
# **************************************************************************** #

all: $(NAME)

bonus: $(NAME)

re$(_b): fclean all

db$(_b): CFLAGS += $(DBGFLAGS)
db$(_b): re$(_b)

vg$(_b): db$(_b)
	@$(VLG) $(VLGFLAGS) ./$(NAME) $(MAPSDIR)/$(ROOTDIR)/$(TESTMAP)

rn$(_b): all
	./$(NAME) $(MAPSDIR)/$(ROOTDIR)/$(TESTMAP)

nm$(_b):
	@$(foreach header, $(ROOTDIR)/$(INCSDIR), norminette -R CheckDefine $(header))
	@$(foreach source, $(ROOTDIR)/$(SRCSDIR), norminette -R CheckForbiddenSourceHeader $(source))

# **************************************************************************** #
#    BUILD
# **************************************************************************** #

$(NAME): $(LIBMLX) $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) $(INCS) $^ $(LIBFT) $(LIBMLX) $(MLXFLAGS) -o $@
	@make --quiet finish

define build_cmd
$1/%.o: %.c | $(BUILDDIR) $(DEPENDDIR)
	@if ! $(CC) $(CFLAGS) $(INCS) $(DEPFLAGS) $$< -o $$@ 2> $(ERRORLOG); then \
		printf "$(R)$(B)\nERROR!\n$(F)$(T)\n"; \
		printf "$(V)Unable to create object file:$(T)\n\n"; \
		printf "$(R)$(B)$$@$(T)\n"; \
		printf "$(Y)\n"; sed '$$d' $(ERRORLOG); \
		printf "$(R)$(B)\n$(F)\nExiting...$(T)\n"; exit 1 ; \
	else \
		printf "$(C)$(B)☑$(T)$(V) $(CC) $(CFLAGS) $$<$ \n  $(C)⮑  $(G)$(B)$$@$(T)\n"; \
	fi
endef

# **************************************************************************** #
#    LIBRARIES
# **************************************************************************** #

$(LIBMLX):
	@$(SCREENCLR)
ifeq ("$(wildcard $(MLXDIR))", "")
	@printf "$(G)$(B)$(MLXDIR)$(T)$(V) not found, commencing download.$(T)\n"
	@git clone https://github.com/codam-coding-college/MLX42.git $(MLXDIR)
else
	@printf "$(V)Skipping download, $(G)$(B)$(MLXDIR)$(T)$(V) exists.$(T)\n"
endif
	@printf "$(V)Building $(G)$(B)MLX42$(T)$(V) binary...$(T)\n"
	@cmake $(MLXDIR) -B $(MLXDIR)/$(OBJSDIR) && make -C $(MLXDIR)/$(OBJSDIR) -j4

$(LIBFT):
	@make --quiet -C $(LIBFTDIR) all
	@make --quiet title

# **************************************************************************** #
#    CLEAN
# **************************************************************************** #

clean:
	@make --quiet -C $(LIBFTDIR) clean
	@$(RM) $(OBJSDIR) $(DEPSDIR) $(ERRLOG)

fclean: clean
	@make --quiet -C $(LIBFTDIR) fclean
	@$(RM) $(MLXDIR)/$(OBJSDIR)
	@$(RM) $(NAME)

vclean: fclean
	@$(RM) $(VLGLOG)

# **************************************************************************** #
#    TITLES
# **************************************************************************** #

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

# **************************************************************************** #
#    FORMAT
# **************************************************************************** #

F	=	=================================
B	=	\033[1m
T	=	\033[0m
G	=	\033[32m
V	=	\033[35m
C	=	\033[36m
R	=	\033[31m
Y	=	\033[33m

# **************************************************************************** #
#    UTILS
# **************************************************************************** #

$(BUILDDIR) $(DEPENDDIR):
	@mkdir -p $@

$(DEPS):
	include $(wildcard $(DEPS))

$(foreach build, $(BUILDDIR), $(eval $(call build_cmd, $(build))))

# **************************************************************************** #
#    PHONY
# **************************************************************************** #

.PHONY: all bonus
.PHONY: clean fclean vclean
.PHONY: title finish
.PHONY: re$(_b) db$(_b) vg$(_b) rn$(_b) nm$(_b)
