#include <stdio.h>
#include <stdlib.h>
#include "../include/data_model.h"
#define FANN_ROWS_ALLOC 100

FannError FannDataset_create(
                                FannDataset** fannDataset,
                                size_t total_count,
                                size_t input_count,
                                size_t output_count
                                )
{
    if(fannDataset ==NULL){
        return FANN_ERR_ARG;
    }

    *fannDataset = NULL;
    
    if (total_count!=input_count+output_count)
    {
        return FANN_ERR_ARG;
    }

    FannDataset* dataset = (FannDataset*)malloc(sizeof(FannDataset));
    
    if(dataset == NULL){
        return FANN_ERR_ALLOC; 
    }

    dataset->rows = NULL;    
    dataset->input_columns = input_count;
    dataset->output_columns = output_count;
    dataset->total_columns = total_count;
    dataset->total_rows = 0;
    dataset->rows_alloc = FANN_ROWS_ALLOC;
    
    Fann_rows* rows = (Fann_rows*)calloc((dataset->rows_alloc), sizeof(Fann_rows));
    if (rows == NULL)
    {
        free(dataset);
        return FANN_ERR_ALLOC;
    }
    
    dataset->rows = rows;
    *fannDataset = dataset;
    
    return FANN_SUCCESS;
}


FannError FannDataset_destroy(FannDataset** fannDataset){
    FannDataset* ds = *fannDataset;
    if (fannDataset == NULL || ds == NULL)
    {
        return FANN_ERR_ARG;
    }
    for (size_t i = 0; i <= ds->total_rows; i++)
    {
        // free(&ds->rows[i]);
    }
    
    free(ds->rows);
    
    

}

