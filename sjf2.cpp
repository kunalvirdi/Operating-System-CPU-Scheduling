#include<bits/stdc++.h>
using namespace std;

//Shortest Job First Preempitive

struct Process
{
    int id;
    int aTime;
    int bTime;
    int cTime;
    int tatTime;
    int wTime;
};

bool compATime(Process p1, Process p2)
{
    return p1.aTime < p2.aTime;
}

void printDetails(Process p[], int n)
{
    cout << "\nProcess Id  Arrival Time  Burst Time  Completion Time  T.A. Time  Waiting Time  Response Time" << endl;

    for (int i = 0; i < n; i++)
    {
        cout << " " << p[i].id << "\t\t" << p[i].aTime << "\t\t" << p[i].bTime << "\t\t"
             << p[i].cTime << "\t" << p[i].tatTime << "\t\t" << p[i].wTime << "\t\t" << endl;
    }
}

int findMaxCTime(int cTime[], int n)
{
    int max = -1;
    for (int i = 0; i < n; i++)
    {
        if (max < cTime[i])
        {
            max = cTime[i];
        }
    }
    return max;
}

Process setProcess()
{
    Process p;
    p.id = INT_MAX;
    p.aTime = INT_MAX;
    p.bTime = INT_MAX;
    return p;
}

int main(){
    int n;
    cout << "Enter number processes:";
    cin >> n;

    Process p[n], dummyP[n];
    for (int i = 0; i < n; i++)
    {
        cout << "Enter Arrival time and Burst Time of process " << i + 1 << ":";
        p[i].id = i + 1;
        cin >> p[i].aTime >> p[i].bTime;
        dummyP[i].id = i + 1;
        dummyP[i].aTime = p[i].aTime;
        dummyP[i].bTime = p[i].bTime;
    }
    sort(dummyP, dummyP + n, compATime);

    int cTime[n+1] = {0};
    vector<Process> pp(n + 1);
    pp[dummyP[0].id] = dummyP[0];
    cTime[dummyP[0].id] = 1;
    pp[dummyP[0].id].bTime--;
    int i = 1;
    bool flag = true;

    while(flag){
        int maxCTime = findMaxCTime(cTime, n + 1);

        for (int k = 0; k < pp.size(); k++)
        {
            flag = false;
            if (pp[k].bTime != 0)
            {
                flag = true;
                break;
            }
        }

        for (int j = 0; j < n;j++){
            if(dummyP[j].aTime==maxCTime){
                pp[dummyP[j].id] = dummyP[j];
            }
        }

        Process pr = setProcess();
        for (int j = 0; j < pp.size(); j++)
        {
            if (pp[j].id != 0 && pp[j].bTime != 0)
            {
                if (pp[j].bTime < pr.bTime)
                {
                    pr = pp[j];
                }
            }
        }
        i++;
        cTime[pr.id] = i;
        pp[pr.id].bTime--;
    }

    for (int i = 0; i < n;i++){
        p[i].cTime = cTime[i + 1];
    }

    for (int i = 0; i < n; i++)
    {
        p[i].tatTime = p[i].cTime - p[i].aTime;
        p[i].wTime = p[i].tatTime - p[i].bTime;
    }

    printDetails(p, n);

    return 0;
}