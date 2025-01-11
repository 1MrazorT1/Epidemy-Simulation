#include <stdio.h>
#include <stdlib.h>

#include "epidemic_sim.h"
#include "logger.h"

/*
 * Runs the Epidemic Simulation process.
 */
int main(int argc, char *argv[]) {
	SimulationMemory* memory;
    memory = setup_shared_memory();
    initialize_memory(memory);
    start_simulation();
	exit(EXIT_SUCCESS);
}
