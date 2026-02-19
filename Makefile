.PHONY: all clean libclean

all: build

build:
	@$(MAKE) -C dependencies/Plutonium/
	@$(MAKE) -C SkylanderDumper/

libclean:
	@$(MAKE) -C dependencies/Plutonium/ clean
	
clean:
	@$(MAKE) -C SkylanderDumper/ clean