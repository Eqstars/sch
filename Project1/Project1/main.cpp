#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int pid;
    int arrival_time;
    int burst_time;
    int waiting_time;
} Process;

void fcfs_scheduling(Process* processes, int n) {
    // ���� �ð� ������ ���μ��� �����ϱ�
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].arrival_time > processes[j + 1].arrival_time) {
                Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }

    // FCFS �����ٸ� �����ϱ�
    int current_time = 0;
    for (int i = 0; i < n; i++) {
        if (current_time < processes[i].arrival_time) {
            current_time = processes[i].arrival_time;
        }
        processes[i].waiting_time = current_time - processes[i].arrival_time;
        current_time += processes[i].burst_time;
    }
}

int main() {
    int n, i;
    Process* processes;

    // ���μ��� ���� �Է¹ޱ�
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // ���μ��� ���� �Է¹ޱ�
    processes = (Process*)malloc(n * sizeof(Process));
    for (i = 0; i < n; i++) {
        printf("Enter process %d arrival time and burst time: ", i + 1);
        scanf("%d %d", &processes[i].arrival_time, &processes[i].burst_time);
        processes[i].pid = i + 1;
    }

    // FCFS �����ٸ� �����ϱ�
    fcfs_scheduling(processes, n);
    int total_waiting_time = 0;
    printf("Process\tArrival Time\tBurst Time\tWaiting Time\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\n", processes[i].pid, processes[i].arrival_time, processes[i].burst_time, processes[i].waiting_time);
        total_waiting_time += processes[i].waiting_time;
    }
    printf("Average Waiting Time: %.2f\n", (float)total_waiting_time / n);
    free(processes);
    return 0;
}