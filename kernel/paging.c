#include <page.h>
#include <stddef.h>
#include <printk.h>
#include <string.h>
#define MEM_SZ (1024 * 1024 * 4)
#define PAGE_SZ (1024 * 4)

extern uint32_t end;
uint32_t placement_addr = (uint32_t)&end;
struct page_directory *current_directory = NULL;

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
	current_directory = dir;
	asm volatile("mov %0, %%cr3":: "r"(dir->tables_physical));
	asm volatile("mov %%cr0, %0": "=r"(cr0));
	cr0 |= 0x80000000;
	asm volatile("mov %0, %%cr0":: "r"(cr0));
}


void paging_install()
{
	struct page_directory *kernel_dir = NULL;
	struct page_table *table;
	kernel_dir = kmalloc(sizeof(*kernel_dir), NULL);
	memset(kernel_dir, 0, 1024 * sizeof(*kernel_dir));
	table = kmalloc(sizeof(*table), NULL);
	memset(table, 0, 1024 * sizeof(*table));
	
	uint32_t i = 0;
	for (i = 0; i < 1024; i++) {
		table->pages[i].present = 1;
		table->pages[i].writeable = 1;
		table->pages[i].user = 0;
		table->pages[i].frame = i;
	}

	kernel_dir->tables[0] = table;
	kernel_dir->tables_physical[0] = ((uint32_t) table->pages) | 3;

	struct page *tbl = (struct page *) (kernel_dir->tables_physical[0] & ~0xFFF);
	for (i = 0; i < 1024; i++) {
		printk("%x\n", tbl[i]);
	}

	switch_to_page_dir(kernel_dir);
}
