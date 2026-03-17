#pragma once
#define MAX 10

#ifdef __cplusplus
extern "C" {
#endif

// Node
struct process {
    int id, arrival_time, burst_time, init_bust, priority; 
    struct process *next;
}; 

struct Pair {
    process* p; 
    int n; 
}; 


struct exporting_process {
    int id, arrival_time, burst_time, priority; 
};

// Structure for the user-input to be stored
struct exporting_Pair {
    exporting_process tot_pro[MAX]; // Array of structures
    int n;  
};

__declspec(dllexport) void fcfs(exporting_Pair* inp, const char* path); 
__declspec(dllexport) void sjf_preemptive(exporting_Pair* inp, const char* path); 
__declspec(dllexport) void priority_preemptive(exporting_Pair* inp, const char* path);
__declspec(dllexport) void build_input(const char* path, exporting_Pair* inp); 

#ifdef __cplusplus
}   
#endif