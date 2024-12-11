NAME = webserv
CPP = c++
CFLAGS = -Wall -Werror -Wextra -std=c++98 #-g3
SRC_FILES = main.cpp \
            Server.cpp \
            Request.cpp \
            Error.cpp \
            Utils.cpp \
            Config.cpp \
            srv.cpp \
            Location.cpp \
            Respons.cpp \
            Cgi.cpp \
            Load.cpp \
            Download.cpp \
            Directory.cpp \
            Dinamic.cpp \
            Delete.cpp \
            Autoindex.cpp \
            ErrorPage.cpp

OBJS = $(addprefix obj/, $(SRC_FILES:.cpp=.o))

CGI_SRC = cgi-bin/multi.cpp
CGI_OUT = cgi-bin/ia.out

BAD_CGI_SRC = cgi-bin/bad_multi.cpp
BAD_CGI_OUT = cgi-bin/bad_ia.out

all: $(NAME) $(CGI_OUT) $(BAD_CGI_OUT)

obj/%.o: %.cpp
	mkdir -p obj
	$(CPP) -c $(CFLAGS) $< -o $@

$(NAME): $(OBJS)
	$(CPP) $(CFLAGS) $(OBJS) -o $(NAME)

$(CGI_OUT): $(CGI_SRC)
	$(CPP) $(CFLAGS) $^ -o $@
    
$(BAD_CGI_OUT): $(BAD_CGI_SRC)
	$(CPP) $(CFLAGS) $^ -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME) $(CGI_OUT) $(BAD_CGI_OUT)
	rmdir obj

re: fclean all

.PHONY: all clean fclean re