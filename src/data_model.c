#include "data_model.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#define FANN_ROWS_ALLOC 100
#define FANN_IO_BUFFER_SIZE 65536

static FannError rows_resize(FannDataset *fannDataset);

FannError FannDataset_create(FannDataset **fannDataset,
                             const char *const file_path, size_t total_columns,
                             size_t input_columns, size_t output_columns) {
  if (fannDataset == NULL || file_path == NULL || file_path[0] == '\0' ||
      total_columns != input_columns + output_columns || input_columns == 0 ||
      output_columns == 0 || total_columns == 0) {

    return FANN_ERR_ARG;
  }

  FILE *file = fopen(file_path, "r");

  if (!file) {

    perror(NULL);
    return FANN_ERR_IO;
  }

  *fannDataset = NULL;

  *fannDataset = (FannDataset *)malloc(sizeof(FannDataset));

  if (*fannDataset == NULL) {
    perror(NULL);
    return FANN_ERR_ALLOC;
  }
  (*fannDataset)->file = file;
  (*fannDataset)->rows = NULL;
  (*fannDataset)->input_columns = input_columns;
  (*fannDataset)->output_columns = output_columns;
  (*fannDataset)->total_columns = total_columns;
  (*fannDataset)->total_rows = 0;
  (*fannDataset)->rows_alloc = FANN_ROWS_ALLOC;

  (*fannDataset)->rows =
      (Fann_rows *)malloc(FANN_ROWS_ALLOC * sizeof(Fann_rows));
  if ((*fannDataset)->rows == NULL) {
    free((*fannDataset));
    perror(NULL);
    return FANN_ERR_ALLOC;
  }
  for (size_t i = 0; i < FANN_ROWS_ALLOC; i++) {
    (*fannDataset)->rows[i].output =
        (char **)malloc(total_columns * sizeof(char *));
  }

  return FANN_SUCCESS;
}

FannError FannDataset_parse_csv(FannDataset *fannDataset,
                                unsigned int skip_rows, const char ayrac) {
  if (fannDataset == NULL || ayrac == '\0') {
    return FANN_ERR_ARG;
  }
  struct stat st;
  if (fstat(fileno(fannDataset->file), &st) != 0) {
    return FANN_ERR_DATA;
  }
  // fseek(fannDataset->file, 0, SEEK_END);
  // unsigned int file_size = ftell(fannDataset->file);
  // fseek(fannDataset->file, 0, SEEK_SET);
  // fseek ile fstat farki sonra test edilecek simdilik isletim sistemini
  // kullanan fonksiyonu kullaniyorum hiz ve guvenirlik acisindan fread
  // davranisinada bakilacak windowsta /r leri galiba kaldiriyor bakicaz
  // read_count a da bakilacak onu unuttum
  if (st.st_size <= 0) {
    perror(NULL);
    fclose(fannDataset->file);
    return FANN_ERR_IO;
  }

  char *const file_handle = malloc(st.st_size + 100);
  if (!file_handle) {
    perror(NULL);
    fclose(fannDataset->file);
    return FANN_ERR_ALLOC;
  }

  fannDataset->file_handle = file_handle;
  size_t read_count = fread(file_handle, 1, st.st_size, fannDataset->file);
  if (read_count != st.st_size) {
    perror(NULL);
    free(file_handle);
    fclose(fannDataset->file);
    return FANN_ERR_IO;
  }

  file_handle[st.st_size] = '\0';
  char *end_ptr = &file_handle[st.st_size - 1];
  fclose(fannDataset->file);
  fannDataset->file = NULL;

  return FannDataset_parse(fannDataset, file_handle, end_ptr, skip_rows, ayrac);
}

