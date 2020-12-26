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

    // Iterate over each item in the database and print them
    leveldb::ReadOptions readOptions = leveldb::ReadOptions();
    readOptions.fill_cache = false;
    leveldb::Iterator* it = db->NewIterator(readOptions);
    
    for (it->SeekToFirst(); it->Valid(); it->Next())
    {
        // cout << it->key().ToString() << " : " << it->value().ToString() << endl;
    }

    printf("30 seconds delay - BEGIN\n");
    std::chrono::milliseconds timespan(30000);
    std::this_thread::sleep_for(timespan);
    printf("30 seconds delay - END\n");
    if (false == it->status().ok())
    {
        cerr << "An error was found during the scan" << endl;
        cerr << it->status().ToString() << endl;
    }

    delete it;
    
    // Close the database
    delete db;
}

