#include <iostream>
#include <string>
#include <fstream>

struct userCredentials
{
    std::string username = "";
    std::string password = "";
};

void getAndStoreCredentials(const userCredentials& user)
{

    std::ofstream saveCredentials("Credentials.txt");
    if (!saveCredentials)
    {
        std::cout << "Error: Couldn't open file for saving credentials!\n";
        return;
    }

    saveCredentials << "Username: " << user.username << "\nPassword: " << user.password << "\n";
    saveCredentials.close();

    std::cout << "Credentials have been saved to 'Credentials.txt'.\n";
}

userCredentials getCredentials()
{
    userCredentials storeCredentials;

    std::cout << "Enter your username: ";
    std::cin >> storeCredentials.username;

    std::cout << "Enter your password: ";
    std::cin >> storeCredentials.password;

    return storeCredentials;
}

bool checkCredentials(const userCredentials& entered, const userCredentials& stored)
{
    return entered.username == stored.username && entered.password == stored.password;
}


int banksystem(const userCredentials& user)
{
    std::cout << "Welcome to your bank app! [" << user.username << "]";
    double balance = 0;
    
    while (true)
    {
        std::cout << "\nOptions: Deposit = D, Withdraw = W, Quit = Q: ";

        char choice;
        std::cin >> choice;
        if (std::toupper(choice) == 'D') // deposit
        {
            double amount;
            std::cout << "Enter the amount: ";
            if (!(std::cin >> amount))
            {
                std::cout << "Invalid input!\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }

            else
            {
                balance += amount;
                std::cout << "You have now $" << amount << " in the bank!\n";
            }
        }
       
        if (std::toupper(choice) == 'W')  //withdraw
        {
            double amount;
            std::cout << "Enter how much you want to withdraw: ";
            if (!(std::cin >> amount))
            {
                std::cout << "Invalid input!\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }

            else
            {

                if (amount <= balance)
                {
                    balance -= amount;
                    std::cout << "Withdrawn money: -$" << amount << '\n';
                }
                else
                {
                    std::cout << "Insufficient funds for your withdrawel!\n";
                }
            }

        }
        
        else if (std::toupper(choice) == 'Q') //quit
        {
            std::cout << "Okay Bye!\n";
            return 0;
        }

    }

    return 0;

}


int login()
{

    userCredentials storedCredentials;

    std::ifstream SavedCredentials("Credentials.txt");
    if (SavedCredentials.is_open())
    {
        std::string line;
        while (std::getline(SavedCredentials, line))
        {

            if (line.find("Username: ") == 0)
            {
                storedCredentials.username = line.substr(10);
            }
            else if (line.find("Password: ") == 0)
            {
                storedCredentials.password = line.substr(10);
            }
        }
        SavedCredentials.close();
    }

    while (true)
    {
        std::cout << "Choose options. Option 1. Sign in. Option 2. Sign up. Option 3. Quit: ";
        char choice;
        std::cin >> choice;

        if (choice == '1')
        {

            userCredentials signInCredentials = getCredentials();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            if (checkCredentials(signInCredentials, storedCredentials))
            {
                banksystem(signInCredentials);
            }
            else
            {
                std::cout << "Credentials not found in database!\n";
            }
        }

        else if (choice == '2')
        {

            userCredentials signUpCredentials = getCredentials();
            getAndStoreCredentials(signUpCredentials);
        }

        else if (choice == '3')
        {
            std::cout << "Bye!\n";
            return 0;
        }
    }

    return 0;
}


int main()
{
    login();
    return 0;
}
