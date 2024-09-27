#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define inputFile "johnson_2_machines.inp"
#define outputFile "johnson_2_machines.out"

// Khai báo cấu trúc công việc
struct job
{
    int id;      // ID công việc
    int time_1;  // Thời gian trên máy 1
    int time_2;  // Thời gian trên máy 2
};

vector<job> jobs;
int n;
vector<int> schedule;
int totalTime;

void input()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    freopen(inputFile, "r", stdin);

    cin >> n;

    job j;
    for (int i = 0; i < n; ++i)
    {
        cin >> j.id >> j.time_1 >> j.time_2;
        jobs.push_back(j);
    }
}

// Hàm dùng cho sắp xếp tăng dần nhóm 1
bool compare_group_1(const job &a, const job &b)
{
    return a.time_1 < b.time_1;
}

// Hàm dùng cho sắp xếp tăng dần nhóm 2
bool compare_group_2(const job &a, const job &b)
{
    return a.time_2 > b.time_2;
}


// Hàm tính tổng thời gian hoàn thành tất cả công việc
int calculateTime(vector<job>& J, vector<int>& S)
{
    vector<int> start_1(n), finish_1(n), start_2(n), finish_2(n);

    // Thời điểm bắt đầu và kết thúc của công việc đầu tiên
    start_1[0] = 0;
    finish_1[0] = J[S[0] - 1].time_1;

    start_2[0] = finish_1[0];
    finish_2[0] = start_2[0] + J[S[0] - 1].time_2;

    // Thời điểm bắt đầu và kết thúc của các công việc còn lại
    for (int i = 1; i < n; i++) {
        start_1[i] = finish_1[i - 1];
        finish_1[i] = start_1[i] + J[S[i] - 1].time_1;

        start_2[i] = max(finish_1[i], finish_2[i - 1]);
        finish_2[i] = start_2[i] + J[S[i] - 1].time_2;
    }

    // Thời gian hoàn thành của công việc cuối cùng trên máy 2
    return finish_2[n - 1];
}


void process()
{
    // Phân nhóm
    // Nhóm 1: các công việc có time_1 <= time_2
    // Nhóm 2: các công việc có time_1 > time_2
    vector<job> group_1, group_2;

    for (int i = 0; i < n; ++i)
    {
        if (jobs[i].time_1 <= jobs[i].time_2)
        {
            group_1.push_back(jobs[i]);
        }
        else
        {
            group_2.push_back(jobs[i]);
        }
    }

    // Sắp xếp nhóm 1 theo time_1 tăng dần
    sort(group_1.begin(), group_1.end(), compare_group_1);
    
    // Sắp xếp nhóm 2 theo time_2 giảm dần
    sort(group_2.begin(), group_2.end(), compare_group_2);

    // Lần lượt đưa nhóm 1 và nhóm 2 vào lịch
    for (int i = 0; i < group_1.size(); ++i)
    {
        schedule.push_back(group_1[i].id);
    }

    for (int i = 0; i < group_2.size(); ++i)
    {
        schedule.push_back(group_2[i].id);
    }

    // Tính tổng thời gian hoàn thành các công việc
    totalTime = calculateTime(jobs, schedule);
}


void output()
{
    freopen(outputFile, "w", stdout);

    for (int i = 0; i < schedule.size(); ++i)
    {
        cout << schedule[i] << ' ';
    }

    cout << '\n';

    cout << totalTime;
}


int main()
{
    input();
    process();
    output();

    return 0;
}