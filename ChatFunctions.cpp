#include "ChatFunctions.h"
#include "User.h"
#include "MenuOption.h"

#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <windows.h>

extern std::vector<User> users;
extern User* currentUser;
extern std::vector<std::string> chatLog;

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void printChatLogo() {
    clearScreen();
    std::cout << "\t\t\t\t  CCCCC  H     H    A    TTTTTTT" << std::endl;
    std::cout << "\t\t\t\t C       H     H   A A      T  " << std::endl;
    std::cout << "\t\t\t\t C       HHHHHHH  AAAAA     T  " << std::endl;
    std::cout << "\t\t\t\t C       H     H A     A    T  " << std::endl;
    std::cout << "\t\t\t\t  CCCCC  H     H A     A    T  " << std::endl;
}

void registerUser() {
    std::string username, password;
    std::cout << "������� ��� ������������: ";
    std::cin >> username;
    std::cout << "������� ������: ";
    std::cin >> password;

    User newUser(username, password);
    users.push_back(newUser);

    std::cout << "����������� ������ �������. ������ �� ������ ����� � �������." << std::endl;
}

void loginUser() {
    std::string username, password;
    std::cout << "������� ��� ������������: ";
    std::cin >> username;
    std::cout << "������� ������: ";
    std::cin >> password;

    for (User& user : users)
    {
        if (user.username == username && user.authenticate(password))
        {
            currentUser = &user;
            std::cout << "���� � ������� �������� �������. ����� ����������, " << currentUser->username << "!" << std::endl;
            return;
        }
    }

    std::cout << "�������� ������� ������. ����������, ���������� �����." << std::endl;
}

void sendMessage() {
    if (!currentUser)
    {
        std::cout << "����������, ������� � ������� ��� ����������������� ��� �������� ���������." << std::endl;
        return;
    }

    std::string receiverName, message;
    std::cout << "������� ��� ����������: ";
    std::cin >> receiverName;

    std::cout << "������� ���� ���������: ";
    std::cin.ignore();
    getline(std::cin, message);

    User* receiverUser = nullptr;
    for (User& user : users)
    {
        if (user.username == receiverName)
        {
            receiverUser = &user;
            break;
        }
    }

    if (receiverUser)
    {
        currentUser->sendMessage(message, *receiverUser);
        std::cout << "��������� ���������� ������������ " << receiverName << ": " << message << std::endl;
    }
    else
    {
        std::cout << "������������ �� ������." << std::endl;
    }
}

void writeInChat() {
    if (!currentUser)
    {
        std::cout << "����������, ������� � ������� ��� ����������������� ��� �������� ���������." << std::endl;
        return;
    }

    std::string message;
    std::cout << "������� ���� ��������� ��� ������ ����: ";
    std::cin.ignore();
    getline(std::cin, message);

    chatLog.push_back(currentUser->username + " -> ����� ���: " + message);
    std::cout << "��������� ���������� � ����� ���." << std::endl;
}

void viewUserMessages() {
    if (!currentUser)
    {
        std::cout << "����������, ������� � ������� ��� ����������������� ��� ��������� ���������." << std::endl;
        return;
    }

    while (true)
    {
        clearScreen();
        std::cout << "��������� ������������ " << currentUser->username << ":" << std::endl;
        std::cout << "1. ������������ ���������:" << std::endl;
        for (const std::string& message : currentUser->sentMessages)
        {
            std::cout << "- " << message << std::endl;
        }
        std::cout << "2. ���������� ���������:" << std::endl;
        for (const std::string& message : currentUser->receivedMessages)
        {
            std::cout << "- " << message << std::endl;
        }
        std::cout << std::endl;

        std::cout << "������� 0 ��� �������� � ������� ����: ";
        int choice;
        std::cin >> choice;

        if (choice == 0)
        {
            break;
        }
    }
}

void displayChatLog() {
    while (true)
    {
        clearScreen();
        if (chatLog.empty())
        {
            std::cout << "����� ��� ���� ����." << std::endl;
        }
        else
        {
            std::cout << "����� ���:" << std::endl;
            for (const std::string& message : chatLog)
            {
                std::cout << message << std::endl;
            }
            std::cout << std::endl;
        }

        std::cout << "������� 0 ��� �������� � ������� ����: ";
        int choice;
        std::cin >> choice;

        if (choice == 0)
        {
            break;
        }
    }
}

void exitAccount()
{
    if (currentUser)
    {
        currentUser = nullptr;
        std::cout << "�� ������� ����� �� ��������." << std::endl;
    }
    else
    {
        std::cout << "�� �� ����� � �������." << std::endl;
    }
}

void exitProgram()
{
    std::cout << "�� ��������!" << std::endl;
    exit(0);
}
