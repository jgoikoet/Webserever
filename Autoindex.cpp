#include "Autoindex.hpp"
#include "dependences.hpp"

bool Autoindex::hasWritePermission(const char* filePath) 
{
    // Verifica si el archivo tiene permisos de escritura
    if (access(filePath, W_OK) == 0) {
        return true;  // Tiene permisos de escritura
    } else {
        // Si no tiene permisos, imprime el error
        std::cerr << "Error: No tiene permisos de escritura en el archivo '"
                  << filePath << "'. Error: " << strerror(errno) << std::endl;
        return false;  // No tiene permisos de escritura
    }
}
Autoindex::Autoindex(srv& server, int fd, size_t i) 
{
    _i = i;
    _fd = fd;
    _server = server;
    handle_request(server.arLoc[i]._root); 
}
Autoindex::~Autoindex()
{
}
void Autoindex::handle_request(const std::string& directory_path) 
{
    std::string response;
    std::ostringstream oss;

    response = generate_autoindex(directory_path);

    // metemos la info del html y del index que hemos creado para el index en un ostringstream
    oss << "HTTP/1.1 200 OK\r\n";
    oss << "Content-Type: text/html\r\n";
    oss << "Content-Length: " << response.size() << "\r\n";
    oss << "\r\n";
    oss << response;
    std::string str = oss.str();
    size_t n = str.size();
    char* cstr = new char[str.length() + 1];
    std::strcpy(cstr, str.c_str());
    int w = write (_fd, cstr, n);
    delete [] cstr;
    if (w == 0 || w == -1)
	{
	if (w == 0)
		std::cout << "Client of socket " << _fd << "closed connection. Client removed" << WHITE << std::endl;
	else if (w == -1)
		std::cout << RED << "Error in socket " << _fd << "closed connection. Client removed" << WHITE << std::endl;
	close (_fd);
    }
}
bool Autoindex::is_directory(const std::string& path) 
{
    struct stat statbuf;
    if (stat(path.c_str(), &statbuf) != 0) 
        return false;
    return S_ISDIR(statbuf.st_mode);
}


std::string Autoindex::generate_autoindex(const std::string& directory_path) 
{
    DIR *dir;
    struct dirent *entry;
    std::ostringstream html;

    dir = opendir(directory_path.c_str());
    if (dir == NULL) 
        return "<html><body><h1>Unable to open directory</h1></body></html>";

    html << "<html><head><title>Index of " << directory_path << "</title></head>";
    html << "<body><h1>Index of " << directory_path << "</h1>";
    html << "<table>";
    html << "<tr><th>Name</th><th>Size</th><th>Last Modified</th></tr>";

    while ((entry = readdir(dir)) != NULL) 
    {
        std::string name = entry->d_name;
        if (name == "." /* || name == ".." */)
        {
            continue;
        }
        std::string full_path = directory_path + "/" + name;

        struct stat filestat;
        if (stat(full_path.c_str(), &filestat) != 0) 
        {
            continue; // Error al obtener información del archivo
        }

        // Formatear la fecha de modificación
        char timebuf[80];
        struct tm *timeinfo;
        timeinfo = localtime(&filestat.st_mtime);
        strftime(timebuf, sizeof(timebuf), "%Y-%m-%d %H:%M:%S", timeinfo);

        html << "<tr>";

        if (is_directory(full_path)) 
        {
            if(full_path[0] == '.' && full_path[1] == '/')
            {
                full_path = full_path.substr(1);
            }
            html << "<td><a href=\"" << full_path << "/\">" << name << "/</a></td>";
            html << "<td>-</td>";  // Sin tamaño para directorios
            html << "<td>" << filestat.st_size << " bytes</td>";
        } 
        else 
        {
            if(full_path[0] == '.' && full_path[1] == '/')
            {
                full_path = full_path.substr(1);
            }
            html << "<td><a href=\"" << full_path  << "\">" << name << "</a></td>";
            html << "<td>" << filestat.st_size << " bytes</td>";
        }

        html << "<td>" << timebuf << "</td>";
        html << "</tr>";
    }
    closedir(dir);

    html << "</table></body></html>";
    return html.str();
}
