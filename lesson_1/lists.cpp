#include <iostream>
#include <stdlib.h>
void init(int **a, int n) {
    *a = (int*) malloc(n * sizeof(int));
}

typedef struct list {
    int key;
    struct list* next;
} list;

list* create_head(list* head, int key) {
    head = (list*) malloc(sizeof(list));
    head->key = key;
    head->next = NULL;
    return head;
}
list* push_back(list* head, int key) {
    list *current = head;
    while (current->next != NULL) {
        current= current->next;
    }
    list *elem = (list*) malloc((sizeof(list)));
    elem->key = key;
    elem->next = NULL;
    current->next = elem; // подвязать к списку, чтобы работало
    return head;
}
void list_show(list* head) {
    // напечатать все элементы списка
    list* current = head;
    while (current != NULL) {
        std::cout << current->key << " ";
        current = current->next;
    }
}
list* remove(list* head, int key) {
    // найдём предыдущий и след элемент
    list * current = head;
//    while(current != NULL) {
//        if (current->key == key) {
//            free(current);
//            current = current->next;
//        }
//        head->next->key == key;

    while (current->next != NULL) {
        if (current->next->key == key) {
            break;
        }
        current = current->next;
    }
    //если голова
    if (head->key == key) {
        list* new_head = head->next;
        free(head);
        return new_head;
    }
    //если не голова и мы ничего не нашли
    if (current->next == NULL) {
        return head;
    }
    //если не голова и мы нашли
    list* find_elem = current->next;
    current->next = current->next->next;
    free(find_elem);
    return head;
}
list* add_by(list* head, int key) {
    // вставляем элемент с захардкоженным 0 за элементом по key
    list* current = head;
    // для начала найдём заданный элемент
    while (current != NULL) {
        if (current->key == key) {
            break;
        }
        current = current->next;
    }
    // мы нашли элемент с ключом, теперь нужно создать элемент за ним
    list *elem = (list*) malloc((sizeof(list)));
    elem->key = 0;
    elem->next = current->next;
    current->next = elem;
    return head;
}
list* remove_all_by_key(list* head, int key) {
    // удаляем ВСЕ элементы, с заданным ключом
    // нам нужно найти элемент до нужного
    list* current = head;
    while (current->next != NULL) {
        // нашли требуемый элемент
        if (current->next->key == key) {
            list* find_elem = current->next;
            current->next = current->next->next;
            free(find_elem);
        } else {
            current = current->next;
        }
    }
    if (head->key == key) {
        list* new_head = head->next;
        free(head);
        return new_head;
    }
    return head;

}
// bubble_sort для списка **extra
// напишем компаратор для элементов листа
// компаратор используем в конце, когда будет понятно, что делать
int list_length(list* head) {
    int length = 0;
    list* current = head;
    while (current != NULL) {
        ++length;
        current = current->next;
    }
    return length;
}
bool comp(const list* a, const list* b) {
    return a->key < b->key;
}
list* bubble_sort(list* head) {
// сортировка пузырьком
// здесь пока стоп, завтра или позже свежим взглядом рассмотрю
// произошла одна итерация
    list* current = head;
    while (current->next != NULL) {
            if (comp(current, current->next))  // здесь будет лежать компаратор
            {
                // Обмен местами
                int temp = current->key;
                current->key = current->next->key;
                current->next->key = temp;
            }
    current = current->next;
    }
    return head;
}
int main() {
    list* head;
    head = create_head(head, 1);
    head = push_back(head, 4);
    head = push_back(head, 2);
    head = push_back(head, 4);
    head = push_back(head, 1);
    head = push_back(head, 2);
    head = push_back(head, 3);
    head = push_back(head, 2);
    head = push_back(head, 3);
    head = push_back(head, 1);
    head = push_back(head, 4);
    head = push_back(head, 2);
    head = push_back(head, 3);
    remove(head, 3);
    head = add_by(head, 4);

    head = remove_all_by_key(head, 5);
    list_show(head);
    std::cout << std::endl;
    head = bubble_sort(head);
    list_show(head);
//    std::cout << list_length(head) << std::endl;
    //std::cout << head->key;

    // напечатать list_shoe
    // удалить первый элемент по значению
    return 0;
}
