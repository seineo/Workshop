/*
 * mm-naive.c - The fastest, least memory-efficient malloc package.
 *
 * In this naive approach, a block is allocated by simply incrementing
 * the brk pointer.  A block is pure payload. There are no headers or
 * footers.  Blocks are never coalesced or reused. Realloc is
 * implemented directly using mm_malloc and mm_free.
 *
 * NOTE TO STUDENTS: Replace this header comment with your own header
 * comment that gives a high level description of your solution.
 */
#include "mm.h"

#include "memlib.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/*********************************************************
 * NOTE TO STUDENTS: Before you do anything else, please
 * provide your team information in the following struct.
 ********************************************************/
team_t team = {
    /* Team name */
    "Ateam",
    /* First member's full name */
    "seineo",
    /* First member's email address */
    "1013248644qq@gmail.com",
    /* Second member's full name (leave blank if none) */
    "",
    /* Second member's email address (leave blank if none) */
    ""};

/**********
 * Macros
 *********/

/* single word (4) or double word (8) alignment */
#define ALIGNMENT 8

/* rounds up to the nearest multiple of ALIGNMENT */
#define ALIGN(size) (((size) + (ALIGNMENT - 1)) & ~0x7)

#define SIZE_T_SIZE (ALIGN(sizeof(size_t)))

#define WSIZE 4             /* Word and header/footer size (bytes) */
#define DSIZE 8             /* Double word size (bytes) */
#define CHUNKSIZE (1 << 12) /* Extend heap by this amount (bytes) */

#define MAX(x, y) ((x) > (y) ? (x) : (y))

/* Pack a size and allocated bit into a word */
#define PACK(size, alloc) ((size) | (alloc))

/* Read and write a word at address p */
#define GET(p) (*(unsigned int *)(p))
#define PUT(p, val) (*(unsigned int *)(p) = (val))

/* Read the size and allocated fields from the address p */
#define GET_SIZE(p) (GET(p) & ~0x7)
#define GET_ALLOC(p) (GET(p) & 0x1)

/* Given block ptr bp, compute address of its header and footer */
#define HDRP(bp) ((char *)(bp)-WSIZE)
#define FTRP(bp) ((char *)(bp) + GET_SIZE(HDRP(bp)) - DSIZE)

/* Given block ptr bp, compute address of next and previous blocks */
#define NEXT_BLKP(bp) ((char *)(bp) + GET_SIZE(((char *)(bp)-WSIZE)))
#define PREV_BLKP(bp) ((char *)(bp)-GET_SIZE(((char *)(bp)-DSIZE)))

/* for debug, comment the line below to disable debug code */
/* #define DEBUG */

#ifdef DEBUG
#define DBG_PRINTF(...) fprintf(stderr, __VA_ARGS__)
#define DBG_ASSERT(...) assert(__VA_ARGS__)
#define CHECKHEAP(verbose) mm_checkheap(verbose)
#else
#define DBG_PRINTF(...)
#define DBG_ASSERT(...)
#define CHECKHEAP(verbose)
#endif /* DEBUG */

/********************
 * Global variables
 *******************/

static char *heap_listp;

/********************
 * Helper functions
 *******************/

/*
 * find_fit - Travese the heap list and find a first fit.
 */
static void *find_fit(size_t size) {
    void *bp;
    for (bp = heap_listp; GET_SIZE(HDRP(bp)) > 0; bp = NEXT_BLKP(bp)) {
        if (!GET_ALLOC(HDRP(bp)) && size <= GET_SIZE(HDRP(bp))) {
            return bp;
        }
    }
    return NULL; /* No fit */
}

/*
 * place - Place the blocks to be allocated.
 */
static void place(void *bp, size_t size) {
    size_t blocksize = GET_SIZE(HDRP(bp));
    size_t freesize = blocksize - size;
    /* The minimum size of block is 2 * DSIZE */
    if (freesize >= 2 * DSIZE) {
        PUT(HDRP(bp), PACK(size, 1));
        PUT(FTRP(bp), PACK(size, 1));
        PUT(HDRP(NEXT_BLKP(bp)), PACK(freesize, 0));
        PUT(FTRP(NEXT_BLKP(bp)), PACK(freesize, 0));
    } else {
        PUT(HDRP(bp), PACK(blocksize, 1));
        PUT(FTRP(bp), PACK(blocksize, 1));
    }
}

