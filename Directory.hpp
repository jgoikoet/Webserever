#ifndef DIRECTORY_HPP
# define DIRECTORY_HPP
# include "Utils.hpp"
# include "dependences.hpp"

class Directory
{
    private:

        std::string dir;
        std::vector<std::string> v;

    public:

        Directory(std::string d);
        ~Directory();

        void    openDir();
        std::vector<std::string> & getDir();
};

#endif