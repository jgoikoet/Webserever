#include "Dinamic.hpp"

Dinamic::Dinamic(std::string ur, int f) : fd(f) 
{
    url = ur;
    Directory d(url);
    dir = d.getDir();
    //createResponse();
}

Dinamic::~Dinamic(){}

void Dinamic::createDeleteForm()
{
    response = "HTTP/1.1 200 OK\r\n";
   	response += "Content-Type: text/html\r\n";
  	response += "\r\n";

    response += "<!DOCTYPE html>";
    response += "<html lang=\"es\">";

    response += "<head>";
    response += "<meta charset=\"UTF-8\">";
    response += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">";
    response += "<title>Delete files</title>";
    response += "</head>";

    response += "<body>";
    response += "<h3>Clic on the file you wanna delete:</h3>";

    for(size_t i = 2; i < dir.size(); i ++)
		response += "<a href=\"/upload?file=" + dir[i] + "&page=setDelete\">" + dir[i] + "</a><br>";

	response += "<br><br><a href=\"load/index.html\"> BACK </a><br>";

    int w = write (fd, response.c_str(), response.size());
    if (w == 0 || w == -1)
	{
	if (w == 0)
		std::cout << "Client of socket " << fd << "closed connection. Client removed" << WHITE << std::endl;
	else if (w == -1)
		std::cout << RED << "Error in socket " << fd << "closed connection. Client removed" << WHITE << std::endl;
	close (fd);
    }
}

void    Dinamic::createResponse()
{
    response = "HTTP/1.1 200 OK\r\n";
   	response += "Content-Type: text/html\r\n";
  	response += "\r\n";

    response += "<!DOCTYPE html>";
    response += "<html lang=\"es\">";

    response += "<head>";
    response += "<meta charset=\"UTF-8\">";
    response += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">";
    response += "<title>File management on server</title>";
    response += "</head>";

    response += "<body>";
    response += "<h1>File management on server</h1>";
    response += "<h2>Files on server:</h2>";

    for(size_t i = 2; i < dir.size(); i ++)
        response +=   dir[i] + "<br>";

    response += "<br><h4>What you wanna do darling?:</h4>";

    response += "<form method=\"GET\" action=\"/load\" style=\"display: inline;\">";
    response += "<button type=\"submit\">Upload file</button>  ";
    response += "</form>";
    
    response += "<form method=\"POST\" action=\"/upload\" style=\"display: inline;\">";
    response += "<input type=\"hidden\" name=\"page\" value=\"download\">";
    response += "<button type=\"submit\">Download file at the fucking speed of light</button>  ";
    response += "</form>";

    response += "<form method=\"POST\" action=\"/upload\" style=\"display: inline;\">";
    response += "<input type=\"hidden\" name=\"page\" value=\"delete\">";
    response += "<button type=\"submit\">Delete resource</button>  ";
    response += "</form>";

    response += "</body>";
    response += "</html>";

    int w = write (fd, response.c_str(), response.size());
    if (w == 0 || w == -1)
	{
	if (w == 0)
		std::cout << "Client of socket " << fd << "closed connection. Client removed" << WHITE << std::endl;
	else if (w == -1)
		std::cout << RED << "Error in socket " << fd << "closed connection. Client removed" << WHITE << std::endl;
	close (fd);
    }
}