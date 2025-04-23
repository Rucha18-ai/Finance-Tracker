#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <iomanip>
using namespace std;

const int MAX_USERS = 10;
const int MAX_TRANSACTIONS = 100;
const int MAX_TASKS = 100;
const int MAX_INVESTMENTS = 50;
const int MAX_BUDGET_PLANS = 3;

class Transaction {
public:
    string type;
    string name;
    string category;
    float amount;

    virtual void display() const {
        cout << type << ": " << name << " | " << category << " | Rs. " << amount << endl;
    }

    virtual ~Transaction() {}
};

class Income : public Transaction {
public:
    Income() {
        type = "Income";
    }

    void display() const override {
        cout << "[INCOME] " << name << " | Category: " << category << " | Rs. " << amount << endl;
    }
};

class Expense : public Transaction {
public:
    Expense() {
        type = "Expense";
    }

    void display() const override {
        cout << "[EXPENSE] " << name << " | Category: " << category << " | Rs. " << amount << endl;
    }
};

class Investment {
public:
    string type;
    float amount;
    string note;

    void display() const {
        cout << type << " - Rs. " << amount << " (" << note << ")" << endl;
    }
};

class Task {
public:
    string description;
    bool completed;
};

class BudgetPlan {
public:
    string name;
    float incomeLimit;
    float expenseLimit;
    float savingsGoal;

    void display() const {
        cout << name << ": Income Limit Rs. " << incomeLimit << " | Expense Limit Rs. " << expenseLimit << " | Savings Goal Rs. " << savingsGoal << endl;
    }
};

class Loan {
public:
    string provider;
    float amount;
    float interestRate;
    int termMonths;

    void display() const {
        cout << "Loan Provider: " << provider << " | Amount: Rs. " << amount << " | Interest Rate: " << interestRate << "% | Term: " << termMonths << " months" << endl;
    }
};

class User {
protected:
    string username;
    string password;
    string role;

    Transaction* transactions[MAX_TRANSACTIONS];
    int transactionCount;

    Investment investments[MAX_INVESTMENTS];
    int investmentCount;

    Task tasks[MAX_TASKS];
    int taskCount;

    BudgetPlan budgetPlans[MAX_BUDGET_PLANS];
    int budgetPlanCount;

    Loan loan;
    bool hasLoan;

    float savingsGoal;
    float totalIncome;
    float totalExpense;

public:
    User() {
        transactionCount = 0;
        investmentCount = 0;
        taskCount = 0;
        budgetPlanCount = 0;
        savingsGoal = 0;
        totalIncome = 0;
        totalExpense = 0;
        hasLoan = false;
    }

    virtual ~User() {
        for (int i = 0; i < transactionCount; i++) {
            delete transactions[i];
        }
    }

    void setLogin(string uname, string pass) {
        username = uname;
        password = pass;
    }

    string getUsername() { return username; }
    string getPassword() { return password; }
    string getRole() { return role; }
    void setRole(string r) { role = r; addDefaultPlans(); }

    void addDefaultPlans() {
        if (budgetPlanCount >= MAX_BUDGET_PLANS) return;
        if (role == "Housewife") {
            budgetPlans[budgetPlanCount++] = {"Basic House Budget", 20000, 15000, 3000};
        } else if (role == "Businessperson") {
            budgetPlans[budgetPlanCount++] = {"Business Budget", 100000, 70000, 20000};
        } else if (role == "Jobholder") {
            budgetPlans[budgetPlanCount++] = {"Salary Budget", 50000, 30000, 10000};
        }
    }

    void addTransaction(Transaction* t) {
        if (transactionCount < MAX_TRANSACTIONS) {
            transactions[transactionCount++] = t;
            if (t->type == "Income") totalIncome += t->amount;
            else if (t->type == "Expense") totalExpense += t->amount;
        }
    }

    void viewSummary() {
        cout << "\n--- Financial Summary ---\n";
        cout << "Total Income: Rs. " << totalIncome << endl;
        cout << "Total Expense: Rs. " << totalExpense << endl;
        cout << "Net Savings: Rs. " << totalIncome - totalExpense << endl;
    }

