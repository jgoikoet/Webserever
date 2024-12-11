#include "Config.hpp"

void Config::clearArrayOfSrv()
{
    array_of_srv.clear();
    std::cout << RED << "array_of_srv.clear();" << std::endl << "array_of_srv.size()=" << array_of_srv.size() << WHITE << std::endl;
}
Config::Config(std::string configName)  : srvCount(0)
{
    
    if(config_routine(configName) == false)
	{
		std::cout << "if(config_routine(configName) == false)"<< std::endl;
         
        return;
	}
    
    if(checksrvloc() == false)
	{
        
        std::cout << "if(checksrvloc() == false)" << std::endl;
        clearArrayOfSrv(); 
		return;
	}
	if(checkduplicateports() == false)
	{
        std::cout << "if(checkduplicateports() == false)"<< std::endl;
        clearArrayOfSrv(); 
		return;
	}
    if(checkduplicateports_server_name() == false)
    {
        clearArrayOfSrv(); 
        return;
    }
    if(validatePort() == false)
	{
        std::cout << "if(validatePort() == false)"<< std::endl;
        clearArrayOfSrv(); 
		return;
	}
	if(getServerCount() == false)
	{
        std::cout << "if(getServerCount() == false)"<< std::endl;
        clearArrayOfSrv(); 
		return;
	}
    if(getArrayOfServers().empty())
    {
		return;
    }
    
}
Config::~Config()
{
   
}

bool Config::checkduplicateports_server_name()
{
    size_t i = 1;
    size_t e = 0;
    while(i < array_of_srv.size())
    {
        e = 0;
        while(e < i)
        {
            if ((array_of_srv[i]._port == array_of_srv[e]._port) && (array_of_srv[i]._server_name == array_of_srv[e]._server_name))
            {
                std::cout << "i=" << i <<"/" << "e=" << e << std::endl;
                std::cout << array_of_srv[i]._port << "=" <<array_of_srv[e]._port << std::endl;
                std::cout << array_of_srv[i]._server_name << "=" <<array_of_srv[e]._server_name << std::endl;
                return std::cout << RED << "checkduplicateports_server_name()" << WHITE << std::endl,false;
            }
            e++;
        }
        i++;
    }
    return true;
}
bool Config::checkduplicateports()
{
    size_t i = 1;
    size_t e = 0;

    while(i < array_of_srv.size())
    {
        e = 0;
        while(e < i)
        {
            if ((array_of_srv[i]._port == array_of_srv[e]._port) && (array_of_srv[i]._host == array_of_srv[e]._host))
            {
                std::cout << "i=" << i <<"/" << "e=" << e << std::endl;
                std::cout << array_of_srv[i]._port << "=" <<array_of_srv[e]._port << std::endl;
                std::cout << array_of_srv[i]._host << "=" <<array_of_srv[e]._host << std::endl;
                return std::cout << RED << "Dupicate port in config" << WHITE << std::endl,false;
            }
            e++;
        }
        i++;
    }
    return true;
}

bool Config::checksrvloc()///cambiar por el iterador por size y arreglar lo de los methods
{

    if(array_of_srv.size() == 0)
    {
        return(std::cout << "array_of_srv.size() == 0" << std::endl,false);
    }
    
    size_t i = 0;
    while (i < array_of_srv.size())
    {
        if(array_of_srv[i].arLoc.size() == 0)
        {

            return(std::cout << "(array_of_srv[" << i << "].arLoc.size() == 0" << std::endl,false); 
        }
        size_t e = 0;
        while (e < array_of_srv[i].arLoc.size())
        {
            ++e;
        }
        ++i;
    }
    return true;
}
bool Config::pairbrackets(const std::string s)
{
    std::stack<char> brackets;

    for (size_t i = 0; i < s.size(); i++)
    {
        if (s[i] == '{')
        {
            brackets.push('{');
        }
        else if (s[i] == '}')
        {
            if (brackets.empty())
            {
                return 0;
            }
            brackets.pop();
        }
    }
    if(brackets.empty())
        return(true);
    return false;
}


bool Config::openFile(std::string Configname)
{
    this->file.open(Configname.c_str(), std::ios::in);
    if (this->file.is_open() == false) 
        return false;
    std::stringstream buffer;
    buffer << file.rdbuf();

    // Convertir el contenido del stringstream en un string
    this->file_content = buffer.str();
    //std::cout << this->Config_data << std::endl;//para printear el contenido del archivo
    file.close();
    return true;
}


bool  Config::config_routine(std::string configName)
{
    if(openFile(configName) == true)
    {
        if(file_content.empty())
            return(std::cout << RED << "File is Empty!"<< WHITE << std::endl ,false);
        if(pairbrackets(file_content) == false)
            return(std::cout << RED << "Bad brackets configuration, please check your config file" << WHITE << std::endl,false);
        if(createSrv() == false)
            return(false);
        return(true);
    } 
    else
        return std::cout << "Archivo no abierto" << std::endl,false;
}
int Config::findCharInString(const std::string& str, char c) {
    std::size_t found = str.find(c);

    if (found != std::string::npos) {
        return static_cast<int>(found);
    } else {
        return -1;  // Devuelve -1 si el carácter no se encuentra
    }
}

