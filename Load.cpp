
# include "Load.hpp"

Load::Load(Request * r, int f, std::string & url, srv & serv) : rq(r), fd(f), _url(url), server(serv)
{
}


bool    Load::createFile()
{
    std::string path = _url + "/" + rq->getUpFileName();

    std::ofstream file(path.c_str(), std::ios::out | std::ios::binary);

    if (file.is_open())
    {
        file << rq->getUpFileContent();
        file.close();
    }
    else
        return (Error(500, fd, server), false);
    
    if (file.fail())
        return (Error(500, fd, server), false);

    return true;
}

Load::~Load(){}

