.PHONY: all clean libclean

all: build

build:
	@$(MAKE) -C Plutonium/
	@$(MAKE) -C SkylanderDumper/

libclean:
	@$(MAKE) -C Plutonium/ clean
	
clean:
	@$(MAKE) -C SkylanderDumper/ clean