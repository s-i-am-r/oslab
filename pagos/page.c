#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *frame;
    int *fcfl;
    int *lru;
    int n_fr;
} Frames;

// Initialize the Frames structure
Frames *init_frames(int n_fr) {
    Frames *f = (Frames *)malloc(sizeof(Frames));
    f->frame = (int *)malloc(n_fr * sizeof(int));
    f->fcfl = (int *)malloc(n_fr * sizeof(int));
    f->lru = (int *)malloc(n_fr * sizeof(int));
    f->n_fr = n_fr;
    
    for (int i = 0; i < n_fr; i++) {
        f->frame[i] = -1; // Using -1 to represent empty slots
        f->fcfl[i] = -1;
        f->lru[i] = i;
    }
    
    return f;
}

// Free allocated memory for Frames structure
void free_frames(Frames *f) {
    free(f->frame);
    free(f->fcfl);
    free(f->lru);
    free(f);
}

// FCFL (FIFO) page replacement
void page_fcfl(Frames *f, int *pages, int n_pages) {
    int done = 0, i = 0;
    
    while (done < n_pages) {
        int found = 0;
        for (int j = 0; j < f->n_fr; j++) {
            if (f->frame[j] == pages[done]) {
                found = 1;
                break;
            }
        }
        
        if (!found) {
            f->frame[i] = pages[done];
            i = (i + 1) % f->n_fr;
        }
        
        done++;
        
        for (int j = 0; j < f->n_fr; j++)
            printf("%d ", f->frame[j]);
        printf("\n");
    }
}

// LRU page replacement
void page_lru(Frames *f, int *pages, int n_pages) {
    int done = 0;
    
    while (done < n_pages) {
        int found = 0;
        for (int j = 0; j < f->n_fr; j++) {
            if (f->frame[j] == pages[done]) {
                found = 1;
                break;
            }
        }
        
        if (!found) {
            int ind = f->lru[0];
            f->frame[ind] = pages[done];
            
            for (int j = 0; j < f->n_fr - 1; j++)
                f->lru[j] = f->lru[j + 1];
            f->lru[f->n_fr - 1] = ind;
        }
        
        done++;
        
        for (int j = 0; j < f->n_fr; j++)
            printf("%d ", f->frame[j]);
        printf("\n");
    }
}

// Optimal page replacement
void page_opt(Frames *f, int *pages, int n_pages) {
    int done = 0;
    
    while (done < n_pages) {
        int found = 0;
        for (int j = 0; j < f->n_fr; j++) {
            if (f->frame[j] == pages[done]) {
                found = 1;
                break;
            }
        }
        
        if (!found) {
            int max_distance = -1, replace_index = 0;
            
            for (int i = 0; i < f->n_fr; i++) {
                int dist = 0;
                
                for (int j = done + 1; j < n_pages; j++) {
                    if (f->frame[i] == pages[j]) break;
                    dist++;
                }
                
                if (dist > max_distance) {
                    max_distance = dist;
                    replace_index = i;
                }
            }
            
            f->frame[replace_index] = pages[done];
        }
        
        done++;
        
        for (int j = 0; j < f->n_fr; j++)
            printf("%d ", f->frame[j]);
        printf("\n");
    }
}

int main() {
    FILE *file = fopen("input.txt", "r");
    if (!file) {
        fprintf(stderr, "Error opening input.txt\n");
        return 1;
    }
    
    int n_pages, pages[100]; // Assuming max 100 pages
    n_pages = 0;
    
    while (fscanf(file, "%d", &pages[n_pages]) != EOF)
        n_pages++;
    fclose(file);
    
    Frames *f = init_frames(3);
    
    printf("Page Reference Sequence: ");
    for (int i = 0; i < n_pages; i++)
        printf("%d ", pages[i]);
    printf("\n");
    
    printf("\nOptimal Page Replacement:\n");
    page_opt(f, pages, n_pages);
    
    // Reset and run other methods if needed
    free_frames(f);
    
    return 0;
}
