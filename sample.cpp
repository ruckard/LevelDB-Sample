#include <iostream>
#include <sstream>
#include <string>

#include "leveldb/include/leveldb/db.h"

using namespace std;

int main(int argc, char** argv)
{
    int init_parametre = 0;
    int read_parametre = 0;

    if (mapArgs.count("--init") && GetRand(atoi(mapArgs["--init"])) == 0)
    {
        printf("DB Init\n");
        init_parametre = 1;
    }

    if (mapArgs.count("--read") && GetRand(atoi(mapArgs["--read"])) == 0)
    {
        printf("DB Read\n");
        read_parametre = 1;
    }
    if ((read_parametre == 0) && (init_parametre == 0)) {
        printf("Usage:\n./sample --init\n./sample --read");
        exit(1);
    }
    if ((read_parametre == 1) && (init_parametre == 1)) {
        printf("Using --init and --read parametres at the same time is not supported.");
        exit(2);
    }

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
    
    if (init_parametre == 1) {
        // Add 256 values to the database
        leveldb::WriteOptions writeOptions;
        for (unsigned int i = 0; i < 3000000; ++i)
        {
            ostringstream keyStream;
            keyStream << "Key" << i;

            ostringstream valueStream;
            valueStream << "Value: " << i;

            db->Put(writeOptions, keyStream.str(), valueStream.str());
        }
    }

    if (read_parametre == 1) {
        // Iterate over each item in the database and print them
        leveldb::Iterator* it = db->NewIterator(leveldb::ReadOptions());
        
        for (it->SeekToFirst(); it->Valid(); it->Next())
        {
            // cout << it->key().ToString() << " : " << it->value().ToString() << endl;
        }
        
        if (false == it->status().ok())
        {
            cerr << "An error was found during the scan" << endl;
            cerr << it->status().ToString() << endl;
        }

        delete it;
    }
    
    // Close the database
    delete db;
}

