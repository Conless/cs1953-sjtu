class MemoryPoolManager {
  private:
    char *head;
    /*
        head: the position of the first free block
    */
    size_t block_size, block_cnt;
    /*
        block_size: the size of each block (in bytes, at least 8);
        block_cnt: the maximum number of blocks
    */
  public:
    MemoryPoolManager(char *ptr, size_t block_size_, size_t block_cnt_)
        : head(ptr), block_size(block_size_), block_cnt(block_cnt_) {
        // to do: code whatever you want here to initialize
        for (int i = 0; i < block_cnt; i++) {
            for (int j = 0; j < block_size; j++)
                head[i * block_size + j] = '?';
        }
    }

    void *allocate() {
        // to do: return a pointer pointing at a free block (nullptr if no free block left)
        int pos = -1;
        for (int i = 0; i < block_cnt; i++) {
            int res = 0;
            for (int j = 0; j < block_size; j++) {
                if (head[i * block_size + j] != '?') {
                    res = 1;
                    break;
                }
            }
            if (!res) {
                pos = i;
                break;
            }
        }
        if (pos == -1)
            return nullptr;
        for (int j = 0; j < block_size; j++)
            head[pos * block_size + j] = '!';
        return head + pos * block_size;
    }

    void free(void *ptr) {
        // to do: make a block ready for reuse (we will guarantee that ptr is a block acquired by previous allocation)
        char *now = (char*)ptr;
        for (int j = 0; j < block_size; j++)
            now[j] = '?';
    }
};