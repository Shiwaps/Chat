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
        MenuOption("������������������", registerUser),
        MenuOption("��������������", loginUser),
        MenuOption("��������� ���������", sendMessage, false),
        MenuOption("�������� � ����� ���", writeInChat, false),
        MenuOption("����������� ��� ���������", viewUserMessages, false),
        MenuOption("���������� ����� ���", displayChatLog, false),
        MenuOption("����� �� ��������", exitAccount, false),
        MenuOption("����� �� ���������", exitProgram, false)
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
            cout << "������� ���� �����: ";
            cin >> choice;

            if (cin.fail() || choice < 1 || choice > menuOptions.size() || !menuOptions[choice - 1].available) {
                cout << "\n\t\t\t������! �������� �����. ����������, ���������� �����." << endl;
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
