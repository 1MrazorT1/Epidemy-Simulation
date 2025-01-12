# Epidemic Simulation Project

## Team Members
- **BRIDA Mohamed Taha**
- **LY Johann**
- **TOUJANI Mohamed**
- **ZOUGGARI Taha**

## Project Description
This project simulates the spread of an epidemic within a city. Two approaches were used: a monothread simulation and a multithread one. Using various mechanisms such as inter-process communication, shared memory, and threading. The goal is to model citizen roles and their interactions to manage and mitigate the contamination.

## Commits History
To view the full history of commits on this project, please make sure that you are on the homepage of the projecture's gitlab repository. Once you enter any of the folders, you will no longer be able to see them because the organization of the root happened at late stages of development.

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
2. ```bash
   make
   ```
   This way you will compile the two parts of the project. Even if you see errors in the compilation, that can be related to only one method and not both of them. So to choose what method to run, please follow the instructions below:
#### Monothread_simulation
1. Run the sim:
   ```bash
   make run-mono
   ```
2. Clean:
   ```bash
   make clean-mono
   ```

#### Multithread_simulation
1. Run the sim:
   ```bash
   make run-multi
   ```
2. Clean:
   ```bash
   make clean-multi
   ```

#### For full cleaning
3. Full cleaning of the project:
   ```bash
   make clean
   ```

## Project Structure
```bash
epidemy-os/
├── Makefile
├── README.md
├── monothread_simulation/
│   ├── Makefile
│   ├── README.md
│   ├── include/            
│   ├── lib/               
│   │   └── slope/         
│   ├── out/                
│   ├── resources/          
│   ├── src/               
│   │   ├── citizen_manager/
│   │   ├── epidemic_sim/  
│   │   ├── timer/         
│   │   └── viewer/         
│   └── tests/              
├── multi-thread_simulation/
│   ├── Makefile
│   ├── Doxyfile            
│   ├── docs/              
│   │   └── html/          
│   ├── out/                
│   ├── resources/          
│   ├── src/                
│   │   ├── epidemic_sim/   
│   │   ├── timer/         
│   │   └── viewer/         
│   └── include/   
```         


## Report Location
Refer to the report in the `doc/` folder for a detailed explanation of the project design, challenges encountered, and solutions implemented.
