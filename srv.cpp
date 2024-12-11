#include "dependences.hpp"
#include "srv.hpp"
#include "Config.hpp"
#include "Utils.hpp"

void srv::clear_arLoc() 
{
    arLoc.clear();
}
srv::srv()
{

}

bool srv::check_Location_root()
{
    size_t i =0;
    while(arLoc.size() > i)
    {
        if(arLoc[i]._location == "/")
            return (true);
        i++;
    }
    return(false);
}
srv::srv(std::string serverBlock)
{
    if(parseServerBlock(serverBlock) == false)
    {
        clear_arLoc();
        return;
    }
    if(  !arErr.empty() && !arErr[0].error_page.empty() && !arLoc.empty())
    {
        size_t i = 0;
        while(i < arLoc.size() )
        {
            std::map<int, std::string>::iterator it = arErr[0].error_page.begin();
            while (it != arErr[0].error_page.end())
            {
                if(arLoc[i]._location == it->second)
                {
                    if(arErr[0].error_page.find(it->first) != arErr[0].error_page.end())
                    {
                        ErrorRoot.insert(std::make_pair(it->first, arLoc[i]._root + arErr[0].error_page[it->first]));
                    }
                }
                ++it;
            }
            i++;
        }
    }
    readErrorRoot();
	if(check_Location_root() == false)
		clear_arLoc();

	for(size_t i = 0; i < arLoc.size(); i++)//usamos el _Root del srv en caso de que la location no tenga root
	{
		if(arLoc[i]._root.empty())
			arLoc[i]._root = _Root;
	}

}
srv::~srv()
{
}

void srv::readErrorRoot()
{
    if(!arErr.empty() && !arErr[0].defaultErMap.empty() && !ErrorRoot.empty())
    {
        for (std::map<int, std::string>::iterator it = ErrorRoot.begin(); it != ErrorRoot.end(); ++it) 
        {
            if (arErr[0].defaultErMap.find(it->first) != arErr[0].defaultErMap.end()) 
            {
                
                std::ifstream file(it->second.c_str());
                if (file) 
                {
                    std::string st;
                    std::stringstream buffer;
                    buffer << file.rdbuf();

                    if(it->first == 200)
                        st = "200 OK";
                    else if(it->first == 201)
                        st= "201 Created";
                    else if(it->first == 202) 
                        st = "202 Accepted";
                    else if(it->first == 204) 
                        st = "204 No Content";
                    else if(it->first == 301) 
                        st = "301 Moved Permanently";
                    else if(it->first == 302) 
                        st = "302 Found";
                    else if(it->first == 303) 
                        st = "303 See Other";
                    else if(it->first == 304) 
                        st = "304 Not Modified";
                    else if(it->first == 400) 
                        st = "400 Bad Request";
                    else if(it->first == 401) 
                        st = "401 Unauthorized";
                    else if(it->first == 403) 
                        st = "403 FORBIDDEN";
                    else if(it->first == 404) 
                        st = "404 Not Found POTOTO";
                    else if(it->first == 405) 
                        st = "405 Method Not Allowed";
                    else if(it->first == 406) 
                        st = "406 Not Acceptable";
                    else if(it->first == 408) 
                        st = "408 Request Timeout";
                    else if(it->first == 409) 
                        st = "409 Conflict";
                    else if(it->first == 411) 
                        st = "411 Length Required";
                    else if(it->first == 413) 
                        st = "413 Payload Too Large";
                    else if(it->first == 414) 
                        st = "414 URI Too Long";
                    else if(it->first == 415) 
                        st = "415 Unsupported Media Type";
                    else if(it->first == 500) 
                        st = "500 Internal Server Error";
                    else if(it->first == 501) 
                        st = "501 Not Implemented";
                    else if(it->first == 502) 
                        st = "502 Bad Gateway";
                    else if(it->first == 503) 
                        st = "503 Service Unavailable";
                    else if(it->first == 505) 
                        st = "505 HTTP Version Not Supported";
                    std::string httpResponse = "HTTP/1.1 " + st + "\r\n";
                    httpResponse += "\r\n";
                    httpResponse += buffer.str();
                    arErr[0].defaultErMap[it->first] = httpResponse;
                } 
                else 
                    std::cout << "Could not open file " << it->second << "\n";
            }
        }
    }
}
std::vector<Location> &  srv::getlocations()
{
    return(arLoc);
}
bool srv::setserverconfig(std::string & variable,std::string print, std::istringstream & lineStream )
{
    std::string temp;
    if(!variable.empty())
        return(std::cout << RED << "twice "<< print <<" in server" << WHITE << std::endl,false);
    lineStream >> temp;
    if (temp[temp.size() - 1] == ';')
        variable = temp.substr(0, temp.size() - 1);
    else
        variable = temp;
    return(true);
}

