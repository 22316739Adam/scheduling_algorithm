#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_set>
#include "imp.h"

using namespace std;

// Constructing the node
process* createProcess(int id, int AT, int BT, int p) {
    process* newP = new process; 
    newP->id = id; 
    newP->arrival_time = AT; 
    newP->burst_time = BT; 
    newP->init_bust = BT; 
    newP->priority = p; 
    newP->next = NULL; 

    return newP; 
}

// At-End insertion to the linked list
void insertAtEnd(process* &header, process* &added) {
    if (header == NULL) {
        header = added; return; 
    }

    process* temp = header; 
    while(temp->next != NULL)
        temp = temp->next; 
    
    temp->next = added; 
}

// Converting the array, within structure, passed from C# interface to linked list
void array_to_ll(exporting_Pair* inp, process* &header) {
    for (int i=0; i< inp->n; i++) {
        exporting_process current = inp->tot_pro[i]; 
        process* temp = createProcess(current.id, current.arrival_time, current.burst_time, current.priority);
        insertAtEnd(header, temp);
    }
}

extern "C" __declspec(dllexport)
void fcfs(exporting_Pair* inp, const char* path) {
    int current_time=0, wt;
    float awt=0.0f;  

    process* header=nullptr; 
    array_to_ll(inp, header); 

    ofstream output(path); 
    output<<"FCFS: ";

    while (header != NULL) {
        current_time += header->burst_time; 
        wt = current_time - header->arrival_time - header->burst_time; 
        awt += wt; 
        output<<header->id<<":";
        
        header = header->next; 
    }
    
    awt /= inp->n; 
    output<<awt<<"\n";
    output.flush();
    output.close(); 
}

extern "C" __declspec(dllexport)
void sjf_preemptive(exporting_Pair* inp, const char* path) {
    int current_time=0, wt;
    float awt= 0.0f; 

    ofstream output(path, ios::app); 
    output<<"Sjf preemptive: ";

    unordered_set<process*> awaiting; 
    process *init= nullptr, *header= nullptr;

    array_to_ll(inp, header); 

    init = header;

    try {
    while(header) {
        if (header->next == NULL) {
            awaiting.insert(header); 
            break; 
        } 

        if (init->burst_time - (header->next->arrival_time - current_time) < 0) {
            while (init->burst_time != 0) {
                current_time++; 
                init->burst_time--; 
            }

            wt = current_time - init->arrival_time - init->init_bust;
            awt += wt;
            output<<init->id<<":";

            // Erasing the process from the awaiting set 
            awaiting.erase(init); 

            // Checking the set for nodes with less burst time
            init = *awaiting.begin(); // Assuming least bt is associated with one of the nodes
            int least_bt = init->burst_time; 
            for (auto &node : awaiting) {
                if (node->burst_time < least_bt) {
                    least_bt = node->burst_time; 
                    init = node; 
                }
            }
        }
        else {
            init->burst_time -= (header->next->arrival_time - current_time); 
            current_time = header->next->arrival_time; 

            if (init->burst_time == 0) {
                wt = current_time - init->arrival_time - init->init_bust;
                awt += wt;  
                output<<init->id<<":"; 

                awaiting.erase(init); 

                int least_bt = header->next->burst_time; 
                for (auto &node : awaiting) {
                    if (node->burst_time < least_bt) {
                        least_bt = node->burst_time; 
                        init = node; 
                    }
                }
            }
            else if (header->next->burst_time < init->burst_time) {
                init = header->next; 
                awaiting.insert(header); 
                }

            header = header->next; 
            if (header != init) 
                awaiting.insert(header); 
            }
        }

    // Processing what's left in the awaiting set
    while (!awaiting.empty()) {
        init = *awaiting.begin(); 
        int least_bt = init->burst_time; 
        for (auto &node : awaiting) {
                if (node->burst_time < least_bt) {
                    least_bt = node->burst_time; 
                    init = node; 
                }
            }

        while (init->burst_time != 0) {
                current_time++; 
                init->burst_time--; 
            }
        
        wt = current_time - init->arrival_time - init->init_bust;
        awt += wt;
        output<<init->id<<":";

        awaiting.erase(init); 
        }
    }
    catch (const std::exception& e) {
        ofstream debug("debug.txt");
        debug << "Exception: " << e.what() << "\n";
    } catch (...) {
        ofstream debug("debug.txt");
        debug << "Unknown exception caught\n";
    }

    awt /= inp->n; 
    output<<awt<<"\n";
    output.flush();
    output.close(); 
    }