FannError FannDataset_parse(FannDataset *fannDataset,
                            char *const file_handle_org, char *end_ptr,
                            unsigned int skip_rows, const char ayrac) {
  char *active_file_handle = file_handle_org;
  size_t rows = 0;
  __uint32_t colums = 0;

  while (skip_rows > 0) {
    if (*active_file_handle == '\n') {
      skip_rows--;
    }
    active_file_handle++;
    if (active_file_handle == end_ptr) {
      return FANN_ERR_DATA;
    }
  }
  char *left_ptr = active_file_handle;
  while (active_file_handle < end_ptr) {

    if (*active_file_handle == ayrac) {
      *active_file_handle = '\0';
      fannDataset->rows[rows].output[colums] = left_ptr;
      left_ptr = active_file_handle + 1;
      colums++;
      if (colums >= fannDataset->total_columns) {
        return FANN_ERR_DATA;
      }
    }
    if (*active_file_handle == '\n') {
      fannDataset->rows[rows].output[colums] = left_ptr;
      *active_file_handle = '\0';
      left_ptr = active_file_handle + 1;
      if (colums != (fannDataset->total_columns - 1)) {
        for (size_t i = colums + 1; i < fannDataset->total_columns; i++) {
          fannDataset->rows[rows].output[i] = NULL;
        }
      }
      colums = 0;

      rows++;
      if (rows >= fannDataset->rows_alloc) {
        if (rows_resize(fannDataset) != FANN_SUCCESS) {
          return FANN_ERR_ALLOC;
        }
      }
    }
    active_file_handle++;
  }
  fannDataset->total_rows = rows;
  return FANN_SUCCESS;
}

static FannError rows_resize(FannDataset *fannDataset) {

  Fann_rows *temp_rows = (Fann_rows *)realloc(
      fannDataset->rows,
      (fannDataset->rows_alloc + FANN_ROWS_ALLOC) * sizeof(Fann_rows));
  if (!temp_rows) {
    return FANN_ERR_ALLOC;
  }
  fannDataset->rows = temp_rows;

  size_t i = fannDataset->rows_alloc;
  fannDataset->rows_alloc = fannDataset->rows_alloc + FANN_ROWS_ALLOC;
  while (i < fannDataset->rows_alloc) {
    fannDataset->rows[i].output =
        (char **)malloc(fannDataset->total_columns * sizeof(char *));
    i++;
  }

  if (!fannDataset->rows_alloc) {
    return FANN_ERR_ALLOC;
  }
  return FANN_SUCCESS;
}

FannError FannDataset_OutData(FannDataset *fannDataset, const char *new_name) {
  if (fannDataset == NULL || new_name == NULL || new_name[0] == '\0') {
    return FANN_ERR_ARG;
  }
  FILE *file = fopen(new_name, "w");
  if (!file) {
    perror(NULL);
    return FANN_ERR_IO;
  }

  int data_flag = 0;
  char io_buffer[FANN_IO_BUFFER_SIZE];
  if (setvbuf(file, io_buffer, _IOFBF, sizeof(io_buffer)) != 0) {
    perror("Buffer set failed");
  }
  fprintf(file, "%zu %zu %zu\n", fannDataset->total_rows,
          fannDataset->input_columns, fannDataset->output_columns);

  for (size_t i = 0; i < fannDataset->total_rows; i++) {
    data_flag = 0;
    for (size_t a = 0; a < fannDataset->total_columns; a++) {
      if (fannDataset->rows[i].output[a] == NULL) {
        data_flag = 1;
        break;
      }
    }

    if (data_flag) {
      continue;
    }

    for (size_t j = 0; j < fannDataset->input_columns; j++) {
      fputs(fannDataset->rows[i].output[j], file);
      if (j < fannDataset->input_columns - 1) {
        fputc(' ', file);
      }
    }
    fputc('\n', file);

    for (size_t j = fannDataset->input_columns; j < fannDataset->total_columns;
         j++) {
      fputs(fannDataset->rows[i].output[j], file);
      if (j < fannDataset->total_columns - 1) {
        fputc(' ', file);
      }
    }
    fputc('\n', file);
  }

  fclose(file);
  return FANN_SUCCESS;
}

FannError FannDataset_destroy(FannDataset **fannDataset) {
  if (fannDataset == NULL || *fannDataset == NULL) {
    return FANN_ERR_ARG;
  }
  if ((*fannDataset)->rows) {

    for (size_t i = 0; i < (*fannDataset)->rows_alloc; i++) {
      free((*fannDataset)->rows[i].output);
    }

    free((*fannDataset)->rows);
  }
  if ((*fannDataset)->file_handle) {

    free((*fannDataset)->file_handle);
  }
  if ((*fannDataset)->file) {
    fclose((*fannDataset)->file);
  }
  free(*fannDataset);
  *fannDataset = NULL;
  return FANN_SUCCESS;
}
