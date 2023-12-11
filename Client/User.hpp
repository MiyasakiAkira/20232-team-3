#ifndef USER_HPP_
#define USER_HPP_

#include"Client.hpp"
#include"../Product/Game.hpp"
#include<vector>

class User: public Client
{
private:
    std::vector<Game> _library;
    std::vector<Game> _wishlist;
public:
    User(std::string _username, std::string _password, std::string _email, std::string _cpf, double balance, std::vector<Game> _library, std::vector<Game> _wishlist);
    virtual void menu();

    void buy_game(std::string gameName, std::string username);
    void print_wishlist();
    void print_library();
    void add_to_wishlist(std::string gameName, std::string username);

};

#endif // USER_HPP_