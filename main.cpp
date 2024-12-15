#include <iostream>
#include <string>
#include <fstream>
using namespace std;

// Constants and array limits
const int MAX_USERS = 5;
const int MAX_ATTEMPTS = 3;

// User and admin data
string userdata[MAX_USERS][2] = {{"user1", "pass123"}}; // 2D array to store usernames and passwords
double account_balance[MAX_USERS]; // Array to store account balances for users
string loggedInUserType; // To track user or admin
int userCount = 1; // Start with 1 user account

// Function declarations
bool login(string userdata[MAX_USERS][2], int &userCount, string admindata[1][2], string &loggedInUserType, double account_balance[MAX_USERS]);
void newAccount(string userdata[MAX_USERS][2], int &userCount, double account_balance[MAX_USERS]);
void displayMainMenu();
void displayMainOptions();
void handleUserInput(char option, string userdata[MAX_USERS][2], int &userCount, string loggedInUserType, double account_balance[MAX_USERS]);
void userMenu(double account_balance[MAX_USERS], int userCount, string userdata[MAX_USERS][2]);
void adminMenu(string userdata[MAX_USERS][2], int &userCount, double account_balance[MAX_USERS]);
bool isValidUser(string userdata[MAX_USERS][2], int userCount, string username, string password);
void payBill(string usernames[MAX_USERS][2], double balances[], int size, string username);
void transferMoney(string usernames[MAX_USERS][2], double balances[], int size, string username);

// Main function
int main() {
    string admindata[1][2] = {{"admin", "admin123"}}; // Admin login data
    bool isLoggedIn = false;
    string loggedInUserType; // To track if the user is a regular user or admin

    // Main menu display
    displayMainMenu();

    // Prompt user for login or account creation
    displayMainOptions();
        char choice;

    do{
	   cout<<"Enter Your choice : " ;
       cin >> choice;
    }while(!(choice == 'A' || choice == 'a'||choice == 'b' || choice == ' B'));
    
    if (choice == 'A' || choice == 'a') {
        newAccount(userdata, userCount, account_balance); // Add new account
    }

    
    bool checkl = login(userdata, userCount, admindata, loggedInUserType, account_balance);

    if (checkl){
	
        do {
        	
            cout << endl << "1 for User Menu\n2 for Admin Menu (Only accessible by Admin)\n3 to Exit" << endl;
            cout << "Enter Your Option: ";
            cin >> choice;

            handleUserInput(choice, userdata, userCount, loggedInUserType, account_balance);

        } while (true);
    } else {
        cout << "Invalid login. Exiting program." << endl;
    }

    return 0;
}

// Display the main menu
void displayMainMenu() {
    cout << "\t\t\t<<<<<<<<< WELCOME TO THE BANKING MAIN MENU >>>>>>>";
    cout << endl << endl;
}

// Display the main options (new account or login)
void displayMainOptions() {
    cout << "\nA for new user\nB for login" << endl;
}

// Login function
bool login(string userdata[MAX_USERS][2], int &userCount, string admindata[1][2], string &loggedInUserType, double account_balance[MAX_USERS]) {
    string username, password;
    int attempts = MAX_ATTEMPTS;
    char userType;

    cout << "Enter 'U' for user login or 'A' for admin login: ";
    cin >> userType;

    if (userType == 'U' || userType == 'u') {
        while (attempts > 0) {
            cout << "Enter your username: ";
            cin >> username;
            int n;
            cin>>n;
            char arr[n];
            cout << "Enter your password: ";
            cin >> password;
            int count =0 ;
            for(int i = 0 ; i<n; i++){
            cin>>arr[i];
            count++;
			}
cout<<"Number of count : "<<count;
            if (isValidUser(userdata, userCount, username, password)) {
                loggedInUserType = "user";
                cout << "\nLogin successful!" << endl;
                return true;
            }

            attempts--;
            cout << "Invalid credentials. Attempts left: " << attempts << endl;

            if (attempts == 0) return false;
        }
    } else if (userType == 'A' || userType == 'a') {
        while (attempts > 0) {
            cout << "Enter your username: ";
            cin >> username;
            cout << "Enter your password: ";
            cin >> password;

            if (username == admindata[0][0] && password == admindata[0][1]) {
                loggedInUserType = "admin";
                cout << "\nAdmin login successful!" << endl;
                return true;
            } else {
                attempts--;
                cout << "Invalid admin credentials. Attempts left: " << attempts << endl;
            }

            if (attempts == 0) return false;
        }
    } else {
        cout << "Invalid option!" << endl;
        return false;
    }

    return false;
}

// Function to check if the user is valid
bool isValidUser(string userdata[MAX_USERS][2], int userCount, string username, string password) {
	int count =0 ;

    for (int i = 0; i < userCount; i++) {
        if (userdata[i][0] == username && userdata[i][1] == password) {
        	
        	
            return true;
        }
    }
    return false;
}

// Create a new account
void newAccount(string userdata[MAX_USERS][2], int &userCount, double account_balance[MAX_USERS]) {
    string username, password;

    if (userCount >= MAX_USERS) {
        cout << "Maximum users reached. Cannot create a new account." << endl;
        return;
    }

    cout << "Enter username for the new account: ";
    cin.ignore();
    getline(cin, username);

    for (int i = 0; i < userCount; i++) {
        if (userdata[i][0] == username) {
            cout << "Username already exists. Please choose another one." << endl;
            return;
        }
    }

    cout << "Enter password for the new account: ";
    getline(cin, password);

    userdata[userCount][0] = username;
    userdata[userCount][1] = password;
    account_balance[userCount] = 0;
    userCount++;

    cout << "Account created successfully!" << endl;
}

