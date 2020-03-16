#include "cachelab.h"
#include<stdio.h>
#include<stdbool.h>
#include<getopt.h>
#include<stdlib.h>
#include<unistd.h>
#include<math.h>
#include<string.h>
#include<assert.h>
#include<limits.h>

/*
 * This struct stores info about cache from command-line arguments
 */
typedef struct {
    char *trace_file;
    int set_num;
    int line_num;
    int block_num;
    bool verbose;
}ArgsInfo;
ArgsInfo args_info;

/*
 * This struct stores cache line info
 */
typedef struct {
    bool valid;
    int tag;
    size_t LRU_counter;
}CacheLine;

/*
 * This struct stores cache set which contains the array of cache lines
 */
typedef struct {
    CacheLine *lines;
}CacheSet;

typedef CacheSet* Cache;

int S, E;
size_t hit, miss, eviction;
size_t time_stamps;

/*
 * print_help_info - When meeting -h or option errors, print help info 
 *                   to stdout
 */
void print_help_info() {
    printf("Usage: ./csim-ref [-hv] -s <s> -E <E> -b <b> -t <tracefile>\n");
    printf("Options:\n");
    printf("-h: Optional help flag that prints usage info\n");
    printf("-v: Optional verbose flag that displays trace info\n");
    printf("-s <s>: Number of set index bits(S = 2^s is the number of sets)\n");
    printf("-E <E>: Associativity (number of lines per set)\n");
    printf("-b <b>: Number of block bits (B = 2 ^ b is the block size)\n");
    printf("-t <tracefile>: Name of the valgrind trace to replay\n");
    exit(0);
}

/*
 * check_option_errors - Check whether options are followed by appropriate 
 *                       number of arguments. We only use it to check options that
 *                       requires an argument.
 */
void check_option_errors(char opt, char *optarg) {
    if(*optarg == '-') {
        printf("Option -%c missed required command-line argument\n", opt);
        print_help_info();
        exit(0);
    }
}

/*
 * parse_args - Parse the command-line options using getopt() 
 *              to get info about cache
 */
void parse_args(int argc, char **argv) {
    extern char *optarg; 
    char opt;
    while((opt = getopt(argc, argv, "hvs:E:b:t:")) != -1) {
        switch(opt) {
            case 's':
                check_option_errors(opt, optarg);
                args_info.set_num = atoi(optarg);
                break;
            case 'E':
                check_option_errors(opt, optarg);
                args_info.line_num = atoi(optarg);
                break;
            case 'b':
                check_option_errors(opt, optarg);
                args_info.block_num = atoi(optarg);
                break;
            case 't':
                check_option_errors(opt, optarg);
                args_info.trace_file = optarg;
                break;
            case 'v':
                args_info.verbose = true;
                break;
            case 'h':
                print_help_info();
            default:
                fprintf(stderr, "Type -h for help\n");
                exit(1);
        }
    }
}

/*
 * initialize_cache - Allocate dynamic memory to initialize cache with S and E. 
 */
Cache initialize_cache() {
    if(args_info.set_num <= 0 || args_info.line_num <= 0)
        return NULL;
    S = pow(2, args_info.set_num);
    E = args_info.line_num;
    Cache cache = (Cache)calloc(S, sizeof(CacheSet));
    if(!cache) {
        perror("calloc failed");
        exit(EXIT_FAILURE);
    }
    for(int i = 0;i != S;++i) {
        cache[i].lines = (CacheLine*)calloc(E, sizeof(CacheLine));
        if(!cache[i].lines) {
            perror("calloc failed");
            exit(EXIT_FAILURE);
        }
    }
    return cache;
}

/*
 * free_cache - Free dynamic memory allocated for cache.
 */
void free_cache(Cache cache) {  
    if(!cache)
        return;
    int S = pow(2, args_info.set_num);
    for(int i = 0;i != S;++i) {
        free(cache[i].lines);
    }
    free(cache); 
}

/*
 * is_hit() - Judge whether cache hit or not by checking valid bit and tag.
 *            If cache hit, update corresponding LRU_counter
 */
bool is_hit(Cache cache, size_t set_index, int addr_tag) {
    for(int i = 0;i != args_info.line_num;++i) {
        if(cache[set_index].lines[i].valid == true && 
                cache[set_index].lines[i].tag == addr_tag) {
            cache[set_index].lines[i].LRU_counter = ++time_stamps;
            return true;
        }
    }
    return false;
}

/*
 * find_line_to_replace - When the cache set is full and cache miss, iterate
 *                        over cache lines and find the least-recently used one 
 *                        to replace 
 */
int find_line_to_replace(Cache cache, size_t set_index) {
    int min = INT_MAX;
    int min_line = 0;
    for(int i = 0;i != args_info.line_num;++i) {
        int cur_counter = cache[set_index].lines[i].LRU_counter;
        if(cur_counter == 0) {
            return i;
        } 
        if(cur_counter < min) {
            min = cur_counter;
            min_line = i;
        }
    }
    return min_line;
}

/*
 * load_or_store - load data to "register" or store data to "memory". 
 *                 Hit, miss and eviction need be taken into account.
 */
