#ifndef ERRORPAGE_HPP
# define ERRORPAGE_HPP
#include "dependences.hpp"


class ErrorPage 
{
    public:

    std::map<int, std::string> error_page;
    std::vector<int> errorIndex;
    std::map< int, std::string> defaultErMap;

    ErrorPage();
    ErrorPage(std::string ErrorPageBlock);
    ~ErrorPage();

    void inidefaultErMap();
    std::string createHtml_in_mapValue(std::string text);
    bool ErrorParseBlock (const std::string ErrorParseBlock);

    bool directoryExistsA(const std::string& dirName);
    bool fileExistsA(const std::string& filename);
    void printErrorPageDetails();
};
#endif