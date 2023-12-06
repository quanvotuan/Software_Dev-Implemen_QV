#include <iostream>
#include <string>

using namespace std;

class User{
private:
    string FirstName;
    string LastName;
    int Age;
    string Email;

public:
    User() // *** Can only have 1 default constructor
    {
        Age = 0;
    }

    User(string firstName, string lastName, int age){
        FirstName = firstName;
        LastName = lastName;
        Age = age;
        Email = firstName+"."+lastName+"@gmail.com";
    }

    void PrintInfo(){
        cout << "FName: " << FirstName << endl;
        cout << "LName: " << LastName << endl;
        cout << "Age: " << Age << endl;
        cout << "Email: " << Email << "\n" << endl;

    }

};


int main() {

    User user1("Quan", "Vo", 20);
    User user2("An", "Hoang", 22);
    User user3;

    user1.PrintInfo();
    user2.PrintInfo();
    user3.PrintInfo();

    cin.get();
}

/*
 * What are the diff types of Constructors?
 *  1. Default
 *  2. Parameterized
 *  3. Copy
 *
 *
 * What are the 6 rules for Constructors?
 *  1. Same name as the class contained it
 *  2. Does not have return type
 *  3. Placed in the public area of the class
 *  4. Default Constructor doesn't have any parameters
 *  5. C++ auto creat a constructor for me, (Not very helpful most of the time)
 *  6. Default constructors are created when I invoke an object in that class

 * When I start create any personal constructor!!!
 * -> I'll automatically lose the default constructor that C++ provided
 * -> Solution: Created my own default constructor

 */
