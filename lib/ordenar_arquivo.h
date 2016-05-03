#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#define ITEM_SIZE 4
#define TRUE 1
#define FALSE 0

#define GB 1000 * 1000 * 1000
#define MB 1000 * 1000

typedef struct pilha_no {
    int32_t value;
    int32_t KFile_index;
} pilha_no;

typedef struct Priore {
    pilha_no *heap;
    int32_t size;
} Priore;

void init_queue(Priore *q, int32_t n);
void enqueue(pilha_no node, Priore *q);
pilha_no dequeue(Priore *q);



typedef struct Run {
    size_t size; //in bytes
} Run;

/* This struct represents the file structure */
typedef struct KFile {
    int32_t id;
    char *name;
    FILE *file;
    Run actual_run;
    unsigned long actual_size;
} KFile;

void insert (pilha_no a_node, pilha_no *heap, int32_t size);

void shift_down (pilha_no *heap, int32_t size, int32_t idx);


pilha_no remove_min (pilha_no *heap, int32_t size);


void enqueue (pilha_no node, Priore *q);


pilha_no dequeue (Priore *q);


void init_queue (Priore *q, int32_t n);


int32_t compare_function (const void * a, const void * b);


KFile* generate_KFiles (const int32_t K);
void print_file_structure (KFile *files, int32_t size);


unsigned long get_file_length (FILE* file);


int32_t get_number_of_runs (unsigned long file_length, const int32_t AVAILABLE_MEMORY);


KFile* generate_runs (FILE *file,
                    const int32_t AVAILABLE_MEMORY,
                    const int32_t K);
int32_t int_log (double base, double x);


int32_t interpolate(KFile *files,
                unsigned long input_file_length,
                const unsigned long AVAILABLE_MEMORY,
                const int32_t K);