extern "C" __declspec(dllexport)
void priority_preemptive(exporting_Pair* inp, const char* path) {
    int current_time=0, wt;
    float awt =0.0f;

    ofstream output(path, ios::app); 
    output<<"Priority preemptive: "; 

    unordered_set<process*> awaiting; 
    process *init= nullptr, *header= nullptr; 

    array_to_ll(inp, header); 

    init = header;

    try {
    while(header) {
        if (header->next == NULL) {
            awaiting.insert(header); 
            break; 
        } 

        if (init->burst_time - (header->next->arrival_time - current_time) < 0) {
            while (init->burst_time != 0) {
                current_time++; 
                init->burst_time--; 
            }

            wt = current_time - init->arrival_time - init->init_bust;
            awt += wt;
            output<<init->id<<":";

            awaiting.erase(init); 

            // Checking the set for nodes with higher priority
            init = *awaiting.begin();
            int least_pr = init->priority; 
            for (auto &node : awaiting) {
                if (node->priority < least_pr) {
                    least_pr = node->priority; 
                    init = node; 
                    }
                }
            
            if (current_time == header->next->arrival_time && header->next->priority < init->priority) 
                init = header->next; 
        }
        else {
            init->burst_time -= (header->next->arrival_time - current_time); 
            current_time = header->next->arrival_time; 

            if (header->burst_time == 0) {
                wt = current_time - init->arrival_time - init->init_bust;
                awt += wt; 
                output<<init->id<<":"; 
                
                awaiting.erase(init); 
            
                init = *awaiting.begin();
                int least_pr = init->priority; 
                for (auto &node : awaiting) {
                    int least_pr = header->next->priority; 
                    if (node->priority < least_pr) {
                        least_pr = node->priority; 
                        init = node; 
                    }
                }
            }
            else if (header->next->priority < init->priority) {
                init = header->next; 
                awaiting.insert(header); 
                }

            header = header->next; 
            if (header != init) 
                awaiting.insert(header); 
            }
        }

    while (!awaiting.empty()) {
        init = *awaiting.begin();
        int least_pr = init->priority; 
        for (auto &node : awaiting) {
            if (node->priority < least_pr) {
                least_pr = node->priority; 
                init = node; 
                }
            }

        while (init->burst_time != 0) {
                current_time++; 
                init->burst_time--; 
            }
        
        wt = current_time - init->arrival_time - init->init_bust;
        awt += wt;
        output<<init->id<<":";
        
        awaiting.erase(init); 
    }
    awt /= inp->n; 
    output<<awt<<"\n"; 
    output.flush();
    output.close(); 
    }
    catch (const std::exception& e) {
        ofstream debug("debug.txt");
        debug << "Exception: " << e.what() << "\n";
    } catch (...) {
        ofstream debug("debug.txt");
        debug << "Unknown exception caught\n";
    }
}

extern "C" __declspec(dllexport)
// Building structure from the C# interface input
void build_input(const char* path, exporting_Pair* inp) {
    int n=-1; 
    string line; 
    ifstream input_file(path); 
    
    // Checking each line to store attributes of each process
    while (getline(input_file, line)) {
        n++; // Storing number of processes

        istringstream iss(line); 

        string value; 
        vector<string> data; 
        while (getline(iss, value, ';'))
            data.push_back(value); 
            
        vector<int> converted; 
        for (auto& s:data) {
            converted.push_back(stoi(s)); 
        }

        inp->tot_pro[n] = {converted[0], converted[1], converted[2], converted[3]}; 
    }

    inp->n = ++n; 
}