    void setSavingsGoal() {
        cout << "Enter your savings goal amount: ";
        cin >> savingsGoal;
        cout << "Savings goal set to Rs. " << savingsGoal << endl;
    }

    void showSavingsProgress() {
        float currentSavings = totalIncome - totalExpense;
        cout << "Current Savings: Rs. " << currentSavings << " / Rs. " << savingsGoal << endl;
    }

    void addInvestment() {
        if (investmentCount >= MAX_INVESTMENTS) {
            cout << "Investment limit reached!\n";
            return;
        }
        cin.ignore();
        cout << "Enter investment type: ";
        getline(cin, investments[investmentCount].type);
        cout << "Enter amount: ";
        cin >> investments[investmentCount].amount;
        cin.ignore();
        cout << "Enter note: ";
        getline(cin, investments[investmentCount].note);
        investmentCount++;
        cout << "Investment added successfully!\n";
    }

    void viewInvestments() {
        for (int i = 0; i < investmentCount; i++) {
            investments[i].display();
        }
    }

    void addTask() {
        if (taskCount >= MAX_TASKS) return;
        cin.ignore();
        cout << "Enter task description: ";
        getline(cin, tasks[taskCount].description);
        tasks[taskCount].completed = false;
        taskCount++;
        cout << "Task added successfully!\n";
    }

    void viewTasks() {
        for (int i = 0; i < taskCount; i++) {
            cout << (i + 1) << ". [" << (tasks[i].completed ? "X" : " ") << "] " << tasks[i].description << endl;
        }
    }

    void completeTask() {
        int index;
        cout << "Enter task number to mark complete: ";
        cin >> index;
        if (index > 0 && index <= taskCount) {
            tasks[index - 1].completed = true;
            cout << "Task marked as complete.\n";
        } else {
            cout << "Invalid task number.\n";
        }
    }

    void addBudgetPlan() {
        if (budgetPlanCount >= MAX_BUDGET_PLANS) {
            cout << "Budget plan limit reached!\n";
            return;
        }
        cin.ignore();
        cout << "Enter plan name: ";
        getline(cin, budgetPlans[budgetPlanCount].name);
        cout << "Enter income limit: ";
        cin >> budgetPlans[budgetPlanCount].incomeLimit;
        cout << "Enter expense limit: ";
        cin >> budgetPlans[budgetPlanCount].expenseLimit;
        cout << "Enter savings goal: ";
        cin >> budgetPlans[budgetPlanCount].savingsGoal;
        budgetPlanCount++;
        cout << "Budget plan added!\n";
    }

    void showTips() {
        cout << "\n--- Financial Tips ---\n";
        cout << "1. Track your expenses daily.\n";
        cout << "2. Save at least 20% of your income.\n";
        cout << "3. Avoid unnecessary subscriptions.\n";
        cout << "4. Invest wisely.\n";
    }

    void saveData() {
        ofstream outFile("user_data.txt");
        if (outFile.is_open()) {
            outFile << username << endl;
            outFile << role << endl;
            outFile << totalIncome << endl;
            outFile << totalExpense << endl;
            outFile << savingsGoal << endl;
            outFile << transactionCount << endl;
            for (int i = 0; i < transactionCount; i++) {
                outFile << transactions[i]->type << endl;
                outFile << transactions[i]->name << endl;
                outFile << transactions[i]->category << endl;
                outFile << transactions[i]->amount << endl;
            }
            outFile << investmentCount << endl;
            for (int i = 0; i < investmentCount; i++) {
                outFile << investments[i].type << endl;
                outFile << investments[i].amount << endl;
                outFile << investments[i].note << endl;
            }
            outFile << taskCount << endl;
            for (int i = 0; i < taskCount; i++) {
                outFile << tasks[i].description << endl;
                outFile << tasks[i].completed << endl;
            }
            outFile << budgetPlanCount << endl;
            for (int i = 0; i < budgetPlanCount; i++) {
                outFile << budgetPlans[i].name << endl;
                outFile << budgetPlans[i].incomeLimit << endl;
                outFile << budgetPlans[i].expenseLimit << endl;
                outFile << budgetPlans[i].savingsGoal << endl;
            }
            outFile << hasLoan << endl;
            if (hasLoan) {
                outFile << loan.provider << endl;
                outFile << loan.amount << endl;
                outFile << loan.interestRate << endl;
                outFile << loan.termMonths << endl;
            }
            outFile.close();
            cout << "Data saved successfully.\n";
        } else {
            cout << "Error saving data.\n";
        }
    }

