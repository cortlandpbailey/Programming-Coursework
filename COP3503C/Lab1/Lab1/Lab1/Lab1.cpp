#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

int inputcheck(string& in0);
bool endcheck(string& in2);
void display(vector<string>, vector<unsigned int>, int size1, string title, string col1, string col2);

int main()
{
 //   bool endsignal;
    string title;
    int valid = 0;
    string header1;
    string header2;
    string temp;
    string temp1;
    unsigned int num;
    unsigned int comma;
    string input;
    unsigned int size = 0;
    vector<string> auth(0);
    vector<unsigned int> books(0);
    //1:
    cout << "Enter a title for the data:" << endl;                  //Get some input for the title
    getline(cin, title);
    cout << "You entered: " << title << endl;
    //2:
    cout << "Enter the column 1 header:" << endl;           //Get some input for column header #1
    getline(cin, header1);
    cout << "You entered: " << header1 << endl;

    cout << "Enter the column 2 header:" << endl;                   //Get some input for column header #2
    getline(cin, header2);
    cout << "You entered: " << header2 << endl;
    //3:
   
    while (valid != 1) {
        cout << "Enter a data point (-1 to stop input):" << endl;
        getline(cin, input);                                            //get input for author and number of books written.
        valid = inputcheck(input);
        
        if (valid == 1) {
            //if user types -1, end data entry and display
            display(auth, books, size, title, header1, header2);
        }
        else if (valid == 2) {
            cout << "Error: Too many commas in input." << endl;                //exception if more than 1 comma
        }
        else if (valid == 3) {
            cout << "Error: No comma in string." << endl;                      //exception if no commas
        }
        else if (valid == 4) {
            cout << "Error: Comma not followed by an integer." << endl;           //exception if no integer after comma
        }
        else {
            //if data entry is ongoing and data is valid, store the data
            comma = input.find(',');                                 //get the location of the comma in the string
            temp = input.substr(0, comma);
            temp1 = input.substr(comma+1, input.size());
            size++;                                                     //increment the size of the vectors
            auth.resize(size);
            books.resize(size);

            auth.at(size - 1) = temp;                                      //store the authors name in the vector
            // ** convert temp to an int
            
            num = stoi(temp1);
            books.at(size - 1) = num;                                     //store number in qty vector
            cout << "Data string: " << auth[size - 1] << endl;
            cout << "Data integer: " << books[size - 1] << endl;

        }
    }
    


    return 0;
}

int inputcheck(string& in0) {
    bool endsignal = endcheck(in0);
    int dig = in0.find(',');
    int dig2 = in0.find(',', dig+1);
    string s = in0.substr(dig+2, in0.size());
    bool t = isdigit(s.at(0));
    try {
        if (endsignal == true) {
            throw 1;                //if end signal received, stop program and display
        }
        else if (dig == string::npos) {
            throw 3;                //if no commas found throw exception 3
        }
        else if (dig2 != string::npos) {
            throw 2;                //if more than one comma found, throw exception 2
        }
        else {
            if (t != true) {
                throw 4;        // if the sub string after the comma isnt an integer, throw exception
            }
            else {
                throw 0;
            }
        }

    }

    catch (int z) {
        return z;
    }
}


bool endcheck(string& in2) {
    if (in2 == "-1")
    {
        return 1;
   }
    else {
        return 0;
    }
}

void display(vector<string> authors, vector<unsigned int> number, int size1, string title, string col1, string col2) {
    cout << endl << setw(33) << right << title << endl;
    cout << setw(20) << left << col1 << "|";
    cout << setw(23) << right << col2 << endl;
    cout << setfill('-') << setw(44) << "" << endl;
    cout << setfill(' ');
    for (int i=0; i < size1; i++) {
        cout << setw(20) << left << authors[i] << "|";
        cout << setw(23) << right << number[i] << endl;
    }
    cout << endl;
    for (int i=0; i < size1; i++) {
        cout << setw(20) << right << authors[i] << " ";
        cout << setfill('*') << setw(number[i]) << "" << endl;
        cout << setfill(' ');
    }

}