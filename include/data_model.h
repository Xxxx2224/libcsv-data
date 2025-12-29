#ifndef DATA_MODEL_H
#define DATA_MODEL_H
#include <stdio.h>
#include <stdlib.h>

typedef struct FannDataset FannDataset;

typedef enum {
  FANN_SUCCESS = 0,
  FANN_ERR_IO,
  FANN_ERR_ALLOC,
  FANN_ERR_ARG,
  FANN_ERR_DATA,
} FannError;

FannError FannDataset_create(FannDataset **fannDataset,
                             const char *const file_path, size_t total_columns,
                             size_t input_columns, size_t output_columns);

FannError FannDataset_parse_csv(FannDataset *FannDataset,
                                unsigned int skip_rows, const char ayrac);

FannError FannDataset_OutData(FannDataset *FannDataset, const char *new_name);

FannError FannDataset_destroy(FannDataset **FannDataset);

void print_raw_string_including_null(const char *str);
#endif
