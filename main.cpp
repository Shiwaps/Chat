#include "User.h"
#include "MenuOption.h"
#include "ChatFunctions.h"

#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <windows.h>

using namespace std;

vector<User> users;
User* currentUser = nullptr;
vector<string> chatLog;

int main() {
    setlocale(LC_ALL, "");
    SetConsoleCP(1251);

    vector<MenuOption> menuOptions =
    {
        MenuOption("Зарегистрироваться", registerUser),
        MenuOption("Авторизоваться", loginUser),
        MenuOption("Отправить сообщение", sendMessage, false),
        MenuOption("Написать в общий чат", writeInChat, false),
        MenuOption("Просмотреть мои сообщения", viewUserMessages, false),
        MenuOption("Отображать общий чат", displayChatLog, false),
        MenuOption("Выход из аккаунта", exitAccount, false),
        MenuOption("Выход из программы", exitProgram, false)
    };

    while (true) {
        if (currentUser && menuOptions[4].available) {
        }
        else {
            clearScreen();
        }

        printChatLogo();

        if (currentUser) {
            menuOptions[0].available = false;
            menuOptions[1].available = false;
            menuOptions[6].available = menuOptions[7].available = true;
            menuOptions[2].available = menuOptions[3].available = menuOptions[5].available = true;
            menuOptions[4].available = menuOptions[5].available = true;
        }
        else {
            menuOptions[0].available = menuOptions[1].available = true;
            menuOptions[6].available = menuOptions[7].available = false;
            menuOptions[2].available = menuOptions[3].available = menuOptions[4].available = menuOptions[5].available = false;
            menuOptions[4].available = menuOptions[5].available = false;
        }

        for (size_t i = 0; i < menuOptions.size(); ++i) {
            if (menuOptions[i].available) {
                cout << " " << i + 1 << ". " << menuOptions[i].text << endl;
            }
        }

        int choice = 0;
        bool validChoice = false;
        while (!validChoice) {
            cout << "Введите свой выбор: ";
            cin >> choice;

            if (cin.fail() || choice < 1 || choice > menuOptions.size() || !menuOptions[choice - 1].available) {
                cout << "\n\t\t\tОшибка! Неверный выбор. Пожалуйста, попробуйте снова." << endl;
                cin.clear();
                cin.ignore();
            }
            else {
                validChoice = true;
            }
        }

        menuOptions[choice - 1].action();

        this_thread::sleep_for(chrono::seconds(2));
        clearScreen();
    }

    return 0;
}
