#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class BankAccount {
public:
    int accNo;
    string name;
    double balance;

    void createAccount() {
        cout << "\nEnter Account Number: ";
        cin >> accNo;
        cin.ignore();

        cout << "Enter Customer Name: ";
        getline(cin, name);

        cout << "Enter Initial Balance: ";
        cin >> balance;
    }

    void showAccount() {
        cout << "\n----------------------------";
        cout << "\nAccount No : " << accNo;
        cout << "\nName       : " << name;
        cout << "\nBalance    : " << balance;
        cout << "\n----------------------------\n";
    }
};

void createAccount() {
    BankAccount a;
    a.createAccount();

    ofstream file("bank.txt", ios::app);
    file << a.accNo << "," << a.name << "," << a.balance << endl;
    file.close();

    cout << "\nAccount Created Successfully!\n";
}

void displayAccounts() {
    ifstream file("bank.txt");
    string line;

    cout << "\n===== All Accounts =====\n";

    while(getline(file,line))
        cout << line << endl;

    file.close();
}

void searchAccount() {
    ifstream file("bank.txt");
    string line;
    int acc;
    bool found=false;

    cout<<"\nEnter Account Number: ";
    cin>>acc;

    while(getline(file,line)){
        if(line.find(to_string(acc)+",")==0){
            cout<<"\nAccount Found:\n";
            cout<<line<<endl;
            found=true;
            break;
        }
    }

    if(!found)
        cout<<"\nAccount Not Found!\n";

    file.close();
}

void depositMoney() {

    int acc;
    double amount;

    cout<<"\nEnter Account Number: ";
    cin>>acc;

    cout<<"Enter Deposit Amount: ";
    cin>>amount;

    ifstream file("bank.txt");
    ofstream temp("temp.txt");

    string line;
    bool found=false;

    while(getline(file,line)){

        int comma1=line.find(',');
        int comma2=line.find(',',comma1+1);

        int account=stoi(line.substr(0,comma1));
        string name=line.substr(comma1+1,comma2-comma1-1);
        double balance=stod(line.substr(comma2+1));

        if(account==acc){
            balance+=amount;
            found=true;
        }

        temp<<account<<","<<name<<","<<balance<<endl;
    }

    file.close();
    temp.close();

    remove("bank.txt");
    rename("temp.txt","bank.txt");

    if(found)
        cout<<"\nDeposit Successful!\n";
    else
        cout<<"\nAccount Not Found!\n";
}

void withdrawMoney() {

    int acc;
    double amount;

    cout<<"\nEnter Account Number: ";
    cin>>acc;

    cout<<"Enter Withdraw Amount: ";
    cin>>amount;

    ifstream file("bank.txt");
    ofstream temp("temp.txt");

    string line;
    bool found=false;

    while(getline(file,line)){

        int comma1=line.find(',');
        int comma2=line.find(',',comma1+1);

        int account=stoi(line.substr(0,comma1));
        string name=line.substr(comma1+1,comma2-comma1-1);
        double balance=stod(line.substr(comma2+1));

        if(account==acc){

            if(balance>=amount){
                balance-=amount;
                cout<<"\nWithdrawal Successful!\n";
            }
            else{
                cout<<"\nInsufficient Balance!\n";
            }

            found=true;
        }

        temp<<account<<","<<name<<","<<balance<<endl;
    }

    file.close();
    temp.close();

    remove("bank.txt");
    rename("temp.txt","bank.txt");

    if(!found)
        cout<<"\nAccount Not Found!\n";
}

int main(){

    int choice;

    do{

        cout<<"\n========== BANK MANAGEMENT ==========\n";
        cout<<"1. Create Account\n";
        cout<<"2. Deposit Money\n";
        cout<<"3. Withdraw Money\n";
        cout<<"4. Search Account\n";
        cout<<"5. Display All Accounts\n";
        cout<<"6. Exit\n";

        cout<<"\nEnter Choice: ";
        cin>>choice;

        switch(choice){

        case 1:
            createAccount();
            break;

        case 2:
            depositMoney();
            break;

        case 3:
            withdrawMoney();
            break;

        case 4:
            searchAccount();
            break;

        case 5:
            displayAccounts();
            break;

        case 6:
            cout<<"\nThank You!\n";
            break;

        default:
            cout<<"\nInvalid Choice!\n";
        }

    }while(choice!=6);

    return 0;
}