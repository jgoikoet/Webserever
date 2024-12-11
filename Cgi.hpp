
#pragma once

# include "dependences.hpp"
# include "Error.hpp"
# include "Request.hpp"
# include "srv.hpp"

class srv;

class Cgi
{
    private:

    	Request                        *rq;
        std::string                 url;
		std::vector<std::string>    envVect;


        std::string result;

        char        **_env;
		int			fd;
        srv                         server;

        int         inFd;
        int         outFd;
        int         inPipe[2];
        int         outPipe[2];
		

    public:

        Cgi(Request *r, std::string  ur, int f, srv & serv);
        ~Cgi();

        void 		createGetEnv();
        void 		createPostEnv();
        void        setPost();
        void 		exec();
        

		void		sendResult();

};