    void loadData() {
        ifstream inFile("user_data.txt");
        if (inFile.is_open()) {
            getline(inFile, username);
            getline(inFile, role);
            inFile >> totalIncome;
            inFile >> totalExpense;
            inFile >> savingsGoal;
            inFile >> transactionCount;
            inFile.ignore(); // Ignore newline after transactionCount
            for (int i = 0; i < transactionCount; i++) {
                string type;
                getline(inFile, type);
                Transaction* t;
                if (type == "Income") {
                    t = new Income();
                } else {
                    t = new Expense();
                }
                t->type = type;
                getline(inFile, t->name);
                getline(inFile, t->category);
                inFile >> t->amount;
                inFile.ignore(); // Ignore newline after amount
                addTransaction(t);
            }
            inFile >> investmentCount;
            inFile.ignore(); // Ignore newline after investmentCount
            for (int i = 0; i < investmentCount; i++) {
                getline(inFile, investments[i].type);
                inFile >> investments[i].amount;
                inFile.ignore(); // Ignore newline after amount
                getline(inFile, investments[i].note);
            }
            inFile >> taskCount;
            inFile.ignore(); // Ignore newline after taskCount
            for (int i = 0; i < taskCount; i++) {
                getline(inFile, tasks[i].description);
                inFile >> tasks[i].completed;
                inFile.ignore(); // Ignore newline after completed
            }
            inFile >> budgetPlanCount;
            inFile.ignore(); // Ignore newline after budgetPlanCount
            for (int i = 0; i < budgetPlanCount; i++) {
                getline(inFile, budgetPlans[i].name);
                inFile >> budgetPlans[i].incomeLimit;
                inFile >> budgetPlans[i].expenseLimit;
                inFile >> budgetPlans[i].savingsGoal;
                inFile.ignore(); // Ignore newline after savingsGoal
            }
            inFile >> hasLoan;
            inFile.ignore(); // Ignore newline
            if (hasLoan) {
                getline(inFile, loan.provider);
                inFile >> loan.amount;
                inFile >> loan.interestRate;
                inFile >> loan.termMonths;
            }
            inFile.close();
            cout << "Data loaded successfully.\n";
        } else {
            cout << "Error loading data.\n";
        }
    }

    void applyForLoan() {
        if (hasLoan) {
            cout << "You already have an active loan.\n";
            return;
        }
        cin.ignore();
        cout << "Enter loan provider name: ";
        getline(cin, loan.provider);
        cout << "Enter loan amount: ";
        cin >> loan.amount;
        cout << "Enter interest rate (%): ";
        cin >> loan.interestRate;
        cout << "Enter loan term (months): ";
        cin >> loan.termMonths;
        hasLoan = true;
        cout << "Loan application submitted successfully!\n";
    }

    void viewLoanDetails() {
        if (!hasLoan) {
            cout << "No active loan found.\n";
            return;
        }
        cout << "\n--- Loan Details ---\n";
        loan.display();
    }

    void viewBudgetPlans() {
        for (int i = 0; i < budgetPlanCount; i++) {
            budgetPlans[i].display();
        }
    }
};

