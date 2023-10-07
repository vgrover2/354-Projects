#include "mem.h"  
                    
extern BLOCK_HEADER* first_header;

int Is_Free(BLOCK_HEADER* current_header){
    if(current_header -> size_alloc % 16 == 0)
        return 1;
    return 0; 
}

//returns pointer to payload
//returns NULL if large enough free block is not available
void* Mem_Alloc(int size){
    //finds a free block which is large enough 
    BLOCK_HEADER* current_header = first_header;
    // return NULL if we didn't find a block
    while(1){
        if(current_header -> payload >= size && Is_Free(current_header)){
            break;
        }
        else{
            if(current_header -> size_alloc == 1){
                return NULL;
            }
            if(Is_Free(current_header)){
                current_header = (BLOCK_HEADER *)((unsigned long)current_header + (current_header -> payload) + 8);
            }
            else{
                current_header = (BLOCK_HEADER *)((unsigned long)current_header + (current_header -> size_alloc) -1);
            }
        }
        
    }
    
    // allocate the block
    int block_allocation = current_header -> payload; 

    // split if necessary (if padding size is greater than or equal to 16 split the block)
    int split = 1; 
    int padding;  
    
    if (block_allocation - size >= 16){
        if((size + 8) % 16 ==0){
            padding = 0;
        }
        else{
            padding = 16 - (size + 8) % 16;
        }
    }
    else {
        split = 0; 
        padding = block_allocation - size;
    }
    current_header -> size_alloc = 8 + size + padding + 1;

    void *USER_POINTER = (void *)((unsigned long)current_header + 8);
    //new header created 
    if(split) {
        BLOCK_HEADER *new_header = (BLOCK_HEADER *)((unsigned long)current_header + 8 + size + padding);
        new_header -> size_alloc = block_allocation - (size + padding);
        new_header -> payload = block_allocation - (8 + size + padding);
    }
    return USER_POINTER;

}


// return 0 on success
// return -1 if the input ptr was invalid
int Mem_Free(void *ptr){
    int count_header = 0;
    BLOCK_HEADER *current_header = first_header;
    
    while(1) {
        if(((void *)((unsigned long)current_header + 8) == ptr) && !Is_Free(current_header)){
            break;
        }
        
        else{
            if(current_header -> size_alloc == 1){
                return -1;
            }
            if(Is_Free(current_header)){
                current_header = (BLOCK_HEADER *)((unsigned long)current_header + (current_header -> payload) + 8);
            }
            else{
                current_header = (BLOCK_HEADER *)((unsigned long)current_header + (current_header -> size_alloc) - 1);
            }
        }
        
        count_header++;

    }
    // free the block 
    // coalesce adjacent free blocks
    int block_allocation = current_header -> size_alloc -1;

    current_header -> size_alloc = block_allocation;
    current_header -> payload = current_header -> size_alloc - 8;

    BLOCK_HEADER *next_block = (BLOCK_HEADER *)((unsigned long)current_header + (current_header -> payload) + 8);

    if(Is_Free(next_block)){
        current_header -> size_alloc = current_header -> size_alloc + next_block -> size_alloc;
        current_header -> payload = current_header -> size_alloc - 8;
    }

    BLOCK_HEADER *prev_block = first_header; 

    int i;
    for(i = 0; i < count_header - 1; i++){
        if(Is_Free(prev_block)){
            prev_block = (BLOCK_HEADER *)((unsigned long)prev_block + (prev_block -> payload) + 8);
        }
        else{
            prev_block = (BLOCK_HEADER *)((unsigned long)prev_block + (prev_block -> size_alloc) - 1);
        }
    }
    if(Is_Free(prev_block) && count_header > 0){
        prev_block -> size_alloc = prev_block -> size_alloc + current_header -> size_alloc;
        prev_block -> payload = prev_block -> size_alloc - 8;
    }



    return 0;
}

