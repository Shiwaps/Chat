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
    std::cout << "Введите имя пользователя: ";
    std::cin >> username;
    std::cout << "Введите пароль: ";
    std::cin >> password;

    User newUser(username, password);
    users.push_back(newUser);

    std::cout << "Регистрация прошла успешно. Теперь вы можете войти в систему." << std::endl;
}

void loginUser() {
    std::string username, password;
    std::cout << "Введите имя пользователя: ";
    std::cin >> username;
    std::cout << "Введите пароль: ";
    std::cin >> password;

    for (User& user : users)
    {
        if (user.username == username && user.authenticate(password))
        {
            currentUser = &user;
            std::cout << "Вход в систему выполнен успешно. Добро пожаловать, " << currentUser->username << "!" << std::endl;
            return;
        }
    }

    std::cout << "Неверные учетные данные. Пожалуйста, попробуйте снова." << std::endl;
}

void sendMessage() {
    if (!currentUser)
    {
        std::cout << "Пожалуйста, войдите в систему или зарегистрируйтесь для отправки сообщений." << std::endl;
        return;
    }

    std::string receiverName, message;
    std::cout << "Введите имя получателя: ";
    std::cin >> receiverName;

    std::cout << "Введите ваше сообщение: ";
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
        std::cout << "Сообщение отправлено пользователю " << receiverName << ": " << message << std::endl;
    }
    else
    {
        std::cout << "Пользователь не найден." << std::endl;
    }
}

void writeInChat() {
    if (!currentUser)
    {
        std::cout << "Пожалуйста, войдите в систему или зарегистрируйтесь для отправки сообщений." << std::endl;
        return;
    }

    std::string message;
    std::cout << "Введите ваше сообщение для общего чата: ";
    std::cin.ignore();
    getline(std::cin, message);

    chatLog.push_back(currentUser->username + " -> Общий чат: " + message);
    std::cout << "Сообщение отправлено в общий чат." << std::endl;
}

void viewUserMessages() {
    if (!currentUser)
    {
        std::cout << "Пожалуйста, войдите в систему или зарегистрируйтесь для просмотра сообщений." << std::endl;
        return;
    }

    while (true)
    {
        clearScreen();
        std::cout << "Сообщения пользователя " << currentUser->username << ":" << std::endl;
        std::cout << "1. Отправленные сообщения:" << std::endl;
        for (const std::string& message : currentUser->sentMessages)
        {
            std::cout << "- " << message << std::endl;
        }
        std::cout << "2. Полученные сообщения:" << std::endl;
        for (const std::string& message : currentUser->receivedMessages)
        {
            std::cout << "- " << message << std::endl;
        }
        std::cout << std::endl;

        std::cout << "Введите 0 для возврата в главное меню: ";
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
            std::cout << "Общий чат пока пуст." << std::endl;
        }
        else
        {
            std::cout << "Общий чат:" << std::endl;
            for (const std::string& message : chatLog)
            {
                std::cout << message << std::endl;
            }
            std::cout << std::endl;
        }

        std::cout << "Введите 0 для возврата в главное меню: ";
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
        std::cout << "Вы успешно вышли из аккаунта." << std::endl;
    }
    else
    {
        std::cout << "Вы не вошли в аккаунт." << std::endl;
    }
}

void exitProgram()
{
    std::cout << "До свидания!" << std::endl;
    exit(0);
}
