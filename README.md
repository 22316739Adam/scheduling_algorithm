# ⚙️ CPU Process Scheduling Simulator

An academic project that demonstrates how operating systems schedule CPU processes using three classical scheduling algorithms. The application provides an interactive Windows Forms interface while leveraging a C++ backend for process scheduling.

## 📖 Overview

CPU scheduling is a fundamental concept in operating systems, responsible for determining the order in which processes access the CPU. This project simulates the behavior of three widely used scheduling algorithms:

- **First Come First Served (FCFS)**
- **Shortest Job First (Preemptive)**
- **Priority Scheduling (Preemptive)**

The simulator allows users to load process information from a text file, visualize the scheduling sequence, and observe how different algorithms affect process execution.

## 🛠️ Technology stack

|     Layer      | Technology |
|----------------|------------|
|    Backend     |    C++     |
|   Interface    |     C#     |
|      GUI       |   .NET     |
| API connection |    DLL     |

## 🏗️ System Architecture

              User Input (input.txt)
                        │
                        ▼
             Windows Forms Interface
              (C# / .NET Framework)
                        │
                        ▼
                 DLL Function Calls
                  (imp.dll Export)
                        │
                        ▼
               C++ Scheduling Engine
                        │
        ┌───────────────┼───────────────┐
        ▼               ▼               ▼
      FCFS        SJF (Preemp.)   Priority (Preemp.)
                        │
                        ▼
                Scheduling Results
                        │
                        ▼
          Process Execution View / Error log 


## 📸 Screenshots

|[Interface](imgs/int.png)

|[input_format](imgs/out.png)

|[output_format](imgs/inp.png)

## 📄 Data format
### Input.txt

| Process ID | Arrival time | Burst time | Priority|
|------------|--------------|------------|---------|
|1           |0             |7           |2        |
|2           |2             |4           |1        |
|3           |4             |1           |3        |
|4           |6             |4           |2        |
|5           |8             |6           |4        |

### Output.txt

|  Algorithm | Process order | Average waiting time |
|------------|--------------|-----------------------|
|FCFS           |1->2->3->4           |5.2          |
|SJF p        |3->2->4->1->5        |3.8       |
|Priority p           |2->4->1->3->5            |5.4          |

## Analysis

Each process sequence fed by the user through the input file is implemented using a linked list. An unordered set is then used to store the processes waiting to be scheduled. The project features a Windows Forms interface developed in C# on the .NET Framework, while the scheduling algorithms are implemented in C++. The connection between the interface and the algorithms is established via a DLL, which exports the necessary functions for the C# application to call. Any error that would be caught during the running of the algorithms will be stoored to the debug.txt file. 

## 🚀 Installation

The project could be installed after downloading the latest release available which automatically ensures the installation of all the necessary files for it. A demo input file would be also available where the data could be altered, and then it should be uploaded to the app run through wkin.exe. Next, an output file is automatically generated where the results are shown. 
Alternatively, the repository couuld be cloned through
```bash
git clone https://github.com/22316739Adam/scheduling_algorithm.git
```
and then the project should be built in release mode where the imp.dll will have all the function calls required for the application. 
