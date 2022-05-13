#include "testing.h"

#include <stdio.h>
#include <stdlib.h>

void pruebas_heap_catedra(void);
void pruebas_heap_estudiante(void);
void pruebas_heap_volumen_catedra(size_t, bool);

/* ******************************************************************
 *                        PROGRAMA PRINCIPAL
 * *****************************************************************/

#ifdef CORRECTOR
int main(int argc, char *argv[]) {
    if (argc > 1) {
        // Asumimos que nos están pidiendo pruebas de volumen.
        long largo = strtol(argv[1], NULL, 10);
        pruebas_heap_volumen_catedra((size_t) largo, false);
        return 0;
    }
    printf("~~~ PRUEBAS ESTUDIANTE ~~~\n");
    pruebas_heap_estudiante();
    printf("\n~~~ PRUEBAS CÁTEDRA ~~~\n");
    pruebas_heap_catedra();

    return failure_count() > 0;
}
#endif



#include "heap.h"

// de la libreria de qsort
int cmp (const void * a, const void * b) {
    return ( *(int*)a - *(int*)b );
}

static void pruebas_heap(){
    int arr_[] = {8,9,10,7,6,5};
    int* arr[] ={&arr_[0], &arr_[1], &arr_[2], &arr_[3], &arr_[4], &arr_[5]};
    heap_t* heap =heap_crear_arr((void*)arr, 6, cmp);

    print_test("Cantidad es 6", heap_cantidad(heap) == 6);
    print_test("El primero es 10", heap_ver_max(heap) == &arr_[2]);
    print_test("Desencolar es 10", heap_desencolar(heap) == &arr_[2]);
    print_test("Desencolar es 9", heap_desencolar(heap) == &arr_[1]);
    int a1 = 3, b1 = 4, c1= 5;
    heap_encolar(heap, &a1);
    heap_encolar(heap, &b1);
    heap_encolar(heap, &c1);
    print_test("El primero es 8", heap_ver_max(heap) == &arr_[0]);
    heap_destruir(heap, NULL);
}

static void pruebas_heap_sort(){
    int arr[] = {4,1,7,5,3,2,8,9,10,6,11};
    int* arr_p[11];
    for (int x = 0; x < 11; x++){
        arr_p[x] = &arr[x];
    }

    heap_sort((void*)arr_p, 11, cmp);
    for (int x = 0; x<11; x++){
        printf("%i", *(int*)arr_p[x]);
        print_test("Heapsort: ", *(int*)arr_p[x] == x+1);
    }

}


int main() {
    pruebas_heap();
    //pruebas_heap_sort();
    return failure_count() > 0;
}