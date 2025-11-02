#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef char* csvRead[7];
typedef csvRead* (*dataSet_t)(FILE*,csvRead*);
csvRead* dataSet(FILE*,csvRead*);
struct IotFann
{
FILE*  safData;
char* satirlar[20600][7];
dataSet_t parser;   
};

int main(){
FILE* safDatax = fopen("/home/emec/Masaüstü/C/data.csv","r");
if(!safDatax){
    return 1;
};
struct IotFann Veri;
Veri.safData = safDatax;
Veri.parser = dataSet;
Veri.parser(Veri.safData,Veri.satirlar);

return 0;

};

csvRead* dataSet(FILE* safData,csvRead* satirlar){
char satir [200];
int  satirSatir = 0;
int satirSutun = 0;
int satirLeft,satirTop = 0;
// csvRead* satirlar = (csvRead*)malloc(24999 * sizeof(csvRead));
char buffer[201];
while(fgets(satir,sizeof(satir),safData)){
    for (int i=0;satir[i] != '\0';i++){ 
        if (satir[i]==',' || satir[i]=='\n')
        {

        for(satirTop=satirLeft;satirTop<i;satirTop++){
            
            buffer[satirTop-satirLeft]=satir[satirTop];

        };

        buffer[satirTop-satirLeft]='\0';

        satirlar[satirSatir][satirSutun] = malloc(satirTop-satirLeft+1);
        
        strcpy(satirlar[satirSatir][satirSutun],buffer);
        
        satirLeft = i+1;
        satirSutun++;
        //printf("%d",satirSutun);

        };
    }
    satirLeft = 0;
    satirSatir++;
    satirSutun = 0;
    
};
    printf("%s \n",satirlar[20560][5]);
    printf("%s \n",satirlar[20560][6]);
    return satirlar;
};

