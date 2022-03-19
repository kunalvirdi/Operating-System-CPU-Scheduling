#include <bits/stdc++.h>
using namespace std;

//Priority CPU scheduling Higher the priority CPU will schedule that task

struct Process
{
    int priority;
    int id;
    int aTime;
    int bTime;
    int cTime;
    int tatTime;
    int wTime;
    int rTime;
};

int findMaxCTime(int cTime[], int n) //Find maximum current time the cpu is working
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

//Set the processes so that we can find the maximum process/job according to priority
Process setProcess()
{
    Process p;
    p.id = INT_MAX;
    p.aTime = INT_MAX;
    p.bTime = INT_MAX;
    p.priority = INT_MIN;
    return p;
}

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
        cout << "Enter Priority, Arrival time and Burst Time of process " << i + 1 << ":";
        p[i].id = i + 1;
        cin >> p[i].priority>> p[i].aTime >> p[i].bTime;
    }


    vector<Process> pp; //Auxillary space to store all the tasks that come on same time/ maxTime
    pp.push_back(p[0]);
    int cTime[n+1] = {0}; //It will track the completion time of all the processes
    cTime[p[0].id] = 1;
    pp[0].bTime--;

    int resTime[n+1]; //It will track first timing when CPU will schedule
    for (int i = 0; i < n+1;i++){
        resTime[i] = -1; 
    }
    resTime[1] = 0;
    bool flag = true;

    //Run until all the processes in ready queue will not finished
    while(flag){
        int maxCtime = findMaxCTime(cTime, n + 1); //Get the maximum time present at the moment

        for (int j = 1; j < n;j++){
            if(p[j].aTime==maxCtime){ //Collect all the processes arrives at current time.
                pp.push_back(p[j]);
            }
        }

        Process pr = setProcess(); //Find the process according to the priority
        for (int j = 0; j < pp.size();j++){
            if(pp[j].bTime!=0){
                if(pr.priority<pp[j].priority){
                    pr = pp[j];
                }
            }
        }
        if(resTime[pr.id]==-1){ //will set the timing of each process/job arrives first time
            resTime[pr.id ] = maxCtime;
        }
        cTime[pr.id] = maxCtime + 1;
        pp[pr.id - 1].bTime--;

        for (int j = 0;j<pp.size();j++){
            flag = false;
            if(pp[j].bTime!=0){
                flag = true;
                break;
            }
        }
        if(!flag){
            break;
        }
    }

    for (int i = 0; i < n + 1;i++){
        cout << resTime[i] << " ";
    }
}