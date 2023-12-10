#include "ClientDB.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

ClientDB::ClientDB(std::string path)
{
    _path = path;
}

bool ClientDB::exist_userName(std::string &username)
{
    std::ifstream arquivo(_path);
    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir o arquivo JSON.1" << std::endl;
        return false;
    }

    json dadosJSON;
    arquivo >> dadosJSON;
    arquivo.close();

    if (dadosJSON.is_array()) {
        for (const auto& data : dadosJSON) {
            std::string usernameJSON = data["Username"];

            // Verifique se o nome e o usuário correspondem aos fornecidos
            if (usernameJSON == username) {
                return true;
            }
        }
    }
    return false;
}


void ClientDB::edit_info(Developer* dev)
{
    int aux;
    std::string tempUsername;
    std::cout << "O que deseja alterar?\n1 - Username;\n2 - Password;\n3 - Email;\n4 - CPF;\n5 - Voltar\n";
    std::cin >> aux;
    switch (aux)
    {
        case 1:
            while (true)
            {
                std::cout << "Digite seu nome de usuário: ";
                std::cin >> tempUsername;
                if(tempUsername.size() > 30)
                {
                    std::cout << "Nome de usuário muito grande, digite novamente\n";
                }
                else
                {
                    if(exist_userName(tempUsername))
                    {
                        std::cout << "Nome de usuário já existente, digite novamente\n";
                    }
                    else
                    {
                        dev->set_username(tempUsername);

                        std::ifstream arquivo(_path);
                        if (!arquivo.is_open()) {
                            std::cerr << "Erro ao abrir o arquivo JSON." << std::endl;
                        }

                        json dadosJSON;
                        arquivo >> dadosJSON;
                        arquivo.close();

                        if (dadosJSON.is_array()) {
                            for (auto& data : dadosJSON) {
                                std::string usernameJSON = data["Username"];

                                // Verifique se o nome e o usuário correspondem aos fornecidos
                                if (usernameJSON == dev->get_username()) {
                                    data["Username"] = tempUsername;
                                }
                            }
                        }

                        break;
                    }

                }
            }
            






            break;
        
    }
}