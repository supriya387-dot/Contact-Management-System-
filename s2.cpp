#include <iostream>
#include <conio.h>
#include <fstream>
#include <cstdio>

using namespace std;

class contact
{
private:
    char fName[50], lName[50], address[100], email[50];
    long long phNo;

public:

    void createContact()
    {
        cout << "\nEnter your first name: ";
        cin >> fName;

        cout << "Enter your last name: ";
        cin >> lName;

        cout << "Enter your phone number: ";
        cin >> phNo;

        cout << "Enter address: ";
        cin >> address;

        cout << "Enter email: ";
        cin >> email;
    }

    void showContact()
    {
        cout << "\nName    : " << fName << " " << lName << endl;
        cout << "Phone   : " << phNo << endl;
        cout << "Address : " << address << endl;
        cout << "Email   : " << email << endl;
    }

    void writeOnFile()
    {
        char ch;
        ofstream f1;

        f1.open("CMS.dat", ios::binary | ios::app);

        do
        {
            createContact();

            f1.write(reinterpret_cast<char*>(this), sizeof(*this));

            cout << "\nDo you have next data? (y/n): ";
            cin >> ch;

        } while(ch == 'y' || ch == 'Y');

        cout << "\nContact has been successfully created...\n";

        f1.close();
    }

    void readFromFile()
    {
        ifstream f2;

        f2.open("CMS.dat", ios::binary);

        if(!f2)
        {
            cout << "\nFile could not be opened...";
            return;
        }

        cout << "\n========== CONTACT LIST ==========\n";

        while(f2.read(reinterpret_cast<char*>(this), sizeof(*this)))
        {
            showContact();
            cout << "----------------------------------\n";
        }

        f2.close();
    }

    void searchContact()
    {
        ifstream f3;
        long long phone;
        bool found = false;

        cout << "\nEnter phone no: ";
        cin >> phone;

        f3.open("CMS.dat", ios::binary);

        while(f3.read(reinterpret_cast<char*>(this), sizeof(*this)))
        {
            if(phone == phNo)
            {
                cout << "\nContact found...\n";
                showContact();
                found = true;
                break;
            }
        }

        if(!found)
        {
            cout << "\nContact not found...\n";
        }

        f3.close();
    }

    void deleteContact()
    {
        ifstream f5;
        ofstream f4;

        long long phone;
        bool flag = false;

        cout << "\nEnter phone no to delete: ";
        cin >> phone;

        f5.open("CMS.dat", ios::binary);
        f4.open("temp.dat", ios::binary);

        while(f5.read(reinterpret_cast<char*>(this), sizeof(*this)))
        {
            if(phone != phNo)
            {
                f4.write(reinterpret_cast<char*>(this), sizeof(*this));
            }
            else
            {
                flag = true;
            }
        }

        f5.close();
        f4.close();

        remove("CMS.dat");
        rename("temp.dat", "CMS.dat");

        if(flag)
            cout << "\n\tContact Deleted...\n";
        else
            cout << "\n\tContact Not Found...\n";
    }

    void modifyContact()
    {
        fstream f6;
        long long phone;
        bool found = false;

        cout << "\nEnter phone no to modify: ";
        cin >> phone;

        f6.open("CMS.dat", ios::binary | ios::in | ios::out);

        while(f6.read(reinterpret_cast<char*>(this), sizeof(*this)))
        {
            if(phone == phNo)
            {
                cout << "\nEnter new contact details:\n";

                createContact();

                int pos = -1 * sizeof(*this);

                f6.seekp(pos, ios::cur);

                f6.write(reinterpret_cast<char*>(this), sizeof(*this));

                cout << "\n\tContact Successfully Updated...\n";

                found = true;
                break;
            }
        }

        if(!found)
        {
            cout << "\n\tContact Not Found...\n";
        }

        f6.close();
    }
};


int main()
{
    contact c;
    char choice;

    do
    {
        system("cls");
        system("color 3F");

        cout << "\n========================================";
        cout << "\n       CONTACT MANAGEMENT SYSTEM";
        cout << "\n========================================";

        cout << "\n\n\t1. Create Contact";
        cout << "\n\t2. Display All Contacts";
        cout << "\n\t3. Search Contact";
        cout << "\n\t4. Modify Contact";
        cout << "\n\t5. Delete Contact";
        cout << "\n\t6. Exit";

        cout << "\n\nEnter your choice: ";
        cin >> choice;

        switch(choice)
        {
            case '1':
                c.writeOnFile();
                break;

            case '2':
                c.readFromFile();
                break;

            case '3':
                c.searchContact();
                break;

            case '4':
                c.modifyContact();
                break;

            case '5':
                c.deleteContact();
                break;

            case '6':
                cout << "\nThank you for using Contact Management System!";
                exit(0);

            default:
                cout << "\nInvalid choice...";
        }

        cout << "\n\nPress any key to continue...";
        getch();

    } while(choice != '6');

    return 0;
}
