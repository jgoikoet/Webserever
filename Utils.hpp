
#pragma once

# include "dependences.hpp"


class Utils
{
    public:

        static bool         isFile(const char* path);
        static bool         isDirectory(const char* path);
        static std::string  toString(const int &num);
        static int          toInt(const std::string &str);

	    static size_t		size(const char *s);   
        static int			countSubstring(const std::string& str, const std::string& sub);
        
        static void			deletespaces(std::string &s);

        static std::string  status(int error);
};