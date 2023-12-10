#include"User.hpp"
#include "../Data_manage/Database.hpp"

User::User(std::string _username, std::string _password, std::string _email, std::string _cpf, double balance, std::vector<Game> _library, std::vector<Game> _wishlist): Client(_username, _password, _email, _cpf, balance, 1)
{
    _library = _library;
    _wishlist = _wishlist;
}

void User::buy_game(Game game)
{ 
    if(stoi(game.get_price()) > this->_balance)
        std::cout << "Saldo insuficiente\n";
    else if(stoi(game.get_ageRating()) > get_age())
        std::cout << "Você não possui idade suficiente para comprar esse jogo\n";
    else
    {
        bool alreadyHave = false;
        for(auto e : this->_library)
        {
            if(e->get_name() == game.get_name())
                alreadyHave = true;
        }        
        
        if(!alreadyHave)
        {
            remove_from_wishlist(game);
            _balance -= stoi(game.get_price());
            this->_library->add_game(game);
            
        }
        else
            std::cout << "Você já possui esse jogo\n";     
    }
}
void User::add_to_wishlist(Game game)
{
    bool alreadyHave = false;
    for(auto e : this->_wishlist)
    {
        if(e->get_name() == game.get_name())
            alreadyHave = true;
    }

    for(auto e : this->_library)
    {
        if(e->get_name() == game.get_name())
            alreadyHave = true;
    }

    if(!alreadyHave)
        _wishlist.push_back(game);
    else
        std::cout << "Você já possui esse jogo na sua lista de desejos\n";
}

void User::remove_from_wishlist(Game game)
{
    Database::remove_from_wishlist(this->_username, game);
}

void User::menu()
{
    int aux;
    std::cout << "Bem vindo, " << _username << "!\n";
    INIT:
    std::cout << "O que deseja fazer?\n1-Ver/Alterar Dados;\n2-Ver/Adicionar Saldo;\n3-Ver biblioteca;\n4-Loja;\n5-Lista de desejos;\n6-Sair;\n";
    std::cin >> aux;
    switch (aux)
    {
    case 1:
        // Mostra os dados e pergunta se quer alterar alguns deles
        std::cout << "Nome de usuário: " << _username << '\n' << "Senha: " << _password << '\n' << "Email: " << _email << '\n' << "CPF: " << _cpf << '\n';
        std::cout << "Qual dado deseja alterar?\n1 - Nome de usuário;\n2 - Senha;\n3 - Email;\n4 - CPF;\n";
        std::cin >> aux;
        switch (aux)
        {
            case 1:
                std::cout << "Digite o novo nome de usuário: ";
                std::cin >> _username;
                // precisa fazer a verificação ainda
                
                break;

            case 2:
                std::cout << "Digite a nova senha: ";
                std::cin >> _password;
                break;
                // precisa fazer a verificação ainda

            case 3:
                std::cout << "Digite o novo email: ";
                std::cin >> _email;
                // precisa fazer a verificação ainda
                break;

            default:
                std::cout << "Digite o novo CPF: ";
                std::cin >> _cpf;
                // precisa fazer a verificação ainda
                break;        

        }
    case 2:
        std::cout << "Seu saldo é de: " << _balance << '\n';
        std::cout << "Deseja adicionar saldo?\n1 - Sim;\n2 - Não;\n";
        std::cin >> aux;
        switch (aux)
        {
            case 1:
                double deposit;
                std::cout << "Digite o valor que deseja adicionar: ";
                std::cin >> deposit; // verificar isso
                _balance += deposit;
                break; // vai 'verificar' se pagou mesmo?
        
            default:
                break;
        }

    case 3:
        for(int i = 0 ; i < _library.size() ; i++)
            std::cout << i+1 << " " << _library[i].get_name() << '\n';
        break;
    case 4:
        Database::show_games();
        // Pergunta se ele quer comprar um jogo e se quiser, faz a compra
        std::cout << "Deseja comprar algum jogo?\n1 - Sim;\n2 - Não;\n";
        std::cin >> aux;
        switch (aux)
        {
            case 1: CIN:
                int index;
                std::cout << "Digite o número do jogo que deseja comprar: ";
                std::cin >> index;
                
                if(check_index(index))
                {
                    // buy_game(_games[index]);
                    break;
                }

                else
                {
                    goto CIN;
                }
        
            default:
                break;
        }
        
    case 6:
        for(int i = 0 ; i < _wishlist.size() ; i++)
        {
            std::cout << i+1 << " " << _wishlist[i].get_name() << '\n';
        }
        // Pergunta se ele quer comprar um jogo e se quiser, faz a compra (Quando comprar, tira da wishlist)
        std:: cout << "Deseja comprar algum jogo da sua lista de desejos?\n1 - Sim;\n2 - Não;\n";
        std::cin >> aux;
        switch (aux)
        {
            case 1: CIN:
                int index;
                std::cout << "Digite o número do jogo que deseja comprar: ";
                std::cin >> index; // verificar isso
                if(check_index(index))
                {
                    buy_game(this->_wishlist[index]);
                    remove_from_wishlist(this->_wishlist[index-1]);
                    break;
                }

                else
                {
                    goto CIN;
                }
            default:
                break;
        
        case 7:        
        std::cout << "Obrigado por usar a Steam!\n";             
            
        }
        // Pergunta se ele quer remover um jogo da lista de desejos e se quiser, remove
        for(int i = 0 ; i < _wishlist.size() ; i++)
        {
            std::cout << i+1 << " " << _wishlist[i].get_name() << '\n';
        }
        std::cout << "Deseja remover algum jogo da sua lista de desejos?\n1 - Sim;\n2 - Não;\n";
        std::cin >> aux;
        switch (aux)
        {
            case 1: CIN:
                int index;
                std::cout << "Digite o número do jogo que deseja remover: ";
                std::cin >> index; // verificar isso
                if(check_index(index))
                {
                    remove_from_wishlist(_wishlist[index-1]);
                    break;
                }

                else
                {
                    goto CIN;
                }
        
            default:
                break;
        }
        
    default:
        break;
    }

    bool User::check_index(int index)
    {
        if(index < 0 || index > _wishlist.size())
        {
            throw std::invalid_argument("Invalid index");
            return false;
        }
        return true;    
    } 
}