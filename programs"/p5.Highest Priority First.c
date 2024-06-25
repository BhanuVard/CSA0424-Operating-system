#include <stdio.h>

typedef struct {
    int pid;
    int burst_time;
    int priority;
} Process;

void sortProcessesByPriority(Process proc[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (proc[i].priority > proc[j].priority) {
                Process temp = proc[i];
                proc[i] = proc[j];
                proc[j] = temp;
            }
        }
    }
}

void priorityScheduling(Process proc[], int n) {
    sortProcessesByPriority(proc, n);
    
    int wait_time = 0, total_wait_time = 0;
    int total_turnaround_time = 0;
    
    printf("PID\tBurst Time\tPriority\tWait Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        int turnaround_time = wait_time + proc[i].burst_time;
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", proc[i].pid, proc[i].burst_time, proc[i].priority, wait_time, turnaround_time);
        
        total_wait_time += wait_time;
        total_turnaround_time += turnaround_time;
        wait_time += proc[i].burst_time;
    }
    
    printf("Average Wait Time: %.2f\n", (float)total_wait_time / n);
    printf("Average Turnaround Time: %.2f\n", (float)total_turnaround_time / n);
}

int main() {
    Process proc[] = {{1, 10, 3}, {2, 1, 1}, {3, 2, 4}, {4, 1, 5}, {5, 5, 2}};
    int n = sizeof(proc) / sizeof(proc[0]);
    
    priorityScheduling(proc, n);
    
    return 0;
}

