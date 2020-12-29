NAME = pong
FLAGS = -Wall -Wextra -std=c++17
SRC = main.cpp Ball.cpp Bot.cpp Game.cpp GameObjects.cpp GamePlayController.cpp Player.cpp Window.cpp
OBJ_D = obj/
OBJ = $(addprefix $(OBJ_D), $(SRC:.cpp=.o))
INCLUDES	=	-I./frameworks/SDL2.framework/Versions/A/Headers \
				-I./frameworks/SDL2_ttf.framework/Versions/A/Headers \
				-I./frameworks/SDL2_image.framework/Versions/A/Headers \
				-I./frameworks/SDL2_mixer.framework/Headers \
				-I./frameworks/SDL2_net.framework/Headers \
				-F./frameworks
FRAMEWORKS	=	-F./frameworks \
				-rpath ./frameworks \
				-framework OpenGL -framework AppKit -framework OpenCl \
				-framework SDL2 -framework SDL2_ttf -framework SDL2_image \
				-framework SDL2_mixer -framework SDL2_net
all: $(NAME)

$(NAME): $(OBJ)
#	@clang++ $(OBJ) -o $(NAME) $(FRAMEWORKS)
	@G++ $(OBJ) -o $(NAME) $(FRAMEWORKS)

$(OBJ): | $(OBJ_D)

$(OBJ_D):
	@mkdir $(OBJ_D)

$(OBJ_D)%.o: %.cpp
#	@clang++ $(FLAGS) -o $@ -c $< $(INCLUDES)
	@G++ $(FLAGS) -o $@ -c $< $(INCLUDES)

clean:
#	@rm -f $(OBJ)
	@rm -rf $(OBJ_D)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re