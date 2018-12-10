#include <iostream>

struct List {
        List* next;
        List* head;
        List* tail;
        List* prev;

        int value;

        List(int v) {
                this->value = v;
                this->next = nullptr;
                this->head = this;
                this->tail = this;
                this->prev = nullptr;
        };

        List* push_back(int v) {
                auto new_list = new List(v);
                new_list->head = head;
                new_list->tail = new_list;
                
                tail->next = new_list;
                new_list->prev = tail;
                tail = new_list;
                return new_list;
        };

        List* push_front(int v) {
                auto new_list = new List(v);
                head->prev = new_list;
                new_list->head = new_list;
                new_list->tail = tail;
                new_list->next = head;
                head = new_list;

                return new_list;
        }

        List* pop() {
                auto curr = tail;
                auto pr = tail->prev;
                pr->next = nullptr;
                tail = prev;

                return curr;
        }

        void print() {
                auto curr = head;

                while(curr != nullptr) {
                        std::cout << curr->value << " -> ";
                        curr = curr->next;
                }
        }
};

struct Queue {
        List* list;       

        Queue(int v) {
                list = new List(v);
        };

        void enqueue(int v) {
                list->push_front(v);
        };

        void deque() {
                if(list->head == nullptr) {
                        return;
                }

                list->pop();
        }

        int top() {
                return list->tail->value;
        }
};

int main() {
        auto queue = new Queue(1);

        queue->enqueue(2);
        queue->enqueue(3);
        queue->enqueue(4);

        queue->deque();
        queue->deque();
        queue->deque();

        std::cout << queue->top() << std::endl;
}