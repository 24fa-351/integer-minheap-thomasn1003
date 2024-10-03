#include <stdio.h>
#include <stdlib.h>

#include "some_heap.h"

#define KEY_NOT_PRESENT -1

heap_t *heap_create(int capacity) {

    heap_t *heap = malloc(sizeof(heap_t));

    if (!heap) {

        return NULL; 

    }

    heap->data = malloc(capacity * sizeof(heap_node_t));

    if (!heap->data) {

        free(heap);
        return NULL; 

    }

    heap->capacity = capacity;

    heap->size = 0;

    return heap;
}



void heap_free(heap_t *heap) {
    if (heap) {

        free(heap->data);

        free(heap);

    }
}

unsigned int heap_size(heap_t *heap) { 

    return heap->size; 

}

unsigned int heap_parent(unsigned int index) { 

    return (index - 1) / 2; 

}

unsigned int heap_left_child(unsigned int index) { 

    return 2 * index + 1; 

}

unsigned int heap_right_child(unsigned int index) { 

    return 2 * index + 2; 

}

unsigned int heap_level(unsigned int index) {

    unsigned int level = 0;

    while (index > 0) {

        index = heap_parent(index);

        level++;

    }

    return level;
}



void heap_print(heap_t *heap) {

    for (int ix = 0; ix < heap_size(heap); ix++) {

        printf("%3d - %3d : " HEAP_KEY_FORMAT "\n", heap_level(ix), ix,

               heap->data[ix].key);

    }

    printf("\n");

}



void heap_swap(heap_t *heap, int index1, int index2) {

    heap_node_t temp = heap->data[index1];

    heap->data[index1] = heap->data[index2];

    heap->data[index2] = temp;

}



void heap_bubble_up(heap_t *heap, int index) {
    while (index > 0 && heap->data[index].key < heap->data[heap_parent(index)].key) {

        heap_swap(heap, index, heap_parent(index));

        index = heap_parent(index);

    }
}



void heap_bubble_down(heap_t *heap, int index) {

    unsigned int smallest = index;

    unsigned int left = heap_left_child(index);

    unsigned int right = heap_right_child(index);

    if (left < heap_size(heap) && heap->data[left].key < heap->data[smallest].key) {

        smallest = left;

    }

    if (right < heap_size(heap) && heap->data[right].key < heap->data[smallest].key) {

        smallest = right;

    }

    if (smallest != index) {

        heap_swap(heap, index, smallest);

        heap_bubble_down(heap, smallest);

    }
}



void heap_insert(heap_t *heap, heap_key_t key, heap_value_t data) {

    if (heap_size(heap) == heap->capacity) {

        return;

    }

    heap->data[heap_size(heap)].key = key;

    heap->data[heap_size(heap)].value = data;

    heap->size++;

    heap_bubble_up(heap, heap_size(heap) - 1);

}

heap_value_t heap_remove_min(heap_t *heap) {

    if (heap_size(heap) == 0) {

        return (heap_value_t) {.as_int = KEY_NOT_PRESENT};

    }

    heap_value_t min = heap->data[0].value;

    heap->size--;

    heap->data[0] = heap->data[heap_size(heap)];

    heap_bubble_down(heap, 0);

    return min;
}
