#include <page.h>
#include <stddef.h>
#include <printk.h>
#include <string.h>
#define MEM_SZ (1024 * 1024 * 4)
#define PAGE_SZ (1024 * 4)

//struct page_directory *kernel_dir;

extern uint32_t end;
uint32_t placement_addr = (uint32_t)&end;
uint32_t *kernel_dir = NULL;

void *kmalloc(size_t sz, uint32_t *ptr)
{
	uint32_t tmp;
	if (placement_addr & 0xFFF) {
		placement_addr &= ~0xFFF;
		placement_addr += 0x1000;
	}
	if (ptr) {
		*ptr = placement_addr;
	}
	tmp = placement_addr;
	placement_addr += sz;
	return (void *) tmp;
}

void switch_to_page_dir(struct page_directory *dir)
{
	uint32_t cr0 = 0;
	printk("dir addr: %x\n", dir->tables_physical);
	asm volatile("mov %0, %%cr3":: "r"(&dir->tables_physical));
	asm volatile("mov %%cr0, %0": "=r"(cr0));
	cr0 |= 0x80000000;
	//printk("%x", (cr0 >> 16));
	//printk("00%x\n", cr0 & 0xFFFF);
	asm volatile("mov %0, %%cr0":: "r"(cr0));
}

void paging_install()
{
	uint32_t *table;
	kernel_dir = (placement_addr & ~0xFFF) + 0x1000;
	memset(kernel_dir, 0, 1024 * sizeof(*kernel_dir));
	table = kernel_dir + 1024;
	memset(table, 0, 1024 * sizeof(*table));
	
	uint32_t i = 0;
	for (i = 0; i < 1024; i++) {
		table[i] = (i * 0x1000) | 3;
	}

	kernel_dir[0] = ((uint32_t) table) | 3;

	uint32_t *tbl = kernel_dir[0] & ~0xFFF;
	for (i = 0; i < 1024; i++) {
		printk("%x\n", tbl[i]);
	}

	uint32_t cr0 = 0;
	printk("dir addr: %x\n", kernel_dir);
	asm volatile("mov %0, %%cr3":: "r"(kernel_dir));
	asm volatile("mov %%cr0, %0": "=r"(cr0));
	cr0 |= 0x80000000;
	asm volatile("mov %0, %%cr0":: "r"(cr0));
}

/*void paging_install()
{
	struct page_table *table;
	struct page *pg;
	uint32_t tmp;
	kernel_dir = kmalloc(sizeof(*kernel_dir), &tmp);
	kernel_dir->physical_addr = (uint32_t)kernel_dir->tables_physical;
	memset(kernel_dir, 0, sizeof(*kernel_dir));
	
	uint32_t i = 0;
	for (i = 0; i < placement_addr; i += 0x1000) {
		uint32_t addr = i / 0x1000;
		uint32_t tbl_idx = addr / 1024;
		if (kernel_dir->tables[tbl_idx]) {
			table = kernel_dir->tables[tbl_idx];
		} else {
			table = kmalloc(sizeof(*table), &tmp);
			memset(table, 0, sizeof(*table));
			kernel_dir->tables[tbl_idx] = table;
			kernel_dir->tables_physical[tbl_idx] = tmp | 3;
		}
		pg = &table->pages[addr % 1024];
		pg->present = 1;
		pg->writeable = 1;
		pg->user = 0;
		pg->frame = addr;
	}

	for (i = 0; kernel_dir->tables[0]->pages[i].present != 0; i++) {
		printk("%x\n", kernel_dir->tables[0]->pages[i]);
	}

	switch_to_page_dir(kernel_dir);
	printk("woo\n");
}*/
