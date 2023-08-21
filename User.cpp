#include "User.h"

User::User(std::string _username, std::string _password) : username(_username), password(_password) {}

bool User::authenticate(std::string inputPassword) {
    return password == inputPassword;
}

void User::sendMessage(std::string message, User& receiver) {
    sentMessages.push_back("�� -> " + receiver.username + ": " + message);
    receiver.receivedMessages.push_back(username + " -> ���: " + message);
}
