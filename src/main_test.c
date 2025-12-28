#include "data_model.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
  printf("Starting FannDataset Test...\n");

  FannDataset *dataset = NULL;
  const char *csv_file = "data.csv";
  const char *output_file = "formatted_output.data";

  // Updated to 7 columns based on data.csv content
  size_t total_cols = 7;
  size_t input_cols = 6;
  size_t output_cols = 1;

  printf("Creating dataset from %s...\n", csv_file);
  FannError err = FannDataset_create(&dataset, csv_file, total_cols, input_cols,
                                     output_cols);
  if (err != FANN_SUCCESS) {
    fprintf(stderr, "Error creating dataset: %d\n", err);
    return 1;
  }

  printf("Parsing CSV...\n");
  // No header row in data.csv, so skip 0
  err = FannDataset_parse_csv(dataset, 0, ',');
  if (err != FANN_SUCCESS) {
    fprintf(stderr, "Error parsing CSV: %d\n", err);
    FannDataset_destroy(&dataset);
    return 1;
  }

  printf("Parsed %zu rows.\n", dataset->total_rows);

  printf("Writing output data to %s...\n", output_file);
  err = FannDataset_OutData(dataset, output_file);
  if (err != FANN_SUCCESS) {
    fprintf(stderr, "Error writing output: %d\n", err);
    FannDataset_destroy(&dataset);
    return 1;
  }

  printf("Destroying dataset...\n");
  FannDataset_destroy(&dataset);

  printf("Test completed successfully.\n");
  return 0;
}
