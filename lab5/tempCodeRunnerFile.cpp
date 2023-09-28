#include <iostream>
#include <vector>
#include <queue>
#include <iomanip>

using namespace std;

// Process structure
struct Process {
    int id;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int priority; // For SJF queue
    int completionTime;
};

// Function to simulate the multilevel feedback queue scheduler
void multilevelFeedbackQueue(vector<Process>& processes) {
    queue<Process> fcfsQueue;
    queue<Process> sjfQueue;
    queue<Process> rrQueue;

    int currentTime = 0;

    while (!processes.empty() || !fcfsQueue.empty() || !sjfQueue.empty() || !rrQueue.empty()) {
        // Move processes to appropriate queues based on arrival time
        while (!processes.empty() && processes.front().arrivalTime <= currentTime) {
            Process p = processes.front();
            processes.erase(processes.begin());

            if (p.priority == 0) {
                fcfsQueue.push(p);
            } else {
                sjfQueue.push(p);
            }
        }

        // Execute processes in the highest priority queue first
        if (!sjfQueue.empty()) {
            Process p = sjfQueue.front();
            sjfQueue.pop();
            cout << "Executing process " << p.id << " from SJF queue" << endl;
            // Simulate execution
            if (p.remainingTime > 1) {
                p.remainingTime--;
                sjfQueue.push(p); // Put it back in the queue
            } else {
                p.completionTime = currentTime + 1;
            }
        } else if (!fcfsQueue.empty()) {
            Process p = fcfsQueue.front();
            fcfsQueue.pop();
            cout << "Executing process " << p.id << " from FCFS queue" << endl;
            // Simulate execution
            if (p.remainingTime > 1) {
                p.remainingTime--;
                fcfsQueue.push(p); // Put it back in the queue
            } else {
                p.completionTime = currentTime + 1;
            }
        } else if (!rrQueue.empty()) {
            Process p = rrQueue.front();
            rrQueue.pop();
            cout << "Executing process " << p.id << " from RR queue" << endl;
            // Simulate execution
            if (p.remainingTime > 1) {
                p.remainingTime--;
                rrQueue.push(p); // Put it back in the queue
            } else {
                p.completionTime = currentTime + 1;
            }
        }

        currentTime++;
    }
}

int main() {
    vector<Process> processes = {
        {1, 0, 6, 6, 1, 0},
        {2, 1, 8, 8, 0, 0},
        {3, 2, 4, 4, 1, 0},
        {4, 3, 5, 5, 0, 0},
        {5, 4, 3, 3, 1, 0}
    };

    multilevelFeedbackQueue(processes);

    // Calculate turnaround time and waiting time
    double totalTurnaroundTime = 0;
    double totalWaitingTime = 0;

    cout << "\nProcess\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time" << endl;

    for (Process p : processes) {
        int turnaroundTime = p.completionTime - p.arrivalTime;
        int waitingTime = turnaroundTime - p.burstTime;
        totalTurnaroundTime += turnaroundTime;
        totalWaitingTime += waitingTime;

        cout << p.id << "\t" << p.arrivalTime << "\t\t" << p.burstTime << "\t\t" << p.completionTime << "\t\t" << turnaroundTime << "\t\t" << waitingTime << endl;
    }

    // Calculate and print average turnaround time and average waiting time
    double avgTurnaroundTime = totalTurnaroundTime / processes.size();
    double avgWaitingTime = totalWaitingTime / processes.size();

    cout << "\nAverage Turnaround Time: " << avgTurnaroundTime << endl;
    cout << "Average Waiting Time: " << avgWaitingTime << endl;

    return 0;
}
