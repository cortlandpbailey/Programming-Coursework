#include <iostream>
#include <string>
#include <map>
using namespace std;

class Contacts {
private:
    map<string, int> names;
    map<int, string> numbers;

public:
    Contacts();
    bool addContact(string name, int number);
    int getNumber(string name);
    string getName(int number);
    bool removeName(string name);
    bool removeNumber(int number);
};

Contacts::Contacts() {

}

bool Contacts::addContact(string name, int number) {
    if (number < 1000000 || number >= 10000000 || number / 1000000 ==0)         // check validity
        return false;
    
    if (name.empty())
        return false;

    names.emplace(name,number);       //assign name and number in contact maps
    numbers.emplace(number,name);
    return true;
}

int Contacts::getNumber(string name) {
    if (names.find(name) != names.end())        // see if the name is in the maps and return the number associated with it
        return names.at(name);
    else 
        return -1;
}

string Contacts::getName(int number) {
    if (numbers.find(number) != numbers.end())      // check if the number is in the contacts, if it is return the name associated with it
        return numbers.at(number);
    else
        return "";
}

bool Contacts::removeName(string name) {
    if (names.find(name) != names.end()) {
        int num = names.at(name);
        names.erase(name);
        numbers.erase(num);
        return true;
    }
    else
        return false;
}

bool Contacts::removeNumber(int number) {
    if (numbers.find(number) != numbers.end()) {
        string name = numbers.at(number);
        numbers.erase(number);
        names.erase(name);
        return true;
    }
    else
        return false;
}