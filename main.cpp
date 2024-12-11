/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoikoet <jgoikoet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 17:00:00 by jgoikoet          #+#    #+#             */
/*   Updated: 2024/09/10 12:23:53 by jgoikoet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Server.hpp"
# include "dependences.hpp"
# include "Config.hpp"



int main(int argc, char **argv)
{
    if (argc == 1)
    {
        std::cout << std::endl << YELLOW << "Configuration file not provided." << std::endl;
        std::cout << GREEN <<"Loading default configuration..."<< WHITE  << std::endl;
        Config confs("conf/default.conf");
        if (confs.getArrayOfServers().empty())
        {
            std::cout << RED << "Default configuration failed. Bye, bye." << WHITE << std::endl << std::endl;
            return (1);    
        }
        else
            Server server(confs.getArrayOfServers());
    }
    else if(argc == 2)
    {
        Config confs(argv[1]);
    
        if (confs.getArrayOfServers().empty())
        {
			std::cout << std::endl << RED << "Configuration file failed." << std::endl;
       		std::cout << GREEN <<"Loading default configuration..."<< WHITE  << std::endl;
			Config confsDef("conf/default.conf");
            if (confsDef.getArrayOfServers().empty())
       		{
            	std::cout << RED << "Default configuration failed. Bye, bye." << WHITE << std::endl << std::endl;
            	return (1);    
        	}
        	else
            	Server server(confsDef.getArrayOfServers());
        }
		else
			Server server(confs.getArrayOfServers());
	}
	else
	{
		std::cout << std::endl << RED << "Too much arguments melon. Bye, bye." << WHITE << std::endl << std::endl;
	}
    return (0);
}
