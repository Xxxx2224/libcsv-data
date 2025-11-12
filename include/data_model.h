#ifndef DATA_MODEL_H
#define DATA_MODEL_H
#include <stdlib.h>
#include <stdio.h>
typedef struct 
{
    size_t sutun_count;
    size_t satir_count;
};

typedef struct{
 size_t output_count;
 char** output;
}Fannsatir;

typedef struct 
{

    Fannsatir* rows;

    //kullanıcı manuel konfigrasyon
    size_t total_columns;
    size_t input_columns;
    size_t output_column;
    size_t total_rows;

}FannDataset;

typedef enum{
    FANN_SUCCESS = 0,
    FANN_ERR_IO,
    FANN_ERR_ALLOC,
    FANN_ERR_ARG,
    FANN_ERR_DATA,
}FannError;


FannError FannDataset_create(
                                FannDataset** fannDataset,
                                size_t total_columns,
                                size_t input_columns,
                                size_t output_columns
                                );




FannError FannDataset_parse_csv(
                                FannDataset* FannDataset,
                                const char* dosya_yolu,
                                int skip_satir,
                                char ayrac
                                );




FannError FannDataset_OutData(
                              FannDataset* FannDataset,
                              const char* new_name
                              );



void FannDataset_destroy(
                        FannDataset** FannDataset
                        );


#endif