bool srv::parseServerBlock(const std::string& s)
{
    std::string line;
    std::istringstream stream(s);
    std::string error;
    std::string listen ;
    size_t i = 0;
    while (std::getline(stream, line)) 
	{
		std::istringstream lineStream(line);
		std::string key;
		lineStream >> key;
        if (key == "listen")
        {
            if(!listen.empty())
                return(std::cout << RED << "twice listen in server" << WHITE << std::endl,false);
            lineStream >> listen;
            if (listen[listen.size() - 1] == ';')
            {
                listen = listen.substr(0, listen.size() - 1);
            }
                while(listen[i]!= ':')
                {
                    i++;
                }
                if(_host.empty())
                {
                    _host = listen.substr(0, i - 0);
                    Utils::deletespaces(_host);
                }
                else
                    return(std::cout << RED << "twice host in server" << WHITE << std::endl,false);
                i++;
                if(_port.empty())
                {
                    _port = listen.substr(i, listen.size() - i);
                    Utils::deletespaces(_port);
                }
                else
                    return(std::cout << RED << "twice port in server" << WHITE << std::endl,false);
        }
        if (key == "server_name")
        {
            if(setserverconfig(_server_name,key, lineStream) == false)
                return(false);
        }
        if (key == "body_size")
        {
            if(setserverconfig(_body,key, lineStream) == false)
                return(false);
        }
        if (key == "root")
        {
            if(setserverconfig(_Root,key, lineStream) == false)
                return(false);
        }
        if( key == "error_page")
            error += line + "\n";
        if (key == "location")
        {
            std::string loc;
            loc = line + '\n';
            while (1)
            {
                if (!std::getline(stream, line))
                    break;
                loc += line + '\n';
                if (line.find('}') != std::string::npos)
                {
                    Location newlocation(loc);
                    if(newlocation.lock_ok == 1)
                        arLoc.push_back(loc);
                    else
                        return(false);
                    break;
                }
            }
        }
	}
    if(_host.empty() || _port.empty() || _body.empty() || _Root.empty()  || _server_name.empty())
    {
        std::cout << "|" << _host << "|" << _port << "|" << _body << "|" << _Root << "|"<< std::endl;
        return(false);
    }
    if(error.size() > 0)
        arErr.push_back(error);
    if(arErr.empty())//para evitar el segfault en arErr
    {
        std::string s = "";
        arErr.push_back(s);
    }
	if(checkstring() == false)
        return false;

    return(1);
}

bool srv::ipAddressToipNum(std::string ipAddress) 
{
    struct in_addr addr;
    // Convierte la dirección IP desde el formato de texto a la representación binaria en formato de red
    if (inet_pton(AF_INET, ipAddress.c_str(), &addr) != 1) 
	{
        std::cerr << "Error converting IP address." << std::endl;
        return false;
    }
    // Convierte la dirección IP desde el formato de red a la representación numérica en formato de host
	_ipNum = ntohl(addr.s_addr);

    return true;
}

    
bool srv::checkstring()
{
    if(!_host.empty() )
	{
        Utils::deletespaces(_host);
		if(ipAddressToipNum(_host) == false)
			return (false);
	}
    if(!_port.empty() )
	{
        Utils::deletespaces(_port);
		if(stringToSizeT(_port, _sizetPort) == false)
			return(std::cout << "Error doing the conversion from _port to __sizetport" << std::endl,false);
	}
    if(!_body.empty())
	{
        Utils::deletespaces(_body);
		if(stringToSizeT(_body,_sizetBody) == false)
			return(std::cout << "Error doing the conversion from _body to __sizetBody" << std::endl,false);
	}
    if(!_server_name.empty() )
        Utils::deletespaces(_server_name);
    if(!_Root.empty())
        Utils::deletespaces(_Root);

    
    return(true);
}
bool srv::stringToSizeT(const std::string& s, size_t &n) 
{
    std::istringstream iss(s);
    iss >> n;
    if (iss.fail()) 
		return(false);
	return(true);
}
