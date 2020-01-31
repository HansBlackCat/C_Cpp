#include <iostream>
#include <string>

using namespace std; 

int main() {
    /*
    int t;
    while(cin >> t) {
        cout << "> " << t << endl;
        if (t == -1) break;
    }
    */

    /*
    // Cin Hex
    int t;
    while (true) {
        // Init 2nd Arg, and set(apply) 1st Arg
        cin.setf(ios_base::hex, ios_base::basefield);
        cin >> t;
        cout << "Input? " << t << endl;
        if (cin.fail()) {
            cout << "Wrong Input!" << endl;
            cin.clear();
            cin.ignore(10, '\n');
        }
        if (t == -1) break;
    }
    */

   /* 
   // Cin Hex (Internally same code with 2nd block)
    int t;
    while (true) {
        cin >> hex >> t;
        cout << "Input? " << t << endl;
        if (cin.fail()) {
            cout << "Wrong Input" << endl;
            cin.clear();
            cin.ignore(10, '\n');
        }
        if (t == -1) break;
    } 
    */

    // Streambuf
    string s;
    cin >> s;

    char peek = cin.rdbuf() -> snextc();
    if (cin.fail()) cout << "Failed";
    cout << "First character in second word: " << peek << endl;
    cin >> s;
    cout << "Again: " << s << endl;
}