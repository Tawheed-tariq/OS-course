/*
In shortest job first those processes which have less cpu burst time will be run first on cpu
*/

/*Algorithm
  -  Sort all the processes according to the arrival time. 

  -  Then select that process that has minimum arrival time and minimum Burst time. 

  -  After completion of the process make a pool of processes that arrives afterward till
    the completion of the previous process and select that process among the pool which is 
    having minimum Burst time. 
*/

#include<stdio.h>


int main(){
    // Matrix for storing Process Id, Burst
    // Time, Average Waiting Time & Average
    // Turn Around Time.
    int A[100][4];
    int i, j,  n, total = 0, index, temp;

    float avg_wt, avg_ta;

    printf("Enter number of processes : ");
    scanf("%d", &n);

    printf("Enter Burst time: \n");
    for(i = 0; i< n; i++){
        A[i][0] = i+1;
        printf("P%d : ", i+1);
        scanf("%d", &A[i][1]);
    }

    // Sorting process according to their Burst Time.
    for (i = 0; i < n; i++) {
        index = i;
        for (j = i + 1; j < n; j++)
            if (A[j][1] < A[index][1])
                index = j;
        //sort burst time
        temp = A[i][1];
        A[i][1] = A[index][1];
        A[index][1] = temp;

        //sort process number
        temp = A[i][0];
        A[i][0] = A[index][0];
        A[index][0] = temp;
    }

    //waiting time calculation
    A[0][2] = 0; //fisrt process has waiting time 0
    for (i = 1; i < n; i++) {
        A[i][2] = 0;
        for (j = 0; j < i; j++)
            A[i][2] += A[j][1];
        total += A[i][2];
    }

    avg_wt = (float)total / n;
    total = 0;

    //Display processes along with all details 
    printf("Processes\tBurst time\tWaiting time\tTurn around time\n");

    for (i = 0; i < n; i++) {
        A[i][3] = A[i][1] + A[i][2];
        total += A[i][3];
        printf("P%d\t\t %d\t\t %d\t\t %d\n", A[i][0],
               A[i][1], A[i][2], A[i][3]);
    }
    avg_ta = (float)total / n;
    printf("Average Waiting Time= %f", avg_wt);
    printf("\nAverage Turnaround Time= %f", avg_ta);
}

