.PHONY: run-mono clean-mono run-multi clean-multi

run-mono:
	$(MAKE) -C monothread_simulation run

clean-mono:
	$(MAKE) -C monothread_simulation clean

run-multi:
	$(MAKE) -C multi-thread_simulation run

clean-multi:
	$(MAKE) -C multi-thread_simulation clean