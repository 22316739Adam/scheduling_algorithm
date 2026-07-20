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



