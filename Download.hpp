#pragma once

# include "dependences.hpp"
# include "Directory.hpp"
# include "Request.hpp"
# include "Error.hpp"
class Error;
class Download
{
    private:

    	int 						fd;
		std::string					url;
		std::string 				response;
		std::vector<std::string>	dir;
		Request			        	*rq;
		srv 						_server;

    public:

		Download(Request * r, std::string & ur, int f, srv &server);
		~Download();

		void	sendForm();
		void	sendFile();

};