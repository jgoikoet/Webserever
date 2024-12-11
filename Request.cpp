

#include "Request.hpp"

Request::Request() : content_len(0), kepOnReading(true), firstRead(true)
{
    
}

Request::~Request() {}

void Request::addBuffer(char * buf, int bytes)
{
    if (bytes > 100)
        part.clear();
    buffer.append(buf, bytes);
    part.append(buf, bytes);

    if (firstRead)
    {
        firstRead = false;

        std::string head;
        size_t headEnd = buffer.find("\r\n\r\n");
        if (headEnd != std::string::npos)
            head = buffer.substr(0, headEnd);
        else
            head = buffer;
        
        std::string line;
        std::istringstream stream(head);

        while (std::getline(stream, line))
        {
            if (line.find("boundary=") != std::string::npos)
            {
                boundary = line.substr(line.find("boundary=") + 9);
                boundary = boundary.substr(0, boundary.size() - 1);
                boundaryStart = "--" + boundary;
                boundaryEnd = "--" + boundary + "--";
            }
        }
    }
}

void    Request::procesData(std::string dat)
{
    std::replace(dat.begin(), dat.end(), '+', ' ');
    
    while (dat.empty() == false)// && i < 10)
    {
        std::string stract;
        std::string clave;
        std::string valor;

        size_t amper = dat.find("&");
        if (amper != std::string::npos)
        {
            stract = dat.substr(0, amper);
            dat = dat.substr(amper);
            if(dat.size() > 1)
                dat = dat.substr(1);
        }
        else
        {
            stract = dat;
            dat.clear();
        }

        size_t equal = stract.find("=");
        if (equal != std::string::npos)
        {
            clave = stract.substr(0, equal);
            valor = stract.substr(equal);
            if (valor.size() > 1)
                valor = valor.substr(1);
            else 
                valor.clear();
        }
        else
            clave = stract;
        data[clave] = valor;
        //i++;
    }
    std::map<std::string, std::string>::iterator it = data.begin();
    while (it != data.end())
    {
        it++;
    }
}

void    Request::stractGetData()
{
    std::string dat;

    size_t question = uri.find("?");
    if(question != std::string::npos)
    {
        dat = uri.substr(question);
        uri = uri.substr(0, question);
        if (dat.size() > 1)
            dat = dat.substr(1);
        else
            dat.clear();
    }
    else
        return;
    
    if (dat.empty() == false)
        procesData(dat);
}

void    Request::stractPostData()
{
    if (body.empty() == false)
        procesData(body);
}

void Request::parse()
{
    //std::cout << std::endl << YELLOW << buffer << WHITE << std::endl;

    std::string line;
    std::istringstream stream(buffer);

    while (std::getline(stream, line))
    {
        std::istringstream lineStream(line);
        std::string key;

        lineStream >> key;

        if (key == "GET" || key == "POST" || key == "DELETE")
        {
            if (key == "GET")
                method = "get";
            if (key == "POST")
                method = "post";
            if (key == "DELETE")
                method = "delete";
            lineStream >> uri;
        }
        else if (key == "Host:")
        {
            std::string hostAndPort;
            lineStream >> hostAndPort;

            size_t secondColonPos = hostAndPort.find(":");

            host = hostAndPort.substr(0, secondColonPos);
            port = hostAndPort.substr(secondColonPos + 1);
        }
        else if (key == "Content-Length:")
            lineStream >> content_len;
        else if (line.find("boundary=") != std::string::npos)
            stractBoundary();
        else if (line == "\r")
            break;
    }
    line.clear();
    while (std::getline(stream, line))
        body += line;

    if (uri.size() > 1 && uri[uri.size() - 1] == '/')
        uri = uri.substr(0, uri.size() - 1);

    if(method == "get")
        stractGetData();
    else if(method == "post" && boundary.empty())
        stractPostData();
    
}

void Request::stractBoundary()
{
    size_t in = buffer.find(boundaryStart) + boundaryStart.size() + 1;
    boundaryContent = buffer.substr(in, buffer.find(boundaryEnd) - in - 2);

    upfileContent = boundaryContent.substr(boundaryContent.find("\r\n\r\n") + 4);

    upfileName = boundaryContent.substr(boundaryContent.find("filename=\"") + 10);
    upfileName = upfileName.substr(0, upfileName.find("\""));

}


std::string Request::getMethod() { return method; }
std::string Request::getUri() { return uri; }
std::string Request::getHost() { return host; }
std::string Request::getPort() { return port; }
std::string Request::getBody() { return body; }
std::string Request::getBoundary() { return boundary; }
size_t Request::getContentLen() { return content_len; }
std::string Request::getDownFile() { return downfile; }
std::string Request::getUpFileContent() { return upfileContent; }
std::string Request::getUpFileName(){ return upfileName; }

// FUNCIONES PARA PRUEBAS----------------------------------------------------------
void Request::printRequest()
{
    //std::cout << GREEN << "method: " << BLUE << method << std::endl;
    //std::cout << GREEN << "uri: " << BLUE << uri << std::endl;
    //std::cout << GREEN << "host: " << BLUE << host << std::endl;
    //std::cout << GREEN << "port: " << BLUE << port << std::endl;
    //std::cout << GREEN << "Content Lenght: " << BLUE << content_len << std::endl;
    std::cout << GREEN << "Body: " << BLUE << body << WHITE << std::endl
              << std::endl;
}