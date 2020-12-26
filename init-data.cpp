#include <iostream>
#include <sstream>
#include <string>
#include <thread>
#include <chrono>

#include "leveldb/include/leveldb/db.h"

using namespace std;


int main(int argc, char** argv)
{

    // Set up database connection information and open database
    leveldb::DB* db;
    leveldb::Options options;
    options.create_if_missing = true;

    leveldb::Status status = leveldb::DB::Open(options, "./testdb", &db);

    if (false == status.ok())
    {
        cerr << "Unable to open/create test database './testdb'" << endl;
        cerr << status.ToString() << endl;
        return -1;
    }
    
    // Add 256 values to the database
    leveldb::WriteOptions writeOptions;
    for (unsigned int i = 0; i < 3000000; ++i)
    {
        ostringstream keyStream;
        keyStream << "Key" << i;

        ostringstream valueStream;
        valueStream << "12345678911234567892123456789312345678941234567895123456789612345678971234567898123456789912345678910234567891123456789122345678913234567891423456789152345678916234567891723456789182345678919234567892023456789212345678922234567892323456789242345678925234567892623456789" << i;

        db->Put(writeOptions, keyStream.str(), valueStream.str());
    }

    // Close the database
    delete db;
}