int main() {
    User* currentUser = nullptr;
    int choice;

    while (true) {
        cout << "\n===== Personal Finance Manager =====\n";
        cout << "Don't have an account...Please register yourself...!!\n";
        cout << "1. Login\n";
        cout << "2. Register\n";
        cout << "3. Exit\n";

        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 3) {
            cout << "Goodbye!" << endl;
            break;
        }

        string username, password;
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;

        if (choice == 1) {
            if (username == "Rucha" && password == "Rucha@2006") {
                cout << "Welcome, Rucha!" << endl;
                currentUser = new User();
                currentUser->setLogin(username, password);
                currentUser->setRole("Jobholder");
            }
            else if (username == "Zeel" && password == "Zeel@2009") {
                cout << "Welcome, Zeel!" << endl;
                currentUser = new User();
                currentUser->setLogin(username, password);
                currentUser->setRole("Businessperson");
            }
            else if (username == "Sneha" && password == "Sneha@1984") {
                cout << "Welcome, Sneha!" << endl;
                currentUser = new User();
                currentUser->setLogin(username, password);
                currentUser->setRole("Housewife");
            }
            else {
                cout << "Invalid credentials.\n";
                continue; // Go back to the main menu
            }
        }
        else if (choice == 2) {
            cout << "Registration successful. Welcome " << username << "!" << endl;
            currentUser = new User();
            currentUser->setLogin(username, password);

            string role;
            cout << "Choose your role:\n";
            cout << "1. Jobholder\n";
            cout << "2. Businessperson\n";
            cout << "3. Housewife\n";
            cout << "Enter role number: ";
            int roleChoice;
            cin >> roleChoice;

            switch (roleChoice) {
                case 1: role = "Jobholder"; break;
                case 2: role = "Businessperson"; break;
                case 3: role = "Housewife"; break;
                default: role = "Unknown"; break;
            }
            currentUser->setRole(role);
        }

        if (currentUser) {
            int loggedInChoice;
            while (true) {
                cout << "\n1. View Summary\n";
                cout << "2. Add Income\n";
                cout << "3. Add Expense\n";
                cout << "4. Set Savings Goal\n";
                cout << "5. Show Savings Progress\n";
                cout << "6. Add Investment\n";
                cout << "7. View Investments\n";
                cout << "8. Add Task\n";
                cout << "9. View Tasks\n";
                cout << "10. Complete Task\n";
                cout << "11. View Budget Plans\n";
                cout << "12. Add Budget Plan\n";
                cout << "13. Show Financial Tips\n";
                cout << "14. Save Data\n";
                cout << "15. Load Data\n";
                cout << "16. Apply for Loan\n";
                cout << "17. View Loan Details\n";
                cout << "18. Logout\n";
                cout << "Enter choice: ";
                cin >> loggedInChoice;

                if (loggedInChoice == 18) {
                    delete currentUser;
                    currentUser = nullptr;
                    cout << "Logged out.\n";
                    break;
                }

                switch (loggedInChoice) {
                    case 1: currentUser->viewSummary(); break;
                    case 2: {
                        string name, category;
                        float amount;
                        cout << "Enter income name: ";
                        cin >> name;
                        cout << "Enter income category: ";
                        cin >> category;
                        cout << "Enter income amount: ";
                        cin >> amount;
                        Income* income = new Income();
                        income->name = name;
                        income->category = category;
                        income->amount = amount;
                        currentUser->addTransaction(income);
                        break;
                    }
                    case 3: {
                        string name, category;
                        float amount;
                        cout << "Enter expense name: ";
                        cin >> name;
                        cout << "Enter expense category: ";
                        cin >> category;
                        cout << "Enter expense amount: ";
                        cin >> amount;
                        Expense* expense = new Expense();
                        expense->name = name;
                        expense->category = category;
                        expense->amount = amount;
                        currentUser->addTransaction(expense);
                        break;
                    }
                    case 4: currentUser->setSavingsGoal(); break;
                    case 5: currentUser->showSavingsProgress(); break;
                    case 6: currentUser->addInvestment(); break;
                    case 7: currentUser->viewInvestments(); break;
                    case 8: currentUser->addTask(); break;
                    case 9: currentUser->viewTasks(); break;
                    case 10: currentUser->completeTask(); break;
                    case 11: currentUser->viewBudgetPlans(); break;
                    case 12: currentUser->addBudgetPlan(); break;
                    case 13: currentUser->showTips(); break;
                    case 14: currentUser->saveData(); break;
                    case 15: currentUser->loadData(); break;
                    case 16: currentUser->applyForLoan(); break;
                    case 17: currentUser->viewLoanDetails(); break;
                    default: cout << "Invalid choice. Try again.\n"; break;
                }
            }
        }
    }

    return 0;
}