void load_or_store(Cache cache, size_t set_index, int addr_tag) {
    if(is_hit(cache, set_index, addr_tag)) {
        hit++;
        if(args_info.verbose) {
            printf("hit ");
        }
    } else {
        miss++;
        int line_index = find_line_to_replace(cache, set_index);
        CacheLine *target_line = &cache[set_index].lines[line_index];
        if(target_line->LRU_counter == 0) {
            if(args_info.verbose) {
                printf("miss ");
            }
            target_line->valid = true;
            target_line->tag = addr_tag;
        } else {
            eviction++;
            if(args_info.verbose) {
                printf("miss eviction ");
            }
            target_line->tag = addr_tag;  
        }
        target_line->LRU_counter = ++time_stamps;
    }
}

/*
 * modify - Treated as a load followed by a store to the same address
 */
void modify(Cache cache, size_t set_index, int addr_tag) {
    load_or_store(cache, set_index, addr_tag);
    load_or_store(cache, set_index, addr_tag);
}

#if 0
void test_parse_args(int argc, char **argv) {
    //test -s 10 -E 4 -b 2 -t ./test-trace-file.trace
    parse_args(argc, argv);
    if(argc == 9 && strcmp(argv[1], "-s") == 0 && strcmp(argv[3], "-E") == 0 
            && strcmp(argv[5],"-b") == 0 && strcmp(argv[7], "-t") == 0) {
        assert(args_info.verbose == false);
        assert(args_info.set_num == 10);
        assert(args_info.line_num == 4);
        assert(args_info.block_num == 2);
        assert(strcmp(args_info.trace_file, "./test-trace-file.trace") == 0);
    }
}

void test_is_hit() {
    Cache cache = initialize_cache();
    //test not hit
    assert(is_hit(cache, 0, 2) == false);
    cache[0].lines[0].tag = 2;
    assert(is_hit(cache, 0, 2) == false);
    cache[0].lines[0].valid = true;
    cache[0].lines[0].tag = 1;
    assert(is_hit(cache, 0, 2) == false);
    //test hit
    cache[0].lines[0].tag = 2;
    assert(is_hit(cache, 0, 2) == true);
    free_cache(cache);
}

void test_find_line_to_replace() {
    //test the situation that LCU counters are all 0
    Cache cache = initialize_cache();
    assert(find_line_to_replace(cache, 0) == 0);
    //test the situation that all 2 other than that in first line is 0
    for(int i = 1;i != args_info.line_num;++i) {
        cache[0].lines[i].LRU_counter = 2;
    }
    assert(find_line_to_replace(cache, 0) == 0);
    //test the situation taht all 2 other than that in first line is 3
    cache[0].lines[0].LRU_counter = 3;
    assert(find_line_to_replace(cache, 0) == 1);
    //test the situation that all 2, except 3 in the first line and 1 in the last line
    cache[0].lines[args_info.line_num - 1].LRU_counter = 1;
    assert(find_line_to_replace(cache, 0) == args_info.line_num - 1);
    free_cache(cache);
}

void test_load_or_store() {
    //test miss
    Cache cache = initialize_cache();
    load_or_store(cache, 0, 0);
    assert(hit == 0 && miss == 1 && eviction == 0);
    //test hit
    load_or_store(cache, 0, 0);
    assert(hit == 1 && miss == 1 && eviction == 0);
    //test eviction
    for(int i = 1;i <= args_info.line_num;++i) {
        load_or_store(cache, 0, i);
    }
    assert(hit == 1 && miss == args_info.line_num + 1 && eviction == 1);
    //restore global variables
    hit = miss = eviction = 0;
}

void test_modify() {
    Cache cache = initialize_cache();
    //test miss + hit
    modify(cache, 0, 0);
    assert(hit == 1 && miss == 1 && eviction == 0);
    //test hit + hit
    modify(cache, 0, 0);
    assert(hit == 3 && miss == 1 && eviction == 0);
    //test miss + eviction + hit
    for(int i = 1;i <= args_info.line_num;++i) {
        modify(cache, 0, i);
    }
    assert(hit == args_info.line_num + 3 && miss == args_info.line_num + 1 
            && eviction == 1);
    //restore global variables
    hit = miss = eviction = 0;
}
#endif

int main(int argc, char **argv)
{
#if 0
    test_parse_args(argc,argv);
    test_is_hit();
    test_find_line_to_replace();
    test_load_or_store();
    test_modify();    
#endif 
    parse_args(argc, argv);
    //open trace file
    FILE *fp = fopen(args_info.trace_file, "r");
    if(!fp) {
        perror("File opening failed");
        exit(EXIT_FAILURE);
    }
    //create cache 
    Cache cache = initialize_cache();
    //parse trace file line by line
    char opt;
    int address;
    size_t size;
    size_t mask = (1 << args_info.set_num) - 1;

    /*note that by using a whitespace character before %c, we can
        consume all consecutive leading whitespaces */
    while(fscanf(fp, " %c %x,%zu", &opt, &address, &size) == 3) {
        if(opt == 'I') 
            continue;
        if(args_info.verbose)
            printf("%c %x,%zu ", opt, address, size);
        size_t set_index = ((address >> args_info.block_num) & mask) % S; 
        int addr_tag = address >> (args_info.block_num + args_info.set_num);
        if(opt == 'L' || opt == 'S') {
            load_or_store(cache, set_index, addr_tag);
        } else {
            modify(cache, set_index, addr_tag);
        }
        printf("\n");
    }
    printSummary(hit, miss, eviction);
    //free dynamic memory
    free_cache(cache);
    return 0;
}
