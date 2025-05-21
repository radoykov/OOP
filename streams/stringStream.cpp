#include <iostream>
#include <string>
#include <sstream>

using namespace std;

int main()
{
    string s1 = "I like 10";
    stringstream ss(s1);

    string f, s;
    int t;
    ss >> f >> s >> t;

    cout << f << " " << s << " " << t + 5 << endl;

    getline(cin, s1);
    stringstream ss1(s1);
    string word;
    while (ss1 >> word)
    {
        cout << word << endl;
    }
    return 0;
}