/*
 * coalesce - Coalesce adjacent free blocks
 */
static void *coalesce(void *bp) {
    size_t prev_alloc = GET_ALLOC(FTRP(PREV_BLKP(bp)));
    size_t next_alloc = GET_ALLOC(HDRP(NEXT_BLKP(bp)));
    size_t size = GET_SIZE(HDRP(bp));
    /* Enumerate four cases */
    if (prev_alloc && next_alloc) {
        return bp;
    } else if (!prev_alloc && next_alloc) {
        size += GET_SIZE(HDRP(PREV_BLKP(bp)));
        PUT(HDRP(PREV_BLKP(bp)), PACK(size, 0));
        PUT(FTRP(bp), PACK(size, 0));
        return PREV_BLKP(bp);
    } else if (prev_alloc && !next_alloc) {
        size += GET_SIZE(HDRP(NEXT_BLKP(bp)));
        PUT(HDRP(bp), PACK(size, 0));
        PUT(FTRP(bp), PACK(size, 0));
        return bp;
    } else {
        size += GET_SIZE(HDRP(PREV_BLKP(bp))) + GET_SIZE(HDRP(NEXT_BLKP(bp)));
        PUT(HDRP(PREV_BLKP(bp)), PACK(size, 0));
        PUT(FTRP(NEXT_BLKP(bp)), PACK(size, 0));
        return PREV_BLKP(bp);
    }
}

/*
 * extend_heap - Extend heap with free blocks.
 */
static void *extend_heap(size_t words) {
    char *bp;
    size_t size;
    /* maintain double words alignment */
    size = words % 2 ? (words + 1) * WSIZE : words * WSIZE;
    /* Extend heap and initialize those free blocks */
    if ((long)(bp = (char *)mem_sbrk(size)) == -1)
        return NULL;
    PUT(HDRP(bp), PACK(size, 0));
    PUT(FTRP(bp), PACK(size, 0));
    PUT(HDRP(NEXT_BLKP(bp)), PACK(0, 1)); /* New epilogue header */
    /* Coalesce the previous block if it was free */
    return coalesce(bp);
}

/*
 * printblock - Print detailed information about block.
 */
static void printblock(void *bp) {
    size_t hdsize, hdalloc, ftsize, ftalloc;
    hdsize = GET_SIZE(HDRP(bp));
    hdalloc = GET_ALLOC(HDRP(bp));
    ftsize = GET_SIZE(FTRP(bp));
    ftalloc = GET_ALLOC(FTRP(bp));
    printf("%p: header: [%zu:%c] footer: [%zu:%c]\n",
           bp,
           hdsize,
           hdalloc ? 'a' : 'f',
           ftsize,
           ftalloc ? 'a' : 'f');
}

/*
 * checkblock - Check at block level
 */
static void checkblock(void *bp) {
    if (GET(HDRP(bp)) != GET(FTRP(bp)))
        DBG_PRINTF("Header and footer don't match\n");
    if ((size_t)bp % ALIGNMENT)
        DBG_PRINTF("Payload area isn't aligned\n");
    if (GET_SIZE(HDRP(bp)) < 2 * DSIZE || GET_SIZE(HDRP(bp)) % ALIGNMENT)
        DBG_PRINTF("Block size is not valid\n");
    if (!GET_ALLOC(HDRP(bp)) && !GET_ALLOC(HDRP(NEXT_BLKP(bp))))
        DBG_PRINTF("Contiguous free blocks exist\n");
}

/*
 * mm_checkheap - Check heap invariants to guarantee track of heap
 */
static void mm_checkheap(int verbose) {
    char *bp;
    if (verbose)
        printf("Heap (%p):\n", heap_listp);
    /* check prologue */
    if (GET_SIZE(HDRP(heap_listp)) != DSIZE)
        DBG_PRINTF("Prologue size is not correct\n");
    if (!GET_ALLOC(HDRP(heap_listp)))
        DBG_PRINTF("Prologue is not allocated\n");
    /* check normal blocks */
    for (bp = heap_listp + DSIZE; GET_SIZE(HDRP(bp)) > 0; bp = NEXT_BLKP(bp)) {
        if (verbose)
            printblock(bp);
        checkblock(bp);
    }
    /* check epilogue */
    if (verbose)
        printblock(bp);
    if (GET_SIZE(HDRP(bp)) != 0)
        DBG_PRINTF("Epilogue size is not correct\n");
    if (!GET_ALLOC(HDRP(bp)))
        DBG_PRINTF("Epilogue is not allocated\n");
}

