#include <stdio.h>

typedef struct {
    int pid;
    int burst_time;
    int remaining_time;
    int priority;
    int wait_time;
    int turnaround_time;
} Process;

void preemptivePriorityScheduling(Process proc[], int n) {
    int total_time = 0, completed = 0;
    int min_priority, idx;
    
    while (completed != n) {
        min_priority = 9999;
        idx = -1;
        
        for (int i = 0; i < n; i++) {
            if (proc[i].remaining_time > 0 && proc[i].priority < min_priority) {
                min_priority = proc[i].priority;
                idx = i;
            }
        }
        
        if (idx != -1) {
            proc[idx].remaining_time--;
            total_time++;
            
            if (proc[idx].remaining_time == 0) {
                proc[idx].turnaround_time = total_time;
                proc[idx].wait_time = total_time - proc[idx].burst_time;
                completed++;
            }
        } else {
            total_time++;
        }
    }
    
    int total_wait_time = 0, total_turnaround_time = 0;
    
    printf("PID\tBurst Time\tPriority\tWait Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", proc[i].pid, proc[i].burst_time, proc[i].priority, proc[i].wait_time, proc[i].turnaround_time);
        total_wait_time += proc[i].wait_time;
        total_turnaround_time += proc[i].turnaround_time;
    }
    
    printf("Average Wait Time: %.2f\n", (float)total_wait_time / n);
    printf("Average Turnaround Time: %.2f\n", (float)total_turnaround_time / n);
}

int main() {
    Process proc[] = {{1, 10, 10, 3, 0, 0}, {2, 1, 1, 1, 0, 0}, {3, 2, 2, 4, 0, 0}, {4, 1, 1, 5, 0, 0}, {5, 5, 5, 2, 0, 0}};
    int n = sizeof(proc) / sizeof(proc[0]);
    
    preemptivePriorityScheduling(proc, n);
    
    return 0;
}

