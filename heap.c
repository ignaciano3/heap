#include <stdlib.h>
#include "heap.h"
#define CAPACIDAD_STANDARD 10

typedef struct heap {
    cmp_func_t cmp_func_t;
    size_t capacidad; // Representa el largo del datos
    size_t cantidad; // Cantidad de elementos
    void** datos;
} heap_t;

heap_t *heap_crear(cmp_func_t cmp) {
    heap_t* heap = malloc(sizeof (heap_t));
    if (heap == NULL) return NULL;
    heap->capacidad = CAPACIDAD_STANDARD;
    heap->cantidad = 0;
    heap->cmp_func_t = cmp;
    heap->datos = malloc (sizeof (void*) * CAPACIDAD_STANDARD);
    return heap;
}


void heap_redimensionar_datos(heap_t *heap, size_t nuevaCapacidad){
    heap->datos = realloc(heap->datos, sizeof (void*) * nuevaCapacidad);
    if (heap->datos) heap->capacidad = nuevaCapacidad;
}

// Despues borro esto
#include <stdio.h>
void heap_imprimir(heap_t *heap) {
    printf("I : %zu\n", heap->cantidad);
    printf("N : %zu\n", heap->capacidad);
    printf("Arreglo:\n");
    for (int i = 0; i<heap->cantidad; i++){
        printf("%d ", *(int*)heap->datos[i]);

    }
}

void downHeap(heap_t* heap, size_t padre) {
    size_t h_izq = 2 * padre + 1;
    size_t h_der = 2 * padre + 2;
    if (h_izq >= heap->cantidad) return;

    size_t min = h_izq;
    if (h_der < heap->cantidad)
        if (heap->cmp_func_t(heap->datos[h_izq], heap->datos[h_der]) < 0)
            min = h_der;

    if (heap->cmp_func_t(heap->datos[min], heap->datos[padre]) > 0){
        void* aux = heap->datos[min];
        heap->datos[min] = heap->datos[padre];
        heap->datos[padre] = aux;
        downHeap(heap, min);
    }

}

heap_t *heap_crear_arr(void **arreglo, size_t n, cmp_func_t cmp) {
    heap_t* heap = heap_crear(cmp);
    if (heap->datos == NULL) return NULL;
    for (int i = 0; i < n; i++){
        heap_encolar(heap, arreglo[i]);
    }
    return heap;
}

void heap_destruir(heap_t *heap, void (*destruir_elemento)(void *)) {
    while (!heap_esta_vacio(heap)){
        void* prim = heap_desencolar(heap);
        if (destruir_elemento != NULL) {
            destruir_elemento(prim);
        }
    }
    free(heap->datos);
    free(heap);
}

size_t heap_cantidad(const heap_t *heap) {
    return heap->cantidad;
}

bool heap_esta_vacio(const heap_t *heap) {
    return heap->cantidad == 0;
}


void upHeap(heap_t* heap, size_t hijo){
    if (hijo == 0) return;
    size_t padre = (hijo-1)/2;
    if (heap->cmp_func_t(heap->datos[hijo], heap->datos[padre]) > 0){
        void* aux = heap->datos[hijo];
        heap->datos[hijo] = heap->datos[padre];
        heap->datos[padre] = aux;
        upHeap(heap, padre);
    }

}


bool heap_encolar(heap_t *heap, void *elem) {
    if (heap->cantidad == heap->capacidad){
        heap_redimensionar_datos(heap, heap->capacidad*2);
        if (heap->datos == NULL) return NULL;
    }

    heap->datos[heap->cantidad] = elem;
    upHeap(heap, heap->cantidad);
    heap->cantidad++;
    return true;
}

void *heap_ver_max(const heap_t *heap) {
    return heap->datos[0];
}

void *heap_desencolar(heap_t *heap) {
    if (heap_esta_vacio(heap)) return NULL;

    heap->cantidad--;
    void* dato = heap->datos[0];

    if (heap->cantidad == 1){
        heap->datos[0] = NULL;
        return dato;
    }

    // Paso el ultimo al principio
    heap->datos[0] = heap->datos[heap->cantidad];
    heap->datos[heap->cantidad] = NULL;

    downHeap(heap, 0);

    if (heap->cantidad <= heap->capacidad/4){
        heap_redimensionar_datos(heap, heap->capacidad/2);
        if (heap->datos == NULL) return NULL;
    }

    return dato;
}

void heap_sort(void **elementos, size_t cant, cmp_func_t cmp) {

}