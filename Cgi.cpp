
#include "Cgi.hpp"

Cgi::Cgi(Request *r, std::string  ur, int f,  srv & serv) : rq(r), url(ur), fd(f), server (serv)
{
	inFd = dup(0);
    outFd = dup(1);
}

Cgi::~Cgi()
{
	delete [] _env;//CUIDAOOOOOOOOO
}

void	Cgi::setPost()
{


	pipe(inPipe);
	dup2(inPipe[1], 1);
	dup2(inPipe[0], 0);
	std::cout << rq->data["numero"] << std::endl;
}


void Cgi::createPostEnv()
{
    std::string user = std::getenv("USER");
	std::string	userEnv = "USER=" + user;
    std::string home = std::getenv("HOME");
	std::string	homeEnv = "HOME=" + home;
    std::string path = std::getenv("PATH");
	std::string	pathEnv = "PATH=" + path;
	_env = new char*[4];

    
	
    //std::vector<std::string>    envVect;

	envVect.push_back(userEnv);
	envVect.push_back(homeEnv);
	envVect.push_back(pathEnv);

    for (int i = 0; i < 3; i++)
        _env[i] = (char *)envVect[i].c_str();

    _env[3] = NULL;
}

void Cgi::createGetEnv()
{
    std::string user = std::getenv("USER");
	std::string	userEnv = "USER=" + user;
    std::string home = std::getenv("HOME");
	std::string	homeEnv = "HOME=" + home;
    std::string path = std::getenv("PATH");
	std::string	pathEnv = "PATH=" + path;
	std::string	query_string = "QUERY_STRING=" + rq->data["numero"];
	_env = new char*[5];

    
	
    //std::vector<std::string>    envVect;

	envVect.push_back(userEnv);
	envVect.push_back(homeEnv);
	envVect.push_back(pathEnv);
	envVect.push_back(query_string);

    for (int i = 0; i < 4; i++)
        _env[i] = (char *)envVect[i].c_str();

    _env[4] = NULL;
}

void Cgi::exec()
{	
    int id;
	char **args;
	args = new char*[2];
    args[0] = (char*)url.c_str();
	args[1] = NULL;

    pipe(outPipe);

    id = fork();

    if (id == 0)
    {
        dup2(outPipe[1], STDOUT_FILENO);
        close(outPipe[1]);
        execve(args[0], args, _env);
    }
    else
    {

		int status;
        pid_t res = waitpid(id, &status, WNOHANG);
	   	for (int i = 0; i < 5 && res == 0; i++)
		{
       		usleep(100000); // Espera 100 milisegundos
			res = waitpid(id, &status, WNOHANG);
		}
        if (res == 0)
		{
            // Si el proceso hijo no ha terminado, lo matamos
            kill(id, SIGKILL);
            std::cerr << std::endl << RED << "Child procces Timeout" << WHITE << std::endl;
			Error (500, fd, server);// el misterio del bucle infinito...
        } else if (res > 0)
		{
            
            dup2(outPipe[0], 0);
            std::getline(std::cin, result);
			close(outPipe[0]);
            
            wait(NULL); // Esperamos la terminación del hijo
			/* Incluso si waitpid con WNOHANG detectó previamente que el hijo terminó, 
			no se garantiza que waitpid en ese punto ya haya recolectado completamente 
			su estado. Por eso, una llamada final a wait(NULL); es necesaria para limpiar
			completamente al proceso hijo y evitar que quede en estado zombie. */
        }
        dup2(inFd, 0);
        dup2(outFd, 1);

        delete [] args;
		if(result.empty() == false && res != 0) 
            sendResult();
		else if(res != 0)
			Error (500, fd, server);
    }

}


void Cgi::sendResult()
{
    std::string httpResponse = "HTTP/1.1 200 OK\r\n";
   	httpResponse += "Content-Type: text/html\r\n";
  	httpResponse += "\r\n";

    httpResponse += "<!DOCTYPE html>";
    httpResponse += "<html lang=\"es\">";

    httpResponse += "<head>";
    httpResponse += "<meta charset=\"UTF-8\">";
    httpResponse += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">";
    httpResponse += "<title>Magia!</title>";
    httpResponse += "</head>";

    httpResponse += "<body>";
    httpResponse += "<h2>And the result is: " + result + "</h2>";
    httpResponse += "<img src= \"nu.jpg\">";
    httpResponse += "<br><br><a href=\"javascript:history.back()\">BACK</a>";
    httpResponse += "</body>";
    httpResponse += "</html>";

    int w = write (fd, httpResponse.c_str(), httpResponse.size());
    if (w == 0 || w == -1)
	{
	if (w == 0)
		std::cout << "Client of socket " << fd << "closed connection. Client removed" << WHITE << std::endl;
	else if (w == -1)
		std::cout << RED << "Error in socket " << fd << "closed connection. Client removed" << WHITE << std::endl;
	close (fd);
    }
}