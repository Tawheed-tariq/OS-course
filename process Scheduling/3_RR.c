#include <stdio.h>

#define MAX_PROCESSES 10

typedef struct {
    int pid;        // Process ID
    int burst_time; // Burst time
    int remaining_time; // Remaining time
    int arrival_time; // Arrival time
    int waiting_time; // Waiting time
    int turnaround_time; // Turnaround time
} Process;

void roundRobinScheduling(Process processes[], int n, int quantum) {
    int time = 0; // Current time
    int processes_completed = 0;
    int waiting_time_sum = 0;
    int turnaround_time_sum = 0;

    while (processes_completed < n) {
        int done = 1; // Check if all processes are done

        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= time && processes[i].remaining_time > 0) {
                done = 0; // At least one process is not done

                if (processes[i].remaining_time > quantum) {
                    time += quantum;
                    processes[i].remaining_time -= quantum;
                    printf("Process %d executed for %d units. Remaining time: %d\n",
                           processes[i].pid, quantum, processes[i].remaining_time);
                } else {
                    time += processes[i].remaining_time;
                    printf("Process %d executed for %d units. Remaining time: 0\n",
                           processes[i].pid, processes[i].remaining_time);
                    processes[i].remaining_time = 0;
                    processes_completed++;

                    processes[i].turnaround_time = time - processes[i].arrival_time;
                    processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;

                    turnaround_time_sum += processes[i].turnaround_time;
                    waiting_time_sum += processes[i].waiting_time;

                    printf("Process %d completed at time %d\n", processes[i].pid, time);
                    printf("Process %d Waiting Time: %d, Turnaround Time: %d\n\n",
                           processes[i].pid, processes[i].waiting_time, processes[i].turnaround_time);
                }
            }
        }

        if (done) {
            time++;
        }
    }

    printf("\nAverage Waiting Time: %.2f\n", (float)waiting_time_sum / n);
    printf("Average Turnaround Time: %.2f\n", (float)turnaround_time_sum / n);
}

int main() {
    int n; // Number of processes
    int quantum; // Time quantum
    Process processes[MAX_PROCESSES];

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter the time quantum: ");
    scanf("%d", &quantum);

    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        printf("Enter arrival time for process %d: ", processes[i].pid);
        scanf("%d", &processes[i].arrival_time);
        printf("Enter burst time for process %d: ", processes[i].pid);
        scanf("%d", &processes[i].burst_time);
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].waiting_time = 0;
        processes[i].turnaround_time = 0;
    }

    printf("\nStarting Round Robin Scheduling...\n\n");
    roundRobinScheduling(processes, n, quantum);

    return 0;
}
