#include "../lib/ordenar_arquivo.h"

void insert (pilha_no a_node, pilha_no *heap, int32_t size)
{
	int32_t idx;
	pilha_no tmp;
	idx = size + 1;
	heap[idx] = a_node;
	while (heap[idx].value < heap[idx/2].value && idx > 1)
	{
		tmp = heap[idx];
		heap[idx] = heap[idx/2];
		heap[idx/2] = tmp;
		idx /= 2;
	}
}

void shift_down (pilha_no *heap, int32_t size, int32_t idx)
{
	int32_t cidx;        //index for child
	pilha_no tmp;
	for (;;)
	{
		cidx = idx*2;
		if (cidx > size)
		{
			break;   //it has no child
		}
		if (cidx < size)
		{
			if (heap[cidx].value > heap[cidx+1].value)
			{
				++cidx;
			}
		}
		//swap if necessary
		if (heap[cidx].value < heap[idx].value)
		{
			tmp = heap[cidx];
			heap[cidx] = heap[idx];
			heap[idx] = tmp;
			idx = cidx;
		}
		else
		{
			break;
		}
	}
}

pilha_no remove_min (pilha_no *heap, int32_t size)
{
	pilha_no rv = heap[1];
	heap[1] = heap[size];
	--size;
	shift_down(heap, size, 1);
	return rv;
}

void enqueue (pilha_no node, Priore *q)
{
	insert(node, q->heap, q->size);
	++q->size;
}

pilha_no dequeue (Priore *q)
{
	pilha_no rv = remove_min(q->heap, q->size);
	--q->size;
	return rv;
}

void init_queue (Priore *q, int32_t n)
{
	q->size = 0;
	q->heap = (pilha_no*) malloc(sizeof(pilha_no) * (n+1));
}

/* this function compares two numbers to verify which one is higher */
int32_t compare_function (const void * a, const void * b)
{
	return (*(int*)a - *(int*)b);
}

/* Generates the initial k-ways */
KFile* generate_KFiles (const int32_t K)
{
	KFile *files = malloc ((2 * K) * sizeof(KFile));
	int32_t i;
	for (i = 0; i < (2 * K); i++)
	{
		char *tmp_char = malloc (sizeof(int));
		sprintf(tmp_char, "%d", i);
		//+1 for the zero-terminator
		char *file_name = malloc(strlen("kfile_") + strlen(tmp_char) + strlen(".bin") + 1);
		strcpy(file_name, "kfile_");
		strcat(file_name, tmp_char);
		strcat(file_name, ".bin");

		files[i].id = i;
		files[i].name = file_name;
		files[i].file = fopen(file_name, "w+b");
		files[i].actual_size = 0;
		files[i].actual_run.size = 0;
	}
	return files;
}

void print_file_structure (KFile *files, int32_t size)
{
	printf("\n***********************************************");
	int32_t i;
	for (i = 0; i < size; i++)
	{
		printf("\nID: %d\n", files[i].id);
		printf("NAME: %s\n", files[i].name);
		printf("ACTUAL SIZE: %lu", files[i].actual_size);
		printf("\nACTUAL RUN SIZE: %zu", files[i].actual_run.size);
	}
	printf("\n***********************************************");
}

unsigned long get_file_length (FILE* file)
{
	unsigned long fileLength;
	fseek(file, 0, SEEK_END);
	fileLength = ftell(file);
	fseek(file, 0, SEEK_SET);

	return fileLength;
}

int32_t get_number_of_runs (unsigned long file_length, const int32_t AVAILABLE_MEMORY)
{
	int32_t number_of_runs = ceil((float) file_length / AVAILABLE_MEMORY);

	return number_of_runs;
}

/* Generate the initial runs */
KFile* generate_runs (FILE *file, const int32_t AVAILABLE_MEMORY, const int32_t K)
{
	KFile* files = generate_KFiles(K);
	int32_t * buffer = NULL;
	int32_t number_of_total_runs = get_number_of_runs(get_file_length(file), AVAILABLE_MEMORY);
	int32_t x;
	for (x = 0; x < number_of_total_runs; x++)
	{
		buffer = (int32_t *) malloc(AVAILABLE_MEMORY);
		size_t bytes_read = fread(buffer, 1, AVAILABLE_MEMORY, file);
		qsort(buffer, bytes_read / ITEM_SIZE, sizeof(int), compare_function);
		int32_t actual_position = x % K;
		files[actual_position].actual_size = files[actual_position].actual_size + bytes_read;

		Run run;
		run.size = bytes_read;
		if (files[actual_position].actual_run.size == 0)
		{
			files[actual_position].actual_run = run;
		}
		fwrite(buffer, bytes_read, 1, files[actual_position].file);
	}
	/* Seek to the beginning of the file */
	for (x = 0; x < K + 1; x++)
	{
		fseek(files[x].file, SEEK_SET, 0);
	}
    free(buffer);

	return files;
}

