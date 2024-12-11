/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoikoet <jgoikoet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 18:08:45 by jgoikoet          #+#    #+#             */
/*   Updated: 2024/09/11 14:32:04 by jgoikoet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "dependences.hpp"
# include "Request.hpp"

# include "srv.hpp"
# include "Respons.hpp"

class Request;
class Respons;

class Server
{
    private:

        
        
        sockaddr_in	ad;
        int			id;
        int			sock;
        int			port;
        
        int			maxFD;
        int         sizeOfAddress;
        int         isServerSock;
        
        char		buffer[60000];
        std::string prueba;
        std::string bf;
        
        std::vector<int>    comFds;
        std::vector<srv>    servers;
		
        std::map<int, int>  serversMap; // clave = socket bindeado, valor = servidor
		std::map<int, int>  readMap; // clave = socket mensajero, valor = socket bindeado

		std::map <int, Request *> rq;


    public:

        Server(std::vector<srv> & srv);
        ~Server();
        
        void			respond(int i);
        void			Respond(int i);
        void			my_select();
        void            Mselect();
        void            serverSet();

		static int sign;
		static void	signalHandler(int i);

        void        setRequest(std::string & buf);

		//FUNCIONES PARA PRUEBAS
		void printRequest();
        void printServers();
};