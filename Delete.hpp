#pragma once

# include "dependences.hpp"
# include "Directory.hpp"
# include "Error.hpp"
# include "srv.hpp"

class Delete
{
    private:

    	int 						fd;
		std::string					url;
		std::string 				response;
		std::vector<std::string>	dir;
		srv							server;

    public:

		Delete(std::string & ur, int f, srv & serv);
		~Delete();

		int		DeleteResource();
		bool	DeleteFolder(std::string ur);
		bool	DeleteFile(std::string ur);
		void	sendResponseOk();

};