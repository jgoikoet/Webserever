
#pragma once

# include "dependences.hpp"
# include "Request.hpp"
# include "Utils.hpp"
# include "srv.hpp"
# include "Cgi.hpp"
# include "Load.hpp"
# include "Download.hpp"
# include "Delete.hpp"
# include "Error.hpp"
# include "Dinamic.hpp"
# include "Autoindex.hpp"

class Request;
class srv;

class Respons
{
	private:

		Request *	rq;
		srv			server;
		int			fd;

		std::string _url;
		std::string	_defaultRoot;
		std::string _extension;
		size_t		_loc;

	public:

		Respons(Request * request, srv & sv, int fDescriptor);
		~Respons();

		int		createRespons();
		void	setBestLocation();
		void	redirect(Location & loc);
		bool	manageData();
		
		int		getResponse();
		int		postResponse();
		int		deleteResponse();
		int		cgiResponse();
		
		bool	checkServerName();
		bool	checkAuthorized();
		bool	checkMethod();
		bool	checkBodySize();

		void	htmlRespond();
		void	jpgRespond();
		void	pngRespond();
		
		

		//FUNCIONES PARA PRUEBAS
		void printRequest();
		void printConf();
};