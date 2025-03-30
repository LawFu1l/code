#include <iostream>
#include <vector>

using namespace std;

char grade(int score)
{
    if (90 <= score && score <= 100) return 'A';
    if (80 <= score && score < 90) return 'B';
    if (70 <= score && score < 80) return 'C';
    if (60 <= score && score < 70) return 'D';
    return 'F';
}

vector<int> grading(vector<int>& scores)
{
    //0번째 인덱스부터 4번째 인덱스까지 각각 ABCDF
    vector<int> graded{0,0,0,0,0};
    int size = scores.size();
    for (int i = 0; i < size; i++)
    {
        char grade_of_student = grade(scores[i]);
        switch (grade_of_student)
        {
            case 'A':
                graded[0]++;
                break;
            case 'B':
                graded[1]++;
                break;
            case 'C':
                graded[2]++;
                break;
            case 'D':
                graded[3]++;
                break;
            case 'F':
                graded[4]++;
                break;
        }
    }
    return graded;
}

vector<int> getscore()
{
    vector<int> scores;
    int student_num;
    cin >> student_num;
    for (int i = 0; i < student_num; i++)
    {
        int score;
        cin >> score;
        scores.push_back(score);
    }
    return scores;
}

int main()
{
    int testcase;
    cin >> testcase;
    for (int i = 0; i < testcase; i++)
    {
        vector<int> scores = getscore();
        vector<int> graded = grading(scores);
        for (auto& e : graded)
            cout << e << " ";
        cout << endl;
    }
    return 0;
}