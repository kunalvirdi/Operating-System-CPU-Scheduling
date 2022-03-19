#include <bits/stdc++.h>
using namespace std;

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

void printDetails(Process p[], int n)
{
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
    for (int i = 0; i < n; i++)
    {
        cout << "Enter Arrival time and Burst Time of process " << i + 1 << ":";
        p[i].id = i + 1;
        cin >> p[i].aTime >> p[i].bTime;
    }
    int cTime[n + 1]={0};
    int rTime[n];
    for (int i = 0; i < n;i++){
        rTime[i] = -1;
    }
    queue<Process> pq; //Queue of all the processes
    int i = 0,j=0;
    pq.push(p[0]);

    while(true){
        Process pr = pq.front(); //Get the first process present in the queue
        pq.pop();
        //Substract the burst time and record when the CPU will given to task first
        if(pr.bTime<2){
            if (rTime[pr.id - 1] == -1)
            {
                rTime[pr.id - 1] = i;
            }
            pr.bTime--;
            i++;
            cTime[pr.id] = i;
        }else{
            if (rTime[pr.id - 1] == -1)
            {
                rTime[pr.id - 1] = i;
            }
            pr.bTime -= 2;
            i += 2;
            cTime[pr.id] = i;
            
        }
        //Collect all tasks in queue so that we can schedule them
        for (int k = j + 1; k < n;k++){
            if(p[k].aTime<=i){
                pq.push(p[k]);
                j++;
            }
        }
        //if our present task's burst time not equal to zero/ our present task does not complete we again push into queue
        if(pr.bTime!=0){
            pq.push(pr);
        }
        if(pq.empty()){
            break;
        }
    }

    for (int i = 0; i < n;i++){
        p[i].cTime = cTime[i + 1];
    }

    for (int i = 0; i < n; i++)
    {
        p[i].tatTime = p[i].cTime - p[i].aTime;
        p[i].wTime = p[i].tatTime - p[i].bTime;
        p[i].rTime = rTime[i] - p[i].aTime;
    }

    printDetails(p, n);

    return 0;
}