all:
	$(MAKE) -C access_forbidden
	$(MAKE) -C signal_handler
	$(MAKE) -C ts_counter
	$(MAKE) -C busy_work
	$(MAKE) -C check_tsx
	$(MAKE) -C meltdown
	
	
clean:
	$(MAKE) -C access_forbidden clean
	$(MAKE) -C signal_handler clean
	$(MAKE) -C ts_counter clean
	$(MAKE) -C busy_work clean
	$(MAKE) -C check_tsx clean
	$(MAKE) -C meltdown clean