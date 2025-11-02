#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* (*dataset(FILE* safData))[7];
int main(){
FILE* safData = fopen("/home/emec/Masaüstü/C/data.csv","r");
if(!safData){
    return 1;
};

dataset(safData);

};

char* (*dataset(FILE* safData))[7]{

struct IotFann
{


    
};
char satir [200];
char*  satirLeft;
int  satirSatir = 0;
int satirSutun = 0;
int a;
char* satirlar[20600][7];
char buffer[20];
int j=0;
while(fgets(satir,sizeof(satir),safData)){
    for (int i=0;satir[i] != '\0';i++){ 
        if (satir[i]==',' || satir[i]=='\n')
        {

        for(j=a;j<i;j++){
            
            buffer[j-a]=satir[j];

        };

        buffer[j-a]='\0';

        satirlar[satirSatir][satirSutun] = malloc(j-a+1);
        
        strcpy(satirlar[satirSatir][satirSutun],buffer);
        
        a = i+1;
        satirSutun++;
        //printf("%d",satirSutun);

        };
    }
    a = 0;
    satirSatir++;
    satirSutun = 0;
    
};
    printf("%s \n",satirlar[20560][5]);
    printf("%s \n",satirlar[20560][6]);

    return satirlar;
};
