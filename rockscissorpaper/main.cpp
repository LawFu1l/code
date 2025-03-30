#include <iostream>

using namespace std;

int count_winners(int rocks, int scissors, int papers)
{
    int winners = 0;
    // 모두 같은 것을 내는 경우
    if ((rocks == 0 && scissors == 0 && papers != 0) ||
        (rocks != 0 && scissors == 0 && papers == 0) ||
        (rocks == 0 && scissors != 0 && papers == 0))
        return 0;

    // 가위바위보가 다 나온경우
    if (rocks != 0 && scissors != 0 && papers != 0) 
        return 0;

    // 승부가 나온경우
    if (rocks == 0) winners = scissors;
    if (papers == 0) winners = rocks;
    if (scissors == 0) winners = papers;

    return winners;
}

int match(int players)
{
    int rock = 0, scissor = 0, paper = 0;
    for (int i = 0; i < players; i++)
    {
        // 가위바위보 각각 1,2,3
        int player_choice;
        cin >> player_choice;

        switch (player_choice)
        {
            case 1: scissor++; break;
            case 2: rock++;    break;
            case 3: paper++;   break;
            default:
                break;
        }
    }

    return count_winners(rock,scissor,paper);
}

int main()
{
    int testcase;
    cin >> testcase;

    for (int i = 0; i < testcase; i++)
    {
        int players; 
        cin >> players;
        int winners = match(players);
        cout << winners << endl;
    }

    return 0;
}