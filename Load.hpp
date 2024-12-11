#pragma once

# include "dependences.hpp"
# include "Request.hpp"
# include "Error.hpp"
# include "srv.hpp"

class Load
{
    private:

        Request   * rq;
		int			fd;
        std::string _url;
        srv         server;

        bool        finish;

    public:

        Load(Request * r, int f, std::string & url, srv & serv);

        ~Load();

        
        bool    createFile();
};