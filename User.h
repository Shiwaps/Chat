#ifndef USER_H
#define USER_H

#include <string>
#include <vector>

class User {
public:
    std::string username;
    std::string password;
    std::vector<std::string> sentMessages;
    std::vector<std::string> receivedMessages;

    User(std::string _username, std::string _password);

    bool authenticate(std::string inputPassword);

    void sendMessage(std::string message, User& receiver);
};

#endif 
