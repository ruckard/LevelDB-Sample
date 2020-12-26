# Introduction

This repo simulates a blockchain with 3 million 260 bytes sized blocks which are stored in LevelDB.

Apparently just looping them uses about 800 MiB of RAM.
I was expecting lower RAM usage for this task as each saved block is only 260 bytes.

# How to build

```
git clone --recurse-submodules https://github.com/ruckard/LevelDB-memory-footprint.git
git submodule update --init --recursive
cd LevelDB-memory-footprint
make
```
# Initialisation

You need to generate the 3 million 260 bytes sized blocks thanks to init-data:

```
./init-data
```

This will create testdb directory which has about 838MiB.
.

# Read the full blockchain

Now you are going to read the 3 million 260 bytes sized blocks.
```
./read-data
```
.

Once the blocks are read you will see:
```
30 seconds delay - BEGIN
```
Now you have 30 seconds to check read-data program on top.

On my PC the results are that RES = 865436 KiB. That means that it occupies 0.8 GiB of RAM.

Finally you see:
```
30 seconds delay - END
```
# Read the full blockchain - Attempt 2

Now you are going to read the 3 million 260 bytes sized blocks but the cache is not going to be used.
```
./read-data
```

Same thing happens.