// Handle user input for different options
void handleUserInput(char option, string userdata[MAX_USERS][2], int &userCount, string loggedInUserType, double account_balance[MAX_USERS]) {
    switch (option) {
        case '1':
            userMenu(account_balance, userCount, userdata);
            break;
        case '2':
            if (loggedInUserType == "admin") {
                adminMenu(userdata, userCount, account_balance);  
            } else {
                cout << "Only admins can access this menu." << endl;
            }
            break;
        case '3':
            cout << "Exiting the program..." << endl;
            exit(0);
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
    }
}

// User menu with options 
void userMenu(double account_balance[MAX_USERS], int userCount, string userdata[MAX_USERS][2]) {
    int choice;
    string username;
    int userIndex = -1;

    cout << "\n-- User Menu --" << endl;
    cout << "Enter your username: ";
    cin >> username;

    for (int i = 0; i < userCount; i++) {
        if (userdata[i][0] == username) {
            userIndex = i;
            break;
        }
    }

    if (userIndex == -1) {
        cout << "User not found. Exiting." << endl;
        return;
    }

    do {
        cout << "\n1. Deposit Money\n2. Withdraw Money\n3. Check Balance\n4. Pay Bill\n5. Transfer Money\n6. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                double depositAmount;
                cout << "Enter amount to deposit: ";
                cin >> depositAmount;
                if (depositAmount > 0) {
                    account_balance[userIndex] += depositAmount;
                    cout << "Deposited " << depositAmount << ". New balance: " << account_balance[userIndex] << endl;
                } else {
                    cout << "Invalid deposit amount." << endl;
                }
                break;
            }
            case 2: {
                double withdrawAmount;
                cout << "Enter amount to withdraw: ";
                cin >> withdrawAmount;
                if (withdrawAmount > 0 && withdrawAmount <= account_balance[userIndex]) {
                    account_balance[userIndex] -= withdrawAmount;
                    cout << "Withdrew " << withdrawAmount << ". New balance: " << account_balance[userIndex] << endl;
                } else {
                    cout << "Insufficient funds or invalid amount." << endl;
                }
                break;
            }
            case 3:
                cout << "Your current balance: " << account_balance[userIndex] << endl;
                break;
            case 4:
                payBill(userdata, account_balance, userCount, username);
                break;
            case 5:
                transferMoney(userdata, account_balance, userCount, username);
                break;
            case 6:
                cout << "Exiting the user menu..." << endl;
                return;
            default:
                cout << "Invalid choice." << endl;
                break;
        }
    } while (true);
}

// Admin menu 
void adminMenu(string userdata[MAX_USERS][2], int &userCount, double account_balance[MAX_USERS]) {
    int choice;

    cout << "\n-- Admin Menu --" << endl;
    do {
        cout << "\n1. View Users\n2. View User Balances\n3. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "User List: " << endl;
                for (int i = 0; i < userCount; i++) {
                    cout << "Username: " << userdata[i][0] << endl;
                }
                break;
            case 2:
                cout << "User Balances: " << endl;
                for (int i = 0; i < userCount; i++) {
                    cout << "Username: " << userdata[i][0] << ", Balance: " << account_balance[i] << endl;
                }
                break;
            case 3:
                cout << "Exiting admin menu..." << endl;
                return;
            default:
                cout << "Invalid choice." << endl;
                break;
        }
    } while (true);
}

// Pay bill function
void payBill(string usernames[MAX_USERS][2], double balances[], int userCount, string username) {
    int userIndex = -1;

    // Find the index of the logged-in user
    for (int i = 0; i < userCount; i++) {
        if (usernames[i][0] == username) {
            userIndex = i;
            break;
        }
    }

    if (userIndex == -1) {
        cout << "User not found." << endl;
        return;
    }

    double amount;
    cout << "Enter bill payment amount: ";
    cin >> amount;

    // Check if sufficient balance exists
    if (balances[userIndex] >= amount) {
        balances[userIndex] -= amount;
        cout << "Bill paid successfully. New balance: " << balances[userIndex] << endl;
    } else {
        cout << "Insufficient funds." << endl;
    }
}

// Transfer money function
void transferMoney(string usernames[MAX_USERS][2], double balances[], int userCount, string username) {
    int senderIndex = -1, recipientIndex = -1;
    double amount;

    // Find the index of the sender (current user)
    for (int i = 0; i < userCount; i++) {
        if (usernames[i][0] == username) {
            senderIndex = i;
            break;
        }
    }

    if (senderIndex == -1) {
        cout << "Sender not found." << endl;
        return;
    }

    string recipient;
    cout << "Enter recipient's username: ";
    cin >> recipient;

    // Find the recipient's index
    for (int i = 0; i < userCount; i++) {
        if (usernames[i][0] == recipient) {
            recipientIndex = i;
            break;
        }
    }

    if (recipientIndex == -1) {
        cout << "Recipient not found." << endl;
        return;
    }

    // Get the amount to transfer
    cout << "Enter amount to transfer: ";
    cin >> amount;

    // Check if the sender has enough balance for the transfer
    if (balances[senderIndex] >= amount) {
        balances[senderIndex] -= amount;  // Deduct from sender
        balances[recipientIndex] += amount;  // Add to recipient
        cout << "Transfer successful." << endl;
        cout << "New balance for " << usernames[senderIndex][0] << ": " << balances[senderIndex] << endl;
        cout << "New balance for " << usernames[recipientIndex][0] << ": " << balances[recipientIndex] << endl;
    } else {
        cout << "Insufficient funds for the transfer." << endl;
    }
}
