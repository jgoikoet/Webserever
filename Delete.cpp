#include "Delete.hpp"

Delete::Delete(std::string & ur, int f, srv & serv) : fd(f)
{
	url = ur;
	server = serv;
}

bool	Delete::DeleteFile(std::string ur)
{
	std::cout << "Erasing:" << ur << std::endl;
	if (remove(ur.c_str()) == 0)
        return (std::cout  << ur << " erased." << std::endl, true);
    else
		return (std::cerr << "Unable to erase " << ur << "\n", false);
}

bool		Delete::DeleteFolder(std::string ur)
{
	Directory d(ur);
	std::string	filePath;

    dir = d.getDir();

	for (size_t i = 2; i < dir.size(); i++)
	{
		filePath = ur + "/" + dir[i];
		if(Utils::isFile(filePath.c_str()) == true)
		{
			if(DeleteFile(filePath) == false)
				return (false);
		}
		else if(Utils::isDirectory(filePath.c_str()) == true)
			DeleteFolder(filePath.c_str());
	}
	if (rmdir(ur.c_str()) != 0)
		return (std::cerr << "Unable to erase " << ur << "\n", false);

	return true;
}


int	Delete::DeleteResource()
{
	struct stat infoArchivo;

    // Llamar a stat para intentar obtener información sobre el archivo
    if (stat(url.c_str(), &infoArchivo) != 0)
	{
        if (errno == EACCES)
		{
            std::cerr << "Error: No se tienen permisos para acceder al directorio o archivo." << std::endl;
			return(Error(403, fd, server), 1);
        }
		else if (errno == ENOENT)
		{
            std::cerr << "Error: El archivo o directorio no existe." << std::endl;
			return(Error(404, fd, server), 1);
        }
		else
		{
            std::cerr << "Error desconocido: " << strerror(errno) << std::endl;
			return(Error(405, fd, server), 1);
        }
    }


	else if(Utils::isDirectory(url.c_str()) == true)
	{
		if (DeleteFolder(url) == true)
			return (sendResponseOk(), 0);
		else
			return (Error (500, fd, server), 1);

	}
	else if(Utils::isFile(url.c_str()) == true)
	{
		if(DeleteFile(url) == true)
			return (sendResponseOk(), 0);
		else
			return (Error (500, fd, server), 1);
	}

	return (0);
}

void	Delete::sendResponseOk()
{
	response = "HTTP/1.1 200 OK\r\n";
   	response += "Content-Type: text/html\r\n";
  	response += "\r\n";

    response += "<!DOCTYPE html>";
    response += "<html lang=\"es\">";

    response += "<!DOCTYPE html>\n";
    response += "<html lang=\"es\">\n";
    response += "<head>\n";
    response += "    <meta charset=\"UTF-8\">\n";
    response += "    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n";
    response += "    <title>Delete resources ok</title>\n";
    response += "</head>\n";
    response += "<body>\n";
    response += "    <header>\n";
    response += "        <h1>Resource deleted... or not...</h1>\n";
    response += "        <h10>...Don`t stress yourself, it`s done... almost for sure...</h10>\n"; 
    response += "    <main>\n";
    response += "        <section>\n";
    response += "            <br><br><img src=\"load/ok.jpg\">\n";
    response += "        </section>\n";
    response += "        <br><br><a href=\"load/index.html\">BACK</a>\n";
    response += "    </main>\n";
    response += "    <footer>\n";
    response += "        <p>&copy; 2024. Todos los derechos reservados.</p>\n";
    response += "    </footer>\n";
    response += "</body>\n";
    response += "</html>\n";

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

Delete::~Delete(){}