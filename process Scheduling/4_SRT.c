#include <stdio.h>
#include <limits.h>

#define MAX_PROCESSES 10

typedef struct {
    int pid;            // Process ID
    int arrival_time;   // Arrival time
    int burst_time;     // Burst time
    int remaining_time; // Remaining time
    int waiting_time;   // Waiting time
    int turnaround_time;// Turnaround time
} Process;

void shortestRemainingTime(Process processes[], int n) {
    int time = 0; // Current time
    int processes_completed = 0;
    int waiting_time_sum = 0;
    int turnaround_time_sum = 0;
    int shortest_index;
    int min_remaining_time;
    
    while (processes_completed < n) {
        // Find the process with the shortest remaining time at the current time
        shortest_index = -1;
        min_remaining_time = INT_MAX;
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= time && processes[i].remaining_time > 0) {
                if (processes[i].remaining_time < min_remaining_time) {
                    min_remaining_time = processes[i].remaining_time;
                    shortest_index = i;
                }
            }
        }

        if (shortest_index == -1) {
            // If no process is ready, increment time
            time++;
            continue;
        }

        // Execute the process with the shortest remaining time
        processes[shortest_index].remaining_time--;
        time++;

        // If the process is completed
        if (processes[shortest_index].remaining_time == 0) {
            processes_completed++;
            processes[shortest_index].turnaround_time = time - processes[shortest_index].arrival_time;
            processes[shortest_index].waiting_time = processes[shortest_index].turnaround_time - processes[shortest_index].burst_time;

            turnaround_time_sum += processes[shortest_index].turnaround_time;
            waiting_time_sum += processes[shortest_index].waiting_time;

            printf("Process %d completed at time %d\n", processes[shortest_index].pid, time);
            printf("Process %d Waiting Time: %d, Turnaround Time: %d\n",
                   processes[shortest_index].pid, processes[shortest_index].waiting_time, processes[shortest_index].turnaround_time);
        }
    }

    printf("\nAverage Waiting Time: %.2f\n", (float)waiting_time_sum / n);
    printf("Average Turnaround Time: %.2f\n", (float)turnaround_time_sum / n);
}

int main() {
    int n; // Number of processes
    Process processes[MAX_PROCESSES];

    printf("Enter the number of processes: ");
    scanf("%d", &n);

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

    printf("\nStarting Shortest Remaining Time Scheduling...\n\n");
    shortestRemainingTime(processes, n);

    return 0;
}
