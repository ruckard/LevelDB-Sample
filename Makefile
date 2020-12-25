all: sample

LIBS += $(CURDIR)/leveldb/build/libleveldb.a

leveldb/build/libleveldb.a:
	@echo "Building LevelDB ..."; cd leveldb; mkdir -p build ; cd build ; cmake -DCMAKE_BUILD_TYPE=Release .. ; cmake --build . ; cd ..; cd ..

sample: sample.cpp leveldb/build/libleveldb.a
	g++ -o $@ $<  $(addprefix -I,$(CURDIR)/leveldb/include) $(addprefix -I,$(CURDIR)/leveldb/helpers) $(LIBS) -lpthread

clean:
	rm -f sample
