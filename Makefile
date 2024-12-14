ROOT    = $(PWD)
SUBDIR  = $(ROOT)/src
#SUBDIR += $(ROOT)/project2

define make_subdir
@for i in $(SUBDIR); do   \
	( cd $$i && make $1 ) \
done;
endef

ALL: 
	$(call make_subdir)

clean:
	$(call make_subdir , clean)

