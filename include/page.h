#ifndef _PAGE_H
#define _PAGE_H
#include <stdint.h>

struct page {
	uint32_t present : 1;
	uint32_t writeable : 1;
	uint32_t user : 1;
	uint32_t rsvd_0 : 2;
	uint32_t accessed : 1;
	uint32_t dirty : 1;
	uint32_t rsvd_1 : 2;
	uint32_t avail : 3;
	uint32_t frame : 12;
} __attribute__((packed));

struct page_table {
	struct page pages[1024];
} __attribute__((packed));

struct page_directory {
	struct page_table *tables[1024];
	uint32_t tables_physical[1024];
	uint32_t physical_addr;
};

void paging_install();
#endif
