#include "Table.h"

Table::Table()
{
    num_rows = 0;
    for (uint32_t i = 0; i < TABLE_MAX_PAGES; i++)
    {
        pages[i] = NULL;
    }
}

Table::~Table()
{
    for (int i = 0; pages[i]; i++)
    {
        free(pages[i]);
    }
}

void *row_slot(Table &table, uint32_t row_num)
{
    uint32_t page_num = row_num / ROWS_PER_PAGE;
    void *page = table.pages[page_num];
    if (page == NULL)
    {
        // Allocate memory only when we try to access page
        page = table.pages[page_num] = malloc(PAGE_SIZE);
    }
    uint32_t row_offset = row_num % ROWS_PER_PAGE;
    uint32_t byte_offset = row_offset * ROW_SIZE;
    return (char *)page + byte_offset;
}