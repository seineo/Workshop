# Your System Cache Info

```shell
#type in your terminal
getconf -a | grep CACHE

#output in my computer
LEVEL1_ICACHE_SIZE                 32768
LEVEL1_ICACHE_ASSOC                8
LEVEL1_ICACHE_LINESIZE             64
LEVEL1_DCACHE_SIZE                 32768
LEVEL1_DCACHE_ASSOC                8
LEVEL1_DCACHE_LINESIZE             64
LEVEL2_CACHE_SIZE                  262144
LEVEL2_CACHE_ASSOC                 4
LEVEL2_CACHE_LINESIZE              64
LEVEL3_CACHE_SIZE                  6291456
LEVEL3_CACHE_ASSOC                 12
LEVEL3_CACHE_LINESIZE              64
LEVEL4_CACHE_SIZE                  0
LEVEL4_CACHE_ASSOC                 0
LEVEL4_CACHE_LINESIZE              0
```

As we can see, for L1 cache, C = 32768 KB(32 MB), E = 8, B = 64. Then according to formula `C = S * E * B`, we can get S = 64.(We only talk about data cache here)

So, for 64-bit address, b = 6, s = 6, t = 52.

For example, address 0x00604420.
We can use python built-in function `bin()` to convert it to binary representation.
```python
bin(0x00604420)
#output
0b0000000011000000100010000100000
```

- tag bits: 0000000011000000100
- set index bits: 010000
- block offset bits: 100000

# Load and Store 

The operands for all arithmetic and logic operations are contained in registers. To operate on data in main memory, the data is first copied into registers. A load operation copies data from main memory into a register. A store operation copies data from a register into main memory .

When a word (4 bytes) is loaded or stored the memory address must be a multiple of four. This is called an alignment restriction. Addresses that are a multiple of four are called word aligned. This restriction makes the hardware simpler and faster. 
