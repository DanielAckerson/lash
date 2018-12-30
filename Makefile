all:
	$(MAKE) -C src

.PHONY: clean
clean:
	$(MAKE) clean -C src
