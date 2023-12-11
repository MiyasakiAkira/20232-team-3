#ifndef USER_HPP_
#define USER_HPP_

#include"Client.hpp"
#include<vector>

class User: public Client
{
private:
    //std::vector<Game> _library;
    //std::vector<Game> _wishlist;
public:
    User(std::string _username, std::string _password, std::string _email, std::string _cpf, double balance);
    virtual void menu();
};

#endif // USER_HPP_