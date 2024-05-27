#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int pid;
    int arrival_time;
    int burst_time;
    int waiting_time;
} Process;

void fcfs_scheduling(Process* processes, int n) {
    // 도착 시간 순으로 프로세스 정렬하기
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].arrival_time > processes[j + 1].arrival_time) {
                Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }

    // FCFS 스케줄링 수행하기
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

    // 프로세스 개수 입력받기
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // 프로세스 정보 입력받기
    processes = (Process*)malloc(n * sizeof(Process));
    for (i = 0; i < n; i++) {
        printf("Enter process %d arrival time and burst time: ", i + 1);
        scanf("%d %d", &processes[i].arrival_time, &processes[i].burst_time);
        processes[i].pid = i + 1;
    }

    // FCFS 스케줄링 수행하기
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