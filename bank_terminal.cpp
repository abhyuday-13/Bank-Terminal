#include <chrono>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <string>
#include <thread>
#include <vector>

using namespace std;

#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define RESET "\033[0m"

class User {
  private:
	string name, username;
	int pin;
	double balance;

  public:
	User() {
		balance = 0.00;
	}

	User(string n, string u, int p, double b) : name(n), username(u), pin(p), balance(b) {}

	void setData(string n, string u, int p, double b) {
		name = n;
		username = u;
		pin = p;
		balance = b;
	}

	// Getter methods to access private members
	string getName() const { return name; }
	string getUsername() const { return username; }
	int getPin() const { return pin; }
	double getBalance() const { return balance; }

	// Setter for balance (used for deposit/withdraw)
	void setBalance(double b) {
		balance = b;
	}

	void saveToFile() const {
		ofstream fout("users.txt", ios::app);
		if (fout.is_open()) {
			fout << name << ',' << username << ',' << pin << ',' << balance << '\n';
			fout.close();
		} else {
			cout << "Error opening file to save user data.\n";
		}
	}

	void display() const {
		cout << "Name: " << name << "\nUsername: " << username
		     << "\nBalance: $" << balance << "\n";
	}
};

bool isUsernameTaken(const string &newUsername) {
	ifstream fin("users.txt");
	string line;

	while (getline(fin, line)) {
		size_t pos1 = line.find(',');
		size_t pos2 = line.find(',', pos1 + 1);
		string username = line.substr(pos1 + 1, pos2 - pos1 - 1);

		if (username == newUsername) {
			fin.close();
			return true;
		}
	}
	fin.close();
	return false;
}

void createUser() {

	string name, username;
	int pin;
	int confirmPin;
	double balance;

	cout << "Enter Your Full Name: ";
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	getline(cin, name);

	while (true) {

		cout << "Enter username: ";
		cin >> username;

		if (isUsernameTaken(username)) {
			cout << "Username already exists!! Try a different one.\n";
		} else {
			break;
		}
	}

	while (true) {

		cout << "Set a 4-digit PIN: ";
		cin >> pin;

		while (pin < 1000 || pin > 9999) {
			cout << "Pin must be a 4-digit number. Try Again.\n";
			cin >> pin;
		}

		cout << "Confirm your PIN: ";
		cin >> confirmPin;

		if (pin != confirmPin) {
			cout << "PINs do not match. Try again.\n";
		} else {
			cout << "Pin set successfully.\n";
			break;
		}
	}

	cout << "Initial deposit amount ($): ";
	cin >> balance;

	while (balance < 0) {
		cout << "Initial deposit cannot be negative. Please enter a valid amount: ";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> balance;
	}

	User newUser;
	newUser.setData(name, username, pin, balance);
	newUser.saveToFile();

	cout << GREEN << "\nAccount created successfully!\n"
	     << RESET << endl;
	newUser.display();
}

bool loadUser(const string &username, int pin, User &user) {
	ifstream fin("users.txt");
	string line;
	bool found = false;

	if (!fin.is_open()) {
		return false;
	}

	while (getline(fin, line)) {
		size_t pos1 = line.find(',');
		string name = line.substr(0, pos1);

		size_t pos2 = line.find(',', pos1 + 1);
		string fileUsername = line.substr(pos1 + 1, pos2 - pos1 - 1);

		size_t pos3 = line.find(',', pos2 + 1);
		int filePin = stoi(line.substr(pos2 + 1, pos3 - pos2 - 1));

		double fileBalance = stod(line.substr(pos3 + 1));

		if (fileUsername == username && filePin == pin) {
			user.setData(name, fileUsername, filePin, fileBalance);
			found = true;
			break;
		}
	}
	fin.close();
	return found;
}

void updateUserInFile(const User &updatedUser) {
	vector<User> users;
	ifstream fin("users.txt");
	string line;

	if (fin.is_open()) {
		while (getline(fin, line)) {
			size_t pos1 = line.find(',');
			string name = line.substr(0, pos1);

			size_t pos2 = line.find(',', pos1 + 1);
			string fileUsername = line.substr(pos1 + 1, pos2 - pos1 - 1);

			size_t pos3 = line.find(',', pos2 + 1);
			int filePin = stoi(line.substr(pos2 + 1, pos3 - pos2 - 1));

			double fileBalance = stod(line.substr(pos3 + 1));

			if (fileUsername == updatedUser.getUsername()) {
				users.push_back(updatedUser);
			} else {
				users.push_back(User(name, fileUsername, filePin, fileBalance));
			}
		}
		fin.close();
	} else {
		cout << "Error: 'users.txt' not found for update.Creating new file.\n";
	}

	ofstream fout("users.txt");
	if (fout.is_open()) {
		for (const auto &user : users) {
			fout << user.getName() << ',' << user.getUsername() << ','
			     << user.getPin() << ',' << user.getBalance() << '\n';
		}
		fout.close();
	} else {
		cout << "Error opening file to rewrite user data.\n";
	}
}

void printReceipt(const string &type, double amount, double newBalance) {
	cout << "\n-------- Transaction Receipt --------" << endl;
	cout << "Transaction Type: " << type << endl;
	cout << "Amount: $" << fixed << setprecision(2) << amount << endl;
	cout << "New Balance: $" << newBalance << endl;
	cout << "Date: " << __DATE__ << "  Time: " << __TIME__ << endl;
	cout << "Bank Ref: #" << rand() % 1000000 << endl;
	cout << "-------------------------------------" << endl;
}