bool Config::checkServerBalance(const std::string& str) {
    int balance = 0;
    bool foundServer = false;

    for (size_t i = 0; i < str.size(); ++i) {
        if (str[i] == '{') {
            ++balance;
        } else if (str[i] == '}') {
            --balance;
        }

        if (i <= str.size() - 6) { // 6 is the length of "Server"
            if (str.substr(i, 6) == "server" && (i+6 >= str.size() || str[i+6] != '_'))
            {
                foundServer = true;
                if (balance != 0) {
                    return false;
                }
            }
        }
    }

    if (!foundServer && balance == 0) {
        return false;
    }

    return true;
}
bool Config::createSrv()
{
    size_t tmp;
    std::istringstream f(this->file_content);
    std::string line;    
    std::string serverBlock;
    size_t i =0;
    std::stack<char> stak;
    while(i < file_content.size())
    {
        tmp = i;
        while(i < file_content.size() && file_content[i] != '{' && file_content[i] != '}')
            i++;
        if(i == file_content.size())
            break;
        if(file_content[i] == '{')
            stak.push('{');
        else if (file_content[i] == '}')
            break;
        i++;
        while (i < file_content.size() && !stak.empty())
        {
            if(file_content[i] == '{')
                stak.push(file_content[i]);
            else if(file_content[i] == '}')
                stak.pop();
            i++;
        }
        size_t length = i - tmp;
        if (tmp + length > file_content.size())
            length = file_content.size() - tmp;
        std::string sub = file_content.substr(tmp, length);

        
        if(checkServerBalance(sub) == false)
            return(std::cout << "Invalid Server configuration" << std::endl,false);
        size_t pos = sub.find("server");//usar server { y darle -2 ??

        
        if (pos != std::string::npos) 
        {
            srv newServer(sub);
            newServer.locationCount = Utils::countSubstring(file_content.substr(tmp, i - tmp), "location");
            array_of_srv.push_back(newServer);
        } 
        else 
            return(std::cout << "sub didnt contain the word server" << std::endl,false);
    
    }
    return(true);
}


bool Config::getServerCount()
{
    size_t  pos = 0;
    int server_name = 0;
    while ((pos = file_content.find("server", pos)) != std::string::npos) 
    {
        this->srvCount++;
        pos += 6; // Longitud de la cadena "Server"
    }
    pos = 0;
    while ((pos = file_content.find("server_name", pos)) != std::string::npos) 
    {
        server_name++;
        pos += 11; // Longitud de la cadena "Server"
    }
    this->srvCount = this->srvCount - server_name;
    if (this->srvCount > 0) 
    {
        //std::cout << "Servers: " << GREEN << srvCount << WHITE << std::endl;
        return true;
    }
    else
        return std::cout << RED << "Server count is less than 0" << WHITE << std::endl,0;
}
///////////////////////
/*
El rango de puertos válidos en Nginx, y en general en cualquier sistema que siga las 
convenciones de red estándar, es de 1 a 65535. Sin embargo, los puertos del 1 al 1023 
son conocidos como puertos bien conocidos y están reservados para servicios específicos 
(por ejemplo, el puerto 80 para HTTP, el puerto 443 para HTTPS). Por lo tanto, a menos 
que estés ejecutando Nginx como root (lo cual no se recomienda por razones de seguridad),
 deberías usar un puerto en el rango de 1024 a 65535.
*/
bool Config::validatePort()
{
    std::cout << std::endl;
    size_t i = 0;
    while(i < array_of_srv.size())
    {
        if(array_of_srv[i]._sizetPort == 0)
            return(std::cout << array_of_srv[i]._sizetPort << std::endl,false);
        if(array_of_srv[i]._sizetPort > 1023 && array_of_srv[i]._sizetPort < 65535)
            std::cout << "Server " << i + 1 << "  Port: " << GREEN << array_of_srv[i]._sizetPort << WHITE << " active"  << std::endl;
        else
            return std::cout << CYAN << "validatePort() error the value of port is "<< RED << array_of_srv[i]._sizetPort << CYAN <<" should be betwen 1023 to 65535"<< WHITE << std::endl,false;
        ++i;
    }
    std::cout << std::endl;
    return true;
}
std::vector<srv> & Config::getArrayOfServers()
{
    return array_of_srv;
}

std::string & Config::skip_p_t_esp(std::string &s)
{
    size_t start = 0;
    while (start < s.size() && (s[start] == ' ' || s[start] == '\n' || s[start] == '\t')) {
        ++start;
    }
    s = s.substr(start);
    return s;
}


