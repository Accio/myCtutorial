DOXYGEN=doxygen

all:
	$(MAKE) -C fork
	$(MAKE) -C malloc
	$(MAKE) -C sizeof
	$(MAKE) -C rank

doc:
	$(DOXYGEN) Doxyfile

.PHONY=doc