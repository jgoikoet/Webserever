
#include "Error.hpp"

Error::Error(int er, int fdescriptor, srv & server)
{
    sendError(server, er, fdescriptor);
}

Error::~Error() {}

std::string Error::status(int error, srv & server)
{
    return server.arErr[0].defaultErMap[error];
}
std::string Error::toString(const int &num)
{
    std::stringstream s;
    s << num;
    return (s.str());
}

void    Error::sendError(srv & server, int error, int fd)
{
    std::string httpResponse = status(error,server);
    int w = write(fd, httpResponse.c_str(), httpResponse.size());
    if (w == 0 || w == -1)
	{
	    if (w == 0)
		    std::cout << "Client of socket " << fd << "closed connection. Client removed" << WHITE << std::endl;
	    else if (w == -1)
	    	std::cout << RED << "Error in socket " << fd << "closed connection. Client removed" << WHITE << std::endl;
	    close (fd);
    }
}