#include <stdio.h>

typedef struct {
    int pid;
    int burst_time;
    int remaining_time;
    int wait_time;
    int turnaround_time;
} Process;

void roundRobinScheduling(Process proc[], int n, int quantum) {
    int time = 0, completed = 0;
    
    while (completed != n) {
        for (int i = 0; i < n; i++) {
            if (proc[i].remaining_time > 0) {
                if (proc[i].remaining_time > quantum) {
                    time += quantum;
                    proc[i].remaining_time -= quantum;
                } else {
                    time += proc[i].remaining_time;
                    proc[i].wait_time = time - proc[i].burst_time;
                    proc[i].turnaround_time = time;
                    proc[i].remaining_time = 0;
                    completed++;
                }
            }
        }
    }
    
    int total_wait_time = 0, total_turnaround_time = 0;
    
    printf("PID\tBurst Time\tWait Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\n", proc[i].pid, proc[i].burst_time, proc[i].wait_time, proc[i].turnaround_time);
        total_wait_time += proc[i].wait_time;
        total_turnaround_time += proc[i].turnaround_time;
    }
    
    printf("Average Wait Time: %.2f\n", (float)total_wait_time / n);
    printf("Average Turnaround Time: %.2f\n", (float)total_turnaround_time / n);
}

int main() {
    Process proc[] = {{1, 10, 10, 0, 0}, {2, 5, 5, 0, 0}, {3, 8, 8, 0, 0}};
    int n = sizeof(proc) / sizeof(proc[0]);
    int quantum = 2;
    
    roundRobinScheduling(proc, n, quantum);
    
    return 0;
}

