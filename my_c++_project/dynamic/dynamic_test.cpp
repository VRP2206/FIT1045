#include <stdlib.h>
#include "splashkit.h"
#include "utilities.h"


int main(){

    double *data_ptr;
    int size;


    size = read_integer("What is the amout of data to be added: ");
    data_ptr = (double *)malloc(size * sizeof(double));

    if (data_ptr == NULL){
        write_line("Memory allocation failed");
        return 1;
    }

    for (int i =0 ; i < size; i++){
        data_ptr[i]= read_double("Enter value No. " + std::to_string(i) + ": ");
    }
    write_line("");
    write_line("======data dump=======");
    for (int i = 0; i<size; i++){
        write_line(data_ptr[i]);
    }
 
    free(data_ptr);
    data_ptr=NULL;
    return 0;
}
