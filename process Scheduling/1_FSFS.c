/*
Given n processes with their burst times, the task is to find average waiting time and 
average turn around time using FCFS scheduling algorithm. 
*/

/*
1-  Input the processes along with their burst time (bt).
2-  Find waiting time (wt) for all processes.
3-  As first process that comes need not to wait so 
    waiting time for process 1 will be 0 i.e. wt[0] = 0.
4-  Find waiting time for all other processes i.e. for
     process i -> 
       wt[i] = bt[i-1] + wt[i-1] .
5-  Find turnaround time = waiting_time + burst_time 
    for all processes.
6-  Find average waiting time = 
                 total_waiting_time / no_of_processes.
7-  Similarly, find average turnaround time = 
                 total_turn_around_time / no_of_processes.
*/


#include<stdio.h>

void waiting_time(int processes[], int n, int bt[], int wt[]){
    //waiting time of process 0 is 0
    wt[0] = 0;
    for(int i = 1; i < n; i++){
        wt[i] = bt[i-1] + wt[i-1]; 
    }
}


void turn_around_time(int processes[], int n, int bt[],int wt[],int ta[]){
    //calculating turn around time by adding (wt[i] + bt[i])

    for(int i =0; i < n; i++){
        ta[i] = wt[i] + bt[i];
    }
}

void avg_time(int processes[], int n, int bt[]){
    int wt[n], ta[n], total_wt = 0, total_ta =0;

    //find waiting time
    waiting_time(processes, n, bt, wt);

    //find turn around time
    turn_around_time(processes, n, bt, wt, ta);

    //Display processes along with all details 
    printf("Processes\tBurst time\tWaiting time\tTurn around time\n"); 

    for(int i = 0; i < n; i++){
        total_wt += wt[i];
        total_ta += ta[i];

        printf("%d\t\t %d\t\t %d\t\t %d\n", processes[i], bt[i], wt[i], ta[i]);
    }
    
    float avg_wt = (float) total_wt / (float) n;
    float avg_ta = (float) total_ta/ (float) n;

    printf("Average waiting time is : %f\n", avg_wt);
    printf("Average turn around time is : %f\n", avg_ta);
}

int main(){
    int processes[] = {1,2,3,4};
    int n = sizeof processes / sizeof processes[0];

    int burst_time[] = {10, 13, 2,5};

    avg_time(processes, n, burst_time);
    return 0;
}
