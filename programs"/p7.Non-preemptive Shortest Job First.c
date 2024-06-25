#include <stdio.h>

typedef struct {
    int pid;
    int burst_time;
    int wait_time;
    int turnaround_time;
} Process;

void sortProcessesByBurstTime(Process proc[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (proc[i].burst_time > proc[j].burst_time) {
                Process temp = proc[i];
                proc[i] = proc[j];
                proc[j] = temp;
            }
        }
    }
}

void sjfScheduling(Process proc[], int n) {
    sortProcessesByBurstTime(proc, n);
    
    int wait_time = 0, total_wait_time = 0;
    int total_turnaround_time = 0;
    
    printf("PID\tBurst Time\tWait Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        proc[i].wait_time = wait_time;
        proc[i].turnaround_time = wait_time + proc[i].burst_time;
        printf("%d\t%d\t\t%d\t\t%d\n", proc[i].pid, proc[i].burst_time, proc[i].wait_time, proc[i].turnaround_time);
        
        total_wait_time += proc[i].wait_time;
        total_turnaround_time += proc[i].turnaround_time;
        wait_time += proc[i].burst_time;
    }
    
    printf("Average Wait Time: %.2f\n", (float)total_wait_time / n);
    printf("Average Turnaround Time: %.2f\n", (float)total_turnaround_time / n);
}

int main() {
    Process proc[] = {{1, 6}, {2, 8}, {3, 7}, {4, 3}};
    int n = sizeof(proc) / sizeof(proc[0]);
    
    sjfScheduling(proc, n);
    
    return 0;
}

