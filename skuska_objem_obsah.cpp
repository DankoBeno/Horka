#include <iostream>

using namespace std;

int main()
{
    int a, b, c;

    cin >> a;
    cin >> b;
    cin >> c;
    int v = a * b * c;
    int s = 2 * (a * b + b * c + c * a);

    cout << "V" << v << " " << "S" << s << "\n";
    return 0;
}