void deposit(User &currentUser) {
	double amount;
	cout << "\nEnter amount to deposit: $";
	cin >> amount;

	if (amount <= 0) {
		cout << "Deposit amount must be positive.\n";
		return;
	}

	currentUser.setBalance(currentUser.getBalance() + amount);
	updateUserInFile(currentUser);
	/*cout << "Successfully deposited $" << amount << ".\n";
	cout << "New balance: $" << currentUser.getBalance() << ".\n";*/
	printReceipt("Deposit", amount, currentUser.getBalance());
}

void withdraw(User &currentUser) {
	double amount;
	cout << "\nEnter withdrawal amount: $";
	cin >> amount;

	if (currentUser.getBalance() < 0) {
		cout << "Insufficient balance.\n";
		return;
	}

	if (amount > currentUser.getBalance()) {
		cout << "Insufficient balance.\n";
		return;
	}

	if (amount <= 0) {
		cout << "Withdrawal amount must be greater than zero.\n";
		return;
	}

	currentUser.setBalance(currentUser.getBalance() - amount);
	updateUserInFile(currentUser);
	/*cout << "Successfully withdrew $" << amount << ".\n";
	cout << "New Balance: $" << currentUser.getBalance() << '\n';*/
	printReceipt("Withdrawal", amount, currentUser.getBalance());
}

void checkBalance(User &currentUser) {
	currentUser.display();
}

void animateLogout() {
	string msg = "Logging out";
	for (int i = 0; i < 3; ++i) {
		cout << msg;
		for (int j = 0; j <= i; ++j)
			cout << ".";
		cout << "\r" << flush;
		std::this_thread::sleep_for(chrono::milliseconds(500));
	}
	cout << "\n"
	     << GREEN << "Goodbye! Come back soon. \n"
	     << RESET;
}

void login() {
	string username;
	int pin;
	User currentUser;

	cout << "Enter username: ";
	cin >> username;
	cout << "Enter 4-digit PIN: ";
	cin >> pin;

	if (loadUser(username, pin, currentUser)) {

		/*cout << "\nLogin Successfull! Welcome, " << currentUser.getName() << ".\n"
		     << endl;*/
		system(CLEAR);
		cout << BLUE << R"(

 _______                                            ___            _______                         __     
/       \                                          /   \          /       \                       /  |    
$$$$$$$  |  ______    ______   _____  ____        /$$$  |         $$$$$$$  | __    __   _______  _$$ |_   
$$ |__$$ | /      \  /      \ /     \/    \       $$ $$ \__       $$ |__$$ |/  |  /  | /       |/ $$   |  
$$    $$< /$$$$$$  |/$$$$$$  |$$$$$$ $$$$  |      /$$$     |      $$    $$< $$ |  $$ |/$$$$$$$/ $$$$$$/   
$$$$$$$  |$$ |  $$ |$$ |  $$ |$$ | $$ | $$ |      $$ $$ $$/       $$$$$$$  |$$ |  $$ |$$      \   $$ | __ 
$$ |__$$ |$$ \__$$ |$$ \__$$ |$$ | $$ | $$ |      $$ \$$  \       $$ |__$$ |$$ \__$$ | $$$$$$  |  $$ |/  |
$$    $$/ $$    $$/ $$    $$/ $$ | $$ | $$ |      $$   $$  |      $$    $$/ $$    $$/ /     $$/   $$  $$/ 
$$$$$$$/   $$$$$$/   $$$$$$/  $$/  $$/  $$/        $$$$/$$/       $$$$$$$/   $$$$$$/  $$$$$$$/     $$$$/  
                                                                                                                                                                                                                   
)" << RESET << endl;

		cout << BLUE << "Welcome to the " << YELLOW << "Bank of Boom & Busts" << BLUE << ", " << GREEN
		     << currentUser.getName() << RESET << "!\n";

		int choice;

		do {
			cout << "\n+-----------------------------+\n";
			cout << "|     Banking Options         |\n";
			cout << "+-----------------------------+\n";
			cout << "| 1. Deposit                  |\n";
			cout << "| 2. Withdraw                 |\n";
			cout << "| 3. Check Balance            |\n";
			cout << "| 4. Logout                   |\n";
			cout << "+-----------------------------+\n";
			cout << "Enter Your Choice: ";
			cin >> choice;

			switch (choice) {
			case 1:
				deposit(currentUser);
				break;
			case 2:
				withdraw(currentUser);
				break;
			case 3:
				checkBalance(currentUser);
				break;
			case 4:
				// cout << "Logging out...\n";
				animateLogout();
				break;
			default:
				cout << "Invalid choice. Please try again.\n";
				break;
			}

			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << YELLOW << "\n[ Press Enter to continue... ]" << RESET << endl;
			cin.get();
			system(CLEAR);
		} while (choice != 4);
	} else {
		cout << "Invalid username or PIN. Please try again.\n";
	}
}

int main() {

	srand(time(0));

	cout << fixed << setprecision(2);
	int entryChoice;

	while (true) {
		cout << "==========================="
		     << "\n   Bank of Boom & Busts"
		     << "\n===========================" << endl;
		cout << "1. Login\n2. Create New Account\n3. Exit"
		     << "\n==========================="
		     << endl;
		cout << "Enter your choice: ";

		cin >> entryChoice;

		switch (entryChoice) {
		case 1:
			login();
			break;
		case 2:
			createUser();
			break;
		case 3:
			cout << "\nThanks for choosing Bank of Boom & Busts"
			     << "\nLogging out...\n"
			     << endl;
			return 0;
			break;
		default:
			cout << "Please enter valid option !" << endl;
			break;
		}

		cout << YELLOW << "\n[ Press Enter to continue... ]" << RESET << endl;
		cin.ignore();  // clear buffer
		cin.get();     // wait for Enter
		system(CLEAR); // or use system("cls"); on Windows
	}
	return 0;
}

/*

*/
