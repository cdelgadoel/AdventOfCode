#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);

    string input;
    cin >> input;

    bool activeBeams[input.size()];
    fill(activeBeams, activeBeams + input.size(), false);
    activeBeams[input.find('S')] = true;

    // read the "empty" line
    cin >> input;

    int64_t divisions = 0;
    while (cin >> input)
    {
        for (int i = 0; i < input.size(); ++i)
        {
            if (input[i] == '^' && activeBeams[i])
            {
                // activate a beam in the previous and next position
                // this takes advantage of there not being two consecutive "^^" characters next
                // to each other in the input
                ++divisions;
                activeBeams[i] = false;
                // no need to check for out of bounds since there are no "^" in the first or last column
                activeBeams[i - 1] = activeBeams[i + 1] = true;
            }
        }
        cin >> input; // read empty line
    }
    cout << divisions << endl;
}