/** 
 * PAGETABLE.H
 * 
 * Gabriel Barrera
 * Tara Vu
 * Professor Roch
 * CS 570
 * Due Date: Thursday 03/12/2019
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <ctype.h>
#include <math.h>

#define MAXBITARG 32

typedef struct pte {
  uint32_t    vfn; /* Virtual frame number */
  uint32_t    pfn; /* Physical frame number iff valid=1 */
  int         reference;
  bool        valid; /* True if in physmem, false otherwise */
  bool        modified;
  int 		    counter;  /* used for LRU, FIFO */
  int		      frequency; /*used for LFU and MFU */
  int 		    c; //keeping track of FIFO order in LFU and MFU
  int		      used; //the used bit for clock algorithm
  int         chance; //The modification bit for second chance algorithm	

} pte_t;

/* Structure for pagetable level */
typedef struct pagetable_level {
  uint32_t size;
  uint32_t log_size;
  bool is_leaf;
} ptlevel_t;

/* Structure representing our multi-level pagetable */
typedef struct pagetable {
  int levelCount;
  int bitMaskAry[MAXBITARG];
  int shiftAry[MAXBITARG];
  int entryCount[MAXBITARG];
} pagetable_t;

/* References number of bits in virtual frame*/
uint32_t vfn_bits;

static pagetable_t * root_table;