#include <stdio.h>
#include <stdbool.h>

#define MAX_BLOCKS 10
#define MAX_PROCESSES 10

void next_fit(int blocks[], int b_size, int processes[], int p_size) {
    printf("\nNext Fit Memory Allocation:\n");
    int last_alloc = 0; // Tracks last allocated block
    for (int i = 0; i < p_size; i++) {
        bool allocated = false;
        for (int j = 0; j < b_size; j++) {
            int index = (last_alloc + j) % b_size; // Circular search
            if (blocks[index] >= processes[i]) {
                printf("Process %d allocated to Block %d\n", i + 1, index + 1);
                blocks[index] -= processes[i];
                last_alloc = index; // Update the last allocated block
                allocated = true;
                break;
            }
        }
        if (!allocated)
            printf("Process %d could not be allocated.\n", i + 1);
    }
}

void first_fit(int blocks[], int b_size, int processes[], int p_size) {
    printf("\nFirst Fit Memory Allocation:\n");
    for (int i = 0; i < p_size; i++) {
        bool allocated = false;
        for (int j = 0; j < b_size; j++) {
            if (blocks[j] >= processes[i]) {
                printf("Process %d allocated to Block %d\n", i + 1, j + 1);
                blocks[j] -= processes[i];
                allocated = true;
                break;
            }
        }
        if (!allocated)
            printf("Process %d could not be allocated.\n", i + 1);
    }
}

void best_fit(int blocks[], int b_size, int processes[], int p_size) {
    printf("\nBest Fit Memory Allocation:\n");
    for (int i = 0; i < p_size; i++) {
        int best_idx = -1;
        for (int j = 0; j < b_size; j++) {
            if (blocks[j] >= processes[i] &&
                (best_idx == -1 || blocks[j] < blocks[best_idx])) {
                best_idx = j;
            }
        }
        if (best_idx != -1) {
            printf("Process %d allocated to Block %d\n", i + 1, best_idx + 1);
            blocks[best_idx] -= processes[i];
        } else {
            printf("Process %d could not be allocated.\n", i + 1);
        }
    }
}

int main() {
    int blocks[MAX_BLOCKS], processes[MAX_PROCESSES];
    int b_size, p_size;

    printf("Enter the number of memory blocks: ");
    scanf("%d", &b_size);

    printf("Enter the size of each memory block:\n");
    for (int i = 0; i < b_size; i++) {
        printf("Block %d: ", i + 1);
        scanf("%d", &blocks[i]);
    }

    printf("\nEnter the number of processes: ");
    scanf("%d", &p_size);

    printf("Enter the size of each process:\n");
    for (int i = 0; i < p_size; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d", &processes[i]);
    }

    // Perform the three memory allocation techniques
    int temp_blocks[MAX_BLOCKS];

    // Next Fit
    for (int i = 0; i < b_size; i++) temp_blocks[i] = blocks[i];
    next_fit(temp_blocks, b_size, processes, p_size);

    // First Fit
    for (int i = 0; i < b_size; i++) temp_blocks[i] = blocks[i];
    first_fit(temp_blocks, b_size, processes, p_size);

    // Best Fit
    for (int i = 0; i < b_size; i++) temp_blocks[i] = blocks[i];
    best_fit(temp_blocks, b_size, processes, p_size);

    return 0;
}
