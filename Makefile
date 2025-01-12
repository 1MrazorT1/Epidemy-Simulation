.PHONY: all clean run-mono clean-mono run-multi clean-multi

all:
	$(MAKE) -C monothread_simulation
	$(MAKE) -C multi-thread_simulation

clean:
	$(MAKE) -C monothread_simulation clean
	$(MAKE) -C multi-thread_simulation clean

run-mono:
	$(MAKE) -C monothread_simulation run

clean-mono:
	$(MAKE) -C monothread_simulation clean

run-multi:
	$(MAKE) -C multi-thread_simulation run

clean-multi:
	$(MAKE) -C multi-thread_simulation clean