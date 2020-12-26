all: init-data read-data read-data2

LIBS += $(CURDIR)/leveldb/build/libleveldb.a

leveldb/build/libleveldb.a:
	@echo "Building LevelDB ..."; cd leveldb; mkdir -p build ; cd build ; cmake -DCMAKE_BUILD_TYPE=Release .. ; cmake --build . ; cd ..; cd ..

init-data: init-data.cpp leveldb/build/libleveldb.a
	g++ -o $@ $<  $(addprefix -I,$(CURDIR)/leveldb/include) $(addprefix -I,$(CURDIR)/leveldb/helpers) $(LIBS) -lpthread

read-data: read-data.cpp leveldb/build/libleveldb.a
	g++ -o $@ $<  $(addprefix -I,$(CURDIR)/leveldb/include) $(addprefix -I,$(CURDIR)/leveldb/helpers) $(LIBS) -lpthread

read-data2: read-data2.cpp leveldb/build/libleveldb.a
	g++ -o $@ $<  $(addprefix -I,$(CURDIR)/leveldb/include) $(addprefix -I,$(CURDIR)/leveldb/helpers) $(LIBS) -lpthread

clean:
	rm -f init-data read-data read-data2
