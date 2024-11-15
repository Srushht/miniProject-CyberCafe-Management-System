#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <iomanip>
using namespace std;

// User class representing a cyber cafe user
class User {
private:
    string name;
    int computerNumber;
    time_t loginTime;
    time_t logoutTime;
    double chargePerHour;
    bool isLoggedIn;

public:
    // Constructor to initialize a user
    User(string n, int compNo, double rate) {
        name = n;
        computerNumber = compNo;
        chargePerHour = rate;
        isLoggedIn = false;
    }

    // Getter for the user's name
    string getName() {
        return name;
    }

    // Method to log in a user
    void login() {
        if (!isLoggedIn) {
            loginTime = time(0);  // Get current time
            isLoggedIn = true;
            cout << "User " << name << " logged in at " << ctime(&loginTime);
        } else {
            cout << "User " << name << " is already logged in.\n";
        }
    }

    // Method to log out a user
    void logout() {
        if (isLoggedIn) {
            logoutTime = time(0);  // Get current time
            isLoggedIn = false;
            cout << "User " << name << " logged out at " << ctime(&logoutTime);
        } else {
            cout << "User " << name << " is not logged in.\n";
        }
    }

    // Calculate total time spent in hours
    double calculateHours() {
        if (!isLoggedIn) {
            double hours = difftime(logoutTime, loginTime) / 3600;  // Convert seconds to hours
            return hours;
        }
        return 0.0;
    }

    // Calculate total charges based on hours used
    double calculateCharges() {
        return calculateHours() * chargePerHour;
    }

    // Method to display user details
    void displayDetails() {
        cout << "User Name: " << name << endl;
        cout << "Computer Number: " << computerNumber << endl;
        cout << "Total Time Used: " << fixed << setprecision(2) << calculateHours() << " hours" << endl;
        cout << "Total Charges: $" << calculateCharges() << endl;
    }

    // Method to save user data to a file
    void saveUserToFile(ofstream& outFile) {
        outFile << name << " " << computerNumber << " " << calculateHours() << " " << calculateCharges() << endl;
    }
};

// CyberCafe class to manage multiple users
class CyberCafe {
private:
    User* users[10];  // Array to store up to 10 users
    int userCount;
    string adminPassword;

public:
    // Constructor to initialize the cyber cafe
    CyberCafe() {
        userCount = 0;
        adminPassword = "admin123";  // Default admin password
    }

    // Method for admin login
    bool adminLogin() {
        string password;
        cout << "Enter Admin Password: ";
        cin >> password;

        if (password == adminPassword) {
            cout << "Admin login successful.\n";
            return true;
        } else {
            cout << "Invalid password.\n";
            return false;
        }
    }

    // Method to add a user to the cafe
    void addUser(string name, int compNo, double rate) {
        if (userCount < 10) {
            users[userCount] = new User(name, compNo, rate);
            userCount++;
            cout << "User added successfully!\n";
        } else {
            cout << "Cafe is full. No more users can be added.\n";
        }
    }

    // Method to log in a user
    void loginUser(string name) {
        for (int i = 0; i < userCount; i++) {
            if (users[i]->getName() == name) {
                users[i]->login();
                return;
            }
        }
        cout << "User not found.\n";
    }

    // Method to log out a user
    void logoutUser(string name) {
        for (int i = 0; i < userCount; i++) {
            if (users[i]->getName() == name) {
                users[i]->logout();
                return;
            }
        }
        cout << "User not found.\n";
    }

    // Method to display all users
    void displayAllUsers() {
        if (userCount == 0) {
            cout << "No users to display.\n";
        } else {
            for (int i = 0; i < userCount; i++) {
                cout << "User " << (i + 1) << " Details: " << endl;
                users[i]->displayDetails();
                cout << "------------------------\n";
            }
        }
    }

    // Method to save all user data to a file
    void saveToFile() {
        ofstream outFile("userData.txt");
        if (outFile.is_open()) {
            for (int i = 0; i < userCount; i++) {
                users[i]->saveUserToFile(outFile);
            }
            outFile.close();
            cout << "User data saved to file successfully.\n";
        } else {
            cout << "Unable to open file.\n";
        }
    }

    // Destructor to free memory
    ~CyberCafe() {
        for (int i = 0; i < userCount; i++) {
            delete users[i];
        }
    }
};

// Main function
int main() {
    CyberCafe cafe;
    int choice;

    do {
        cout << "\nCyberCafe Management System\n";
        cout << "1. Admin Login\n";
        cout << "2. Add User\n";
        cout << "3. Log In User\n";
        cout << "4. Log Out User\n";
        cout << "5. Display All Users\n";
        cout << "6. Save Data\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            if (cafe.adminLogin()) {
                // Admin options can be extended here
            }
            break;
        case 2: {
            string name;
            int compNo;
            double rate;

            cout << "Enter user name: ";
            cin >> name;
            cout << "Enter computer number: ";
            cin >> compNo;
            cout << "Enter charge per hour: ";
            cin >> rate;

            cafe.addUser(name, compNo, rate);
            break;
        }
        case 3: {
            string name;
            cout << "Enter user name: ";
            cin >> name;
            cafe.loginUser(name);
            break;
        }
        case 4: {
            string name;
            cout << "Enter user name: ";
            cin >> name;
            cafe.logoutUser(name);
            break;
        }
        case 5:
            cafe.displayAllUsers();
            break;
        case 6:
            cafe.saveToFile();
            break;
        case 7:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 7);

    return 0;
}
