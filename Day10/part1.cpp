#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdint>
using namespace std;
typedef int64_t ll;

vector<vector<int>> machineDesiredState;
vector<vector<vector<int>>> buttonsPerMachine;

void readInput()
{
    char c;
    while (cin >> c)
    {
        if (c != '[')
            continue;

        vector<int> lightState;
        while (cin >> c)
        {
            if (c == ']')
                break;
            lightState.push_back(c == '#' ? 1 : 0);
        }
        machineDesiredState.push_back(lightState);

        int num;
        vector<vector<int>> buttons;
        while (cin >> c)
        {
            if (c == '{')
                break;
            int connected = 0;
            vector<int> button;
            while (cin >> num)
            {
                button.push_back(num);
                ++connected;
                cin >> c;
                if (c == ')')
                    break;
            }
            buttons.push_back(button);
        }
        buttonsPerMachine.push_back(buttons);
    }
}

int main()
{
    readInput();
    int ans = 0;
    for (int i = 0; i < machineDesiredState.size(); ++i)
    {
        const vector<int> &desiredState = machineDesiredState[i];
        const vector<vector<int>> &buttons = buttonsPerMachine[i];
        int m = desiredState.size();
        int b = buttons.size();
        int ansCurrentMachine = b + 1;

        // try all button combinations
        for (int mask = 0; mask < (1 << b); ++mask)
        {
            vector<int> currentState(m, 0);
            for (int j = 0; j < b; ++j)
            {
                if (mask & (1 << j))
                {
                    for (int lightIdx : buttons[j])
                    {
                        currentState[lightIdx] ^= 1;
                    }
                }
            }
            if (currentState == desiredState)
            {
                ansCurrentMachine = min(ansCurrentMachine, __builtin_popcount(mask));
            }
        }
        if (ansCurrentMachine == b + 1)
        {
            cout << "Machine" << i << " cannot be solved " << "\n";
            return 0;
        }
        ans += ansCurrentMachine;
    }
    cout << ans << endl;
    return 0;
}