int32_t int_log (double base, double x)
{
	return ceil((double) (log(x) / log(base)));
}

/* Interpolate the values and return the output file index */
int32_t interpolate(KFile *files, unsigned long input_file_length, const unsigned long AVAILABLE_MEMORY, const int32_t K)
{
	Priore priority_queue;
	int32_t num_of_interpolation_steps = int_log(K, input_file_length / AVAILABLE_MEMORY);
	int32_t count_num_of_interpolations;
	int32_t count_num_of_combination_per_interpolation;

	/* It holds the actual output position index */
	int32_t actual_output_position = -1;
	for (count_num_of_interpolations = 0; count_num_of_interpolations < num_of_interpolation_steps; count_num_of_interpolations++)
	{
		int32_t num_of_combinations_per_interpolation = num_of_interpolation_steps - count_num_of_interpolations;
		int32_t start, end;
		if (count_num_of_interpolations % 2 == 0)
		{
			start = 0;
			end = K;
			actual_output_position = K;
		}
		else
		{
			start = K;
			end = 2 * K;
			actual_output_position = 0;
		}
		for (count_num_of_combination_per_interpolation = 0; count_num_of_combination_per_interpolation < num_of_combinations_per_interpolation; count_num_of_combination_per_interpolation++)
		{
			int32_t count;
			size_t total_bytes_written = 0;
			init_queue(&priority_queue, K);
			/* Populates the heap with the first values of the current run */
			for (count = start; count < end; count++)
			{
				if (files[count].actual_size == 0)
				{
					continue;
				}
				/* skip only in the first time */
				if (count_num_of_combination_per_interpolation == 0 && count_num_of_interpolations > 0)
				{
					fseek(files[count].file, SEEK_SET, 0);
				}
				/* Creating the initial current run for each k-way */
				if (files[count].actual_size != 0 && files[count].actual_run.size == 0)
				{
					Run run;
					if(files[count].actual_size <= AVAILABLE_MEMORY)
					{
						run.size = files[count].actual_size;
					}
					else
					{
						run.size = (count_num_of_interpolations + 1) * AVAILABLE_MEMORY;
					}
					files[count].actual_run = run;
				}
				pilha_no tmp_pilha_no;
				tmp_pilha_no.KFile_index = count;
				fread(&tmp_pilha_no.value, 1, ITEM_SIZE, files[count].file);
				total_bytes_written += files[count].actual_run.size;
				files[count].actual_run.size -= sizeof(int);
				files[count].actual_size -= sizeof(int);
				enqueue(tmp_pilha_no, &priority_queue);
			}
			total_bytes_written = 0;
			/* If the destination file has values and we are in the first combination, clean it! */
			if (count_num_of_combination_per_interpolation == 0 && count_num_of_interpolations > 0)
			{
				ftruncate(fileno(files[actual_output_position].file), 0);
				fseek(files[actual_output_position].file, SEEK_SET, 0);
			}
			while (priority_queue.size > 0)
			{
				pilha_no pilha_no = dequeue(&priority_queue);
				fwrite(&pilha_no.value, sizeof(int), 1, files[actual_output_position].file);
				files[actual_output_position].actual_size += sizeof(int);
				total_bytes_written += sizeof(int);
				if (files[pilha_no.KFile_index].actual_run.size == 0)
				{
					continue;
				}
				fread(&pilha_no.value, 1, ITEM_SIZE, files[pilha_no.KFile_index].file);
				files[pilha_no.KFile_index].actual_run.size -= sizeof(int);
				files[pilha_no.KFile_index].actual_size = files[pilha_no.KFile_index].actual_size - sizeof(int);
				enqueue(pilha_no, &priority_queue);
			}
			/* Generating the runs for the new output file */
			Run run;
			run.size = total_bytes_written;
			if (files[actual_output_position].actual_run.size == 0)
			{
				files[actual_output_position].actual_run = run;
			}
			actual_output_position++;
		}
	}
	return (actual_output_position - 1);
}
