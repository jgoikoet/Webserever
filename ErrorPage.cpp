#include "ErrorPage.hpp"


ErrorPage::ErrorPage()
{

    inidefaultErMap();
    std::string e = "404";
    int i = atoi(e.c_str());
    error_page[i] = "/404.html";
	errorIndex.push_back(i);
}

ErrorPage::ErrorPage(std::string ErrorPageBlock)
{
    inidefaultErMap();
    if(ErrorParseBlock(ErrorPageBlock) == false)
        return;
}
ErrorPage::~ErrorPage()
{
}

void ErrorPage::printErrorPageDetails() {
/*     std::cout << MAGENTA << "Error Page Details:\n"<< WHITE;

    std::cout << "error_page:\n";
    for (std::map<int, std::string>::iterator it = error_page.begin(); it != error_page.end(); ++it) {
        std::cout << "Error Code: " << it->first << ", Page: " << it->second << "\n";
    }

    std::cout << "errorIndex:\n";
    for (size_t i = 0; i < errorIndex.size(); i++) {
        std::cout << "Index " << i << ": " << errorIndex[i] << "\n";
    } */

/*     std::cout << "defaultErMap:\n";
    for (std::map<int, std::string>::iterator it = defaultErMap.begin(); it != defaultErMap.end(); ++it) {
        std::cout << "Error Code: " << it->first << ", Default Error: " << it->second << "\n";
    } */

}

std::string ErrorPage::createHtml_in_mapValue(std::string text)
{
    std::string httpResponse = "HTTP/1.1 " + text + "\r\n";
    httpResponse += "Content-Type: text/html\r\n";
    httpResponse += "\r\n";

    httpResponse += "<!DOCTYPE html>";
    httpResponse += "<html lang=\"es\">";
    httpResponse += "<head>";
    httpResponse += "<meta charset=\"UTF-8\">";
    httpResponse += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">";
    httpResponse += "<title>" + text +  "</title>";
    httpResponse += "<style>";
    httpResponse += "body {";
    httpResponse += "text-align: center;";
    httpResponse += "padding: 50px;";
    httpResponse += "font-family: \"Arial\", sans-serif;";
    httpResponse += "}";
    httpResponse += "h1 {";
    httpResponse += "font-size: 50px;";
    httpResponse += "}";
    httpResponse += "p {";
    httpResponse += "font-size: 20px;";
    httpResponse += "}";
    httpResponse += "a {";
    httpResponse += "color: #0077cc;";
    httpResponse += "text-decoration: none;";
    httpResponse += "}";
    httpResponse += "a:hover {";
    httpResponse += "text-decoration: underline;";
    httpResponse += "}";
    httpResponse += "</style>";
    httpResponse += "</head>";
    httpResponse += "<body>";
    httpResponse += "<h2>Error " + text + "</h2>";
    httpResponse +="<a href=\"/\">Volver a la página de inicio</a>";
    httpResponse +="</body>";
    httpResponse += "</html>"; 
    return httpResponse;
}
void ErrorPage::inidefaultErMap()
{
    std::string _200 = "200 OK";
    std::string _201 = "201 Created";
    std::string _202 = "202 Accepted";
    std::string _204 = "204 No Content";

    std::string _301 = "301 Moved Permanently";
    std::string _302 = "302 Found";
    std::string _303 = "303 See Other";
    std::string _304 = "304 Not Modified";

    std::string _400 = "400 Bad Request";
    std::string _401 = "401 Unauthorized";
    std::string _403 = "403 Forbidden";
    std::string _404 = "404 Not Found";
    std::string _405 = "405 Method Not Allowed";
    std::string _406 = "406 Not Acceptable";
    std::string _408 = "408 Request Timeout";
    std::string _409 = "409 Conflict";
    std::string _411 = "411 Length Required";
    std::string _413 = "413 Payload Too Large";
    std::string _414 = "414 URI Too Long";
    std::string _415 = "415 Unsupported Media Type";

    std::string _500 = "500 Internal Server Error";
    std::string _501 = "501 Not Implemented";
    std::string _502 = "502 Bad Gateway";
    std::string _503 = "503 Service Unavailable";
    std::string _505 = "505 HTTP Version Not Supported";

////////////////////////////////////////////////////////////////

    defaultErMap[200] = createHtml_in_mapValue(_200);
    defaultErMap[201] = createHtml_in_mapValue(_201);
    defaultErMap[202] = createHtml_in_mapValue(_202);
    defaultErMap[204] = createHtml_in_mapValue(_204);

    defaultErMap[301] = createHtml_in_mapValue(_301);
    defaultErMap[302] = createHtml_in_mapValue(_302);
    defaultErMap[303] = createHtml_in_mapValue(_303);
    defaultErMap[304] = createHtml_in_mapValue(_304);

    defaultErMap[400] = createHtml_in_mapValue(_400);
    defaultErMap[401] = createHtml_in_mapValue(_401);
    defaultErMap[403] = createHtml_in_mapValue(_403);
    defaultErMap[404] = createHtml_in_mapValue(_404);
    defaultErMap[405] = createHtml_in_mapValue(_405);
    defaultErMap[406] = createHtml_in_mapValue(_406);
    defaultErMap[408] = createHtml_in_mapValue(_408);
    defaultErMap[409] = createHtml_in_mapValue(_409);
    defaultErMap[411] = createHtml_in_mapValue(_411);
    defaultErMap[413] = createHtml_in_mapValue(_413);
    defaultErMap[414] = createHtml_in_mapValue(_414);
    defaultErMap[415] = createHtml_in_mapValue(_415);

    defaultErMap[500] = createHtml_in_mapValue(_500);
    defaultErMap[501] = createHtml_in_mapValue(_501);
    defaultErMap[502] = createHtml_in_mapValue(_502);
    defaultErMap[503] = createHtml_in_mapValue(_503);
    defaultErMap[505] = createHtml_in_mapValue(_505);   
}


bool ErrorPage::ErrorParseBlock (const std::string ErrorParseBlock)
{
    
    std::string line;
    std::istringstream stream(ErrorParseBlock);

    while (std::getline(stream, line)) 
	{
		std::istringstream lineStream(line);
		std::string key;

		lineStream >> key;
        if (key == "error_page")
        {
            int temp;
            lineStream >> key;
            temp = std::atoi(key.c_str());
            errorIndex.push_back(temp);
            lineStream >> key;
            if(key[key.size() - 1] == ';')
                error_page.insert(std::make_pair(temp, key.substr(0,key.size() - 1)));
            else
                error_page.insert(std::make_pair(temp, key));
        }
        else
        {
            int e = 0;
            std::string key;
            errorIndex.push_back(e);
            error_page.insert(std::make_pair(e, key));
        }
    }

    return(1);
}
bool ErrorPage::directoryExistsA(const std::string& dirName) 
{
    struct stat info;

    if (stat(dirName.c_str(), &info) != 0) {
        // No se puede acceder al directorio
        return false;
    } else if (info.st_mode & S_IFDIR) {
        // Es un directorio
        return true;
    } else {
        // Existe, pero no es un directorio
        return false;
    }
}
bool ErrorPage::fileExistsA(const std::string& filename) 
{
    std::ifstream file(filename.c_str());
    return file.good();
}