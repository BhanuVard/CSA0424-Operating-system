#include <stdio.h>

typedef struct {
    int pid;
    int burst_time;
} Process;

void fcfsScheduling(Process proc[], int n) {
    int wait_time = 0, total_wait_time = 0;
    int total_turnaround_time = 0;
    
    printf("PID\tBurst Time\tWait Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        int turnaround_time = wait_time + proc[i].burst_time;
        printf("%d\t%d\t\t%d\t\t%d\n", proc[i].pid, proc[i].burst_time, wait_time, turnaround_time);
        
        total_wait_time += wait_time;
        total_turnaround_time += turnaround_time;
        wait_time += proc[i].burst_time;
    }
    
    printf("Average Wait Time: %.2f\n", (float)total_wait_time / n);
    printf("Average Turnaround Time: %.2f\n", (float)total_turnaround_time / n);
}

int main() {
    Process proc[] = {{1, 24}, {2, 3}, {3, 3}};
    int n = sizeof(proc) / sizeof(proc[0]);
    
    fcfsScheduling(proc, n);
    
    return 0;
}

