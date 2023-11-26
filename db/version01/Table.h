#include "Page.h"

#define TABLE_MAX_PAGES 100

const uint32_t PAGE_SIZE = 4096;
const uint32_t ROWS_PER_PAGE = PAGE_SIZE / ROW_SIZE;
const uint32_t TABLE_MAX_ROWS = ROWS_PER_PAGE * TABLE_MAX_PAGES;

class Table
{
public:
    uint32_t num_rows;
    void *pages[TABLE_MAX_PAGES];
    Table();
    ~Table();
};

// 表页该从何处开始读写
void *row_slot(Table &table, uint32_t row_num);