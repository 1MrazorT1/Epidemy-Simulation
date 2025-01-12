# Epidemic Simulation Project

## Team Members
- **BRIDA Mohamed Taha**
- **LY Johann**
- **TOUJANI Mohamed**
- **ZOUGGARI Taha**

## Project Description
This project simulates the spread of an epidemic within a city. Two approaches were used: a monothread simulation and a multithread one. Using various mechanisms such as inter-process communication, shared memory, and threading. The goal is to model citizen roles and their interactions to manage and mitigate the contamination.

## Setup and Execution
### Prerequisites
- A Linux environment (for ncurses or graphical libraries).
- C compiler (e.g., `gcc`).

### Build Instructions
1. Clone the repository:
   ```bash
   git clone https://gitlab.ecole.ensicaen.fr/toujani/epidemy-os.git
   cd epidemy-os
   ```
#### Monothread_simulation
1. Build and run the sim:
   ```bash
   make run-mono
   ```
2. Clean:
   ```bash
   make clean-mono
   ```

#### Multithread_simulation
1. Build and run the sim:
   ```bash
   make run-multi
   ```
2. Clean:
   ```bash
   make clean-multi
   ```

## Project Structure
epidemy-os/ ├── Makefile ├── README.md ├── monothread_simulation/ │ ├── Makefile │ ├── README.md │ ├── include/ │ ├── lib/ │ │ └── slope/ │ ├── out/ │ ├── resources/ │ ├── src/ │ │ ├── citizen_manager/ │ │ ├── epidemic_sim/ │ │ ├── timer/ │ │ └── viewer/ │ └── tests/ ├── multi-thread_simulation/ │ ├── Makefile │ ├── Doxyfile │ ├── docs/ │ │ └── html/ │ ├── out/ │ ├── resources/ │ ├── src/ │ │ ├── epidemic_sim/ │ │ ├── timer/ │ │ └── viewer/ │ └── include/

## Additional Information
Refer to the report in the `doc/` folder for a detailed explanation of the project design, challenges encountered, and solutions implemented.
