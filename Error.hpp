#pragma once

# include "dependences.hpp"
# include "srv.hpp"
class srv;
class Error
{   

    public:

        Error(int er, int fdescriptor, srv &server);
        ~Error();

        static std::string	status(int error, srv &server);
		std::string 		toString(const int &num);
        void				sendError(srv &server, int error, int fd);
};