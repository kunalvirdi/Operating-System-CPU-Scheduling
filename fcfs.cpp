#include<bits/stdc++.h>
using namespace std;

//First Come First Serve CPU scheduling 

struct Process
{
    int id;
    int aTime;
    int bTime;
    int cTime;
    int tatTime;
    int wTime;
    int rTime;
};

bool compATime(Process p1,Process p2){
    return p1.aTime < p2.aTime;
}

bool compId(Process p1,Process p2){
    return p1.id < p2.id;
}

void calculateCTime(Process p[],int n){
    for (int i = 1; i < n; i++)
    {
        if (p[i].aTime < p[i - 1].cTime) //if our arrival time of process lie in between the previous task's completetion time then we add burst time to that completion time else simply arrival time of that process+burst time of current process
        {
            p[i].cTime = p[i - 1].cTime + p[i].bTime;
        }
        else
        {
            p[i].cTime = p[i].aTime + p[i].bTime;
        }
    }
}

void printDetails(Process p[],int n){
    cout << "\nProcess Id  Arrival Time  Burst Time  Completion Time  T.A. Time  Waiting Time  Response Time" << endl;

    for (int i = 0; i < n; i++)
    {
        cout << " " << p[i].id << "\t\t" << p[i].aTime << "\t\t" << p[i].bTime << "\t\t"
             << p[i].cTime << "\t" << p[i].tatTime << "\t\t" << p[i].wTime << "\t\t" << p[i].rTime << endl;
    }
}

int main(){

    int n;
    cout << "Enter number processes:";
    cin >> n;

    Process p[n];
    for (int i = 0; i < n;i++){
        cout << "Enter Arrival time and Burst Time of process " << i + 1<<":";
        p[i].id = i + 1;
        cin >> p[i].aTime >> p[i].bTime;
    }

    sort(p, p + n,compATime); //Sort all the processes according to burst time

    p[0].cTime = p[0].bTime; //first task will execute first and completed.

    calculateCTime(p, n);

    for (int i = 0; i < n;i++){
        p[i].tatTime = p[i].cTime - p[i].aTime;
        p[i].wTime = p[i].tatTime - p[i].bTime;
        p[i].rTime = p[i].wTime;
    }

    sort(p, p + n, compId);

    printDetails(p, n);

    return 0;
}