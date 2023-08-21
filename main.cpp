#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <thread>

using namespace std;

struct User
{
    string username;
    string password;
    vector<string> sentMessages;
    vector<string> receivedMessages;

    User(string username, string password) : username(username), password(password) {}

    bool authenticate(string inputPassword)
    {
        return password == inputPassword;
    }

    void sendMessage(string message, User& receiver)
    {
        sentMessages.push_back("Вы -> " + receiver.username + ": " + message);
        receiver.receivedMessages.push_back(username + " -> Вам: " + message);
    }
};

vector<User> users;
User* currentUser = nullptr;
vector<string> chatLog;

struct MenuOption
{
    string text;
    void (*action)();
    bool available;

    MenuOption(string _text, void (*_action)(), bool _available = true)
        : text(_text), action(_action), available(_available) {}


};

void clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void printChatLogo()
{
    clearScreen();
    cout << "\t\t\t\t  CCCCC  H     H    A    TTTTTTT" << endl;
    cout << "\t\t\t\t C       H     H   A A      T  " << endl;
    cout << "\t\t\t\t C       HHHHHHH  AAAAA     T  " << endl;
    cout << "\t\t\t\t C       H     H A     A    T  " << endl;
    cout << "\t\t\t\t  CCCCC  H     H A     A    T  " << endl;
}

void registerUser()
{
    string username, password;
    cout << "Введите имя пользователя: ";
    cin >> username;
    cout << "Введите пароль: ";
    cin >> password;

    User newUser(username, password);
    users.push_back(newUser);

    cout << "Регистрация прошла успешно. Теперь вы можете войти в систему." << endl;
}

void loginUser()
{
    string username, password;
    cout << "Введите имя пользователя: ";
    cin >> username;
    cout << "Введите пароль: ";
    cin >> password;

    for (User& user : users)
    {
        if (user.username == username && user.authenticate(password))
        {
            currentUser = &user;
            cout << "Вход в систему выполнен успешно. Добро пожаловать, " << currentUser->username << "!" << endl;
            return;
        }
    }

    cout << "Неверные учетные данные. Пожалуйста, попробуйте снова." << endl;
}

void sendMessage()
{
    if (!currentUser)
    {
        cout << "Пожалуйста, войдите в систему или зарегистрируйтесь для отправки сообщений." << endl;
        return;
    }

    string receiverName, message;
    cout << "Введите имя получателя: ";
    cin >> receiverName;

    cout << "Введите ваше сообщение: ";
    cin.ignore();
    getline(cin, message);

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
        cout << "Сообщение отправлено пользователю " << receiverName << ": " << message << endl;
    }
    else
    {
        cout << "Пользователь не найден." << endl;
    }
}


void writeInChat()
{
    if (!currentUser)
    {
        cout << "Пожалуйста, войдите в систему или зарегистрируйтесь для отправки сообщений." << endl;
        return;
    }

    string message;
    cout << "Введите ваше сообщение для общего чата: ";
    cin.ignore();
    getline(cin, message);

    chatLog.push_back(currentUser->username + " -> Общий чат: " + message);
    cout << "Сообщение отправлено в общий чат." << endl;
}

void viewUserMessages()
{
    if (!currentUser)
    {
        cout << "Пожалуйста, войдите в систему или зарегистрируйтесь для просмотра сообщений." << endl;
        return;
    }

    while (true)
    {
        clearScreen();
        cout << "Сообщения пользователя " << currentUser->username << ":" << endl;
        cout << "1. Отправленные сообщения:" << endl;
        for (const string& message : currentUser->sentMessages)
        {
            cout << "- " << message << endl;
        }
        cout << "2. Полученные сообщения:" << endl;
        for (const string& message : currentUser->receivedMessages)
        {
            cout << "- " << message << endl;
        }
        cout << endl;

        cout << "Введите 0 для возврата в главное меню: ";
        int choice;
        cin >> choice;

        if (choice == 0)
        {
            break;
        }
    }
}


void displayChatLog()
{
    while (true)
    {
        clearScreen();
        if (chatLog.empty())
        {
            cout << "Общий чат пока пуст." << endl;
        }
        else
        {
            cout << "Общий чат:" << endl;
            for (const string& message : chatLog)
            {
                cout << message << endl;
            }
            cout << endl;
        }

        cout << "Введите 0 для возврата в главное меню: ";
        int choice;
        cin >> choice;

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
        cout << "Вы успешно вышли из аккаунта." << endl;
    }
    else
    {
        cout << "Вы не вошли в аккаунт." << endl;
    }
}

void exitProgram()
{
    cout << "До свидания!" << endl;
    exit(0);
}

int main()
{
    setlocale(LC_ALL, "rus");

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

    while (true)
    {
        if (currentUser && menuOptions[4].available)
        {
        }
        else
        {
            clearScreen();
        }

        printChatLogo();

        if (currentUser)
        {
            menuOptions[0].available = false;
            menuOptions[1].available = false;
            menuOptions[6].available = menuOptions[7].available = true;
            menuOptions[2].available = menuOptions[3].available = menuOptions[5].available = true;
            menuOptions[4].available = menuOptions[5].available = true;
        }
        else
        {
            menuOptions[0].available = menuOptions[1].available = true;
            menuOptions[6].available = menuOptions[7].available = false;
            menuOptions[2].available = menuOptions[3].available = menuOptions[4].available = menuOptions[5].available = false;
            menuOptions[4].available = menuOptions[5].available = false;
        }

        for (size_t i = 0; i < menuOptions.size(); ++i)
        {
            if (menuOptions[i].available)
            {
                cout << " " << i + 1 << ". " << menuOptions[i].text << endl;
            }
        }

        int choice = 0;
        bool validChoice = false;
        while (!validChoice)
        {
            cout << "Введите свой выбор: ";
            cin >> choice;

            if (cin.fail() || choice < 1 || choice > menuOptions.size() || !menuOptions[choice - 1].available)
            {
                cout << "\n\t\t\tОшибка! Неверный выбор. Пожалуйста, попробуйте снова." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            else
            {
                validChoice = true;
            }
        }

        menuOptions[choice - 1].action();

        this_thread::sleep_for(chrono::seconds(2));
        clearScreen();
    }

    return 0;
}