/*****************
 * Main routines
 ****************/

/*
 * mm_init - Initialize the malloc package.
 */
int mm_init(void) {
    /* Create initial empty heap */
    if ((heap_listp = (char *)mem_sbrk(4 * WSIZE)) == (void *)-1)
        return -1;
    PUT(heap_listp, 0);                            /* Alignment padding */
    PUT(heap_listp + (1 * WSIZE), PACK(DSIZE, 1)); /* Prologue header */
    PUT(heap_listp + (2 * WSIZE), PACK(DSIZE, 1)); /* Prologue footer */
    PUT(heap_listp + (3 * WSIZE), PACK(0, 1));     /* Epilogue header */
    heap_listp += (2 * WSIZE);
    /* Extend the empty heap with a free block of CHUNKSIZE bytes */
    if (extend_heap(CHUNKSIZE / WSIZE) == NULL)
        return -1;
    CHECKHEAP(0);
    return 0;
}

/*
 * mm_malloc - Allocate a block whose size is a multiple of the alignment.
 */
void *mm_malloc(size_t size) {
    CHECKHEAP(0);
    size_t extend_size;
    char *bp;
    if (size == 0)
        return NULL;
    /* The minimum size of block is 2 * DSIZE (payload: DSIZE,
     * header and footer: DSIZE) and size should round up for alignment */
    size = size <= DSIZE ? 2 * DSIZE
                         : DSIZE * (((size + DSIZE) + DSIZE - 1) / DSIZE);
    /* find the free list for a fit */
    if ((bp = (char *)find_fit(size)) != NULL) {
        place(bp, size);
        return bp;
    }
    /* Fail, then ask for more heap space */
    extend_size = MAX(size, CHUNKSIZE);
    if ((bp = (char *)extend_heap(extend_size / WSIZE)) == NULL)
        return NULL;
    place(bp, size);
    CHECKHEAP(0);
    return bp;
}

/*
 * mm_free - Free an allocated block.
 */
void mm_free(void *ptr) {
    CHECKHEAP(0);
    size_t size = GET_SIZE(HDRP(ptr));
    PUT(HDRP(ptr), PACK(size, 0));
    PUT(FTRP(ptr), PACK(size, 0));
    coalesce(ptr); /* coalesce adjacent free blocks */
    CHECKHEAP(0);
}

/*
 * mm_realloc - Changet the size of memory block
 */
void *mm_realloc(void *ptr, size_t size) {
    CHECKHEAP(0);
    if (ptr == NULL)
        return mm_malloc(size);
    if (size == 0) {
        mm_free(ptr);
        return NULL;
    }
    char *newbp;
    /* round up for alignment */
    size_t blocksize = size <= DSIZE
                           ? 2 * DSIZE
                           : DSIZE * (((size + DSIZE) + DSIZE - 1) / DSIZE);
    size_t oldsize = GET_SIZE(HDRP(ptr));
    if (oldsize >= blocksize) {  /* just modify its size in place */
        int freesize = oldsize - blocksize;
        /* the minimum size of free block is 2 * DSIZE */
        if(freesize >= 2 * DSIZE) {
            PUT(HDRP(ptr), PACK(blocksize, 1));
            PUT(FTRP(ptr), PACK(blocksize, 1));
            PUT(HDRP(NEXT_BLKP(ptr)), PACK(freesize, 0));
            PUT(FTRP(NEXT_BLKP(ptr)), PACK(freesize, 0));
            return ptr;
        } else {
            return ptr;   
        }
    } else { /* malloc and get different address from the old block */
        newbp = (char *)mm_malloc(size);
        if (newbp == NULL)
            return NULL;
        memcpy(newbp, ptr, oldsize - DSIZE); /* copy payload not the block */
        mm_free(ptr);
        CHECKHEAP(0);
        return newbp;
    }
}
