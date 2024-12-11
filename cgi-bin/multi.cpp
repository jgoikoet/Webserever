
# include <sstream>
# include <iostream>
# include <unistd.h>
# include <stdlib.h>
int toInt(const std::string &str)
{
    std::stringstream ss(str);
    int num;
    ss >> num;
    return (num);
}

std::string getStdInput()
{
    std::string numero;
    std::getline(std::cin, numero);
    return numero;
}

void    sendResult(int n)
{
	
	std::cout << n << std::endl;
	
}

int main ()
{
    //std::cerr << "Buenas tarde biesvenido al marasvilloso mundos de las magia" << std::endl;
    std::string number;

    if (getenv("QUERY_STRING"))
	{
		//std::cerr << std::endl << "*******GET**********" << std::endl;
        number =  getenv("QUERY_STRING");
	}
    else
	{
		//std::cerr << std::endl << "*******POST**********" << std::endl;
        number = getStdInput();
	}

    //std::cerr << std::endl << "QUERY_STRING en cgi = " << number << std::endl;
    //std::cerr << std::endl << "Resultado = " << toInt(number) * 2 << std::endl;
	sendResult(toInt(number) * 2);

    return 0;
}