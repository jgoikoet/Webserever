#include "Directory.hpp"

Directory::Directory(std::string d) : dir(d)
{
    openDir();
}

void    Directory::openDir()
{
    DIR *directory;
    struct dirent *entry;
    
    directory = opendir(dir.c_str());
    if (!directory) {
        perror("Error al abrir el directorio");
        return;
    }

    while((entry = readdir(directory)) != NULL)
	{
    	v.push_back(entry->d_name);
	}

    closedir(directory);
}

std::vector<std::string> & Directory::getDir()
{
	return v;
}

Directory::~Directory(){}
