/*

@Authour: Saugata Roy Arghya
@Institute: KUET

*/


#include <bits/stdc++.h>
using namespace std;

struct Process {
    int processNumber;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int completedTime;
};




bool compareArrivalTime(const Process& a, const Process& b) {
    return a.arrivalTime < b.arrivalTime;
}

int main() {
    int numProcesses;
    cout << "Enter the number of processes: ";
    cin >> numProcesses;

    vector<Process> processes(numProcesses);
    
    cout << "Enter the arrival time, and burst time for each process:\n";
    for (int i = 0; i < numProcesses; i++) {
        processes[i].processNumber = i + 1;
        cin >> processes[i].arrivalTime >> processes[i].burstTime;
        processes[i].remainingTime = processes[i].burstTime;
    }

    sort(processes.begin(), processes.end(), compareArrivalTime);

    int currentTime{0};
    vector<int> ganttChart;
    int completed{0};
    
    while (completed < numProcesses) {
        int shortestProcess = -1;
        int shortestTime = INT_MAX;

        for (int i = 0; i < numProcesses; i++) {
            if (processes[i].arrivalTime <= currentTime && processes[i].remainingTime < shortestTime && processes[i].remainingTime > 0) {
                shortestProcess = i;
                shortestTime = processes[i].remainingTime;
            }
        }

        if (shortestProcess == -1) {
            currentTime++;
            ganttChart.push_back(0);
        } else {
            processes[shortestProcess].remainingTime--;
            currentTime++;
            ganttChart.push_back(processes[shortestProcess].processNumber);

            if (processes[shortestProcess].remainingTime == 0) {
                completed++;
                processes[shortestProcess].completedTime = currentTime;
                //int completionTime = currentTime;
                //processes[shortestProcess].remainingTime = completionTime - processes[shortestProcess].arrivalTime;
            }
        }
    }

    int idletime = 0;

    cout << "Gantt Chart: ";
    for (int process : ganttChart) {
        if (process == 0) {
            cout << "Idle ";
            idletime++;
            
        } else {
            cout << "P" << process << " ";
        }
    }
    cout << endl;



    cout<<"CPU Utilization: "<<(float)(currentTime-idletime)/currentTime<<endl;
    cout<<"Throughput: "<<(float)numProcesses/currentTime<<endl;


     float totalWaitingTime = 0;

    for (const Process& process : processes) {
        totalWaitingTime += process.completedTime - process.arrivalTime - process.burstTime;
    }    
    cout<<"Average Waiting Time: "<<totalWaitingTime/numProcesses<<endl;


    float totalTurnaroundTime = 0;
    for(const Process& process : processes){
        totalTurnaroundTime += process.completedTime - process.arrivalTime;
    }
    cout<<"Average Turnaround Time: "<<totalTurnaroundTime/numProcesses<<endl;



    int checkProcess = 1;

    int totalResponseTime = 0;
    for(size_t i = 0; i<ganttChart.size();i++)
    {
        if(ganttChart[i] == checkProcess)
        {
            totalResponseTime += i - processes[checkProcess-1].arrivalTime;
            checkProcess++;
            i = 0;
        }
        if(checkProcess>numProcesses)
        {
            break;
        }

    }
    //cout<<totalResponseTime<<endl;
    cout<<"Average Response Time: "<<(float)totalResponseTime/numProcesses<<endl;
    return 0;
}
