
#include "Utils.hpp"

std::string Utils::status(int error)
{
	std::map<int, std::string> statusCodes;

	statusCodes[200] = "200 OK";
	statusCodes[201] = "201 Created";
	statusCodes[202] = "202 Accepted";
	statusCodes[204] = "204 No Content";
	statusCodes[301] = "301 Moved Permanently";
	statusCodes[302] = "302 Found";
	statusCodes[303] = "303 See Other";
	statusCodes[304] = "304 Not Modified";
	statusCodes[400] = "400 Bad Request";
	statusCodes[401] = "401 Unauthorized";
	statusCodes[403] = "403 Forbidden";
	statusCodes[404] = "404 Not Found";
	statusCodes[405] = "405 Method Not Allowed";
	statusCodes[406] = "406 Not Acceptable";
	statusCodes[408] = "408 Request Timeout";
	statusCodes[409] = "409 Conflict";
	statusCodes[411] = "411 Length Required";
	statusCodes[413] = "413 Payload Too Large";
	statusCodes[414] = "414 URI Too Long";
	statusCodes[415] = "415 Unsupported Media Type";
	statusCodes[500] = "500 Internal Server Error";
	statusCodes[501] = "501 Not Implemented";
	statusCodes[502] = "502 Bad Gateway";
	statusCodes[503] = "503 Service Unavailable";
	statusCodes[505] = "505 HTTP Version Not Supported";

	return statusCodes[error];
}

bool Utils::isFile(const char* path)
{
    struct stat info;
    if (stat(path, &info) != 0)
        return (false);

    return S_ISREG(info.st_mode);
}

bool Utils::isDirectory(const char* path)
{
    struct stat info;
    if (stat(path, &info) != 0)
        return false;

    return S_ISDIR(info.st_mode);
}

int Utils::toInt(const std::string &str)
{
    std::stringstream ss(str);
    int num;
    ss >> num;
    return (num);
}

std::string Utils::toString(const int &num)
{
    std::stringstream ss;
    ss << num;
    return (ss.str());
}

size_t Utils::size(const char *s)
{
	size_t i = 0;
	if (s == NULL)
		return 0;
	while (s[i] != '\0')
		++i;
	return i;
}
int Utils::countSubstring(const std::string& str, const std::string& sub)
{
    if (sub.length() == 0) 
        return 0;
    int count = 0;
    for (size_t offset = str.find(sub); offset != std::string::npos;offset = str.find(sub, offset + sub.length()))
        ++count;
    return count;
}


void Utils::deletespaces(std::string &s)
{
    size_t i = 0;
    std::string temp;
    while(i < s.size())
    {
        while(s[i] == ' ')
            i++;
		if(s[i] != ' ')
		{
        	temp.push_back(s[i]);
        	i++;
		}
    }
	s = temp;
}
