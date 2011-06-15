/**
* This class is used to create and modify linked lists.
* Author - Darin Beaudreau
* Last Update - 05/26/2011  4:04 PM
**/

#ifndef LIST_H
#define LIST_H

#include <iostream>
using std::cout;
using std::cin;
using std::endl;

namespace linklist {
    template< typename T >
    struct node {
        T data; // Data stored in the node.
        node<T> *next; // Pointer to the next node in the list.
    };

    template< typename T >
    class List {
        public:
            /**
            * Constructors and destructor.
            **/
            List(); // Default constructor. Creates a new list. Line:
            ~List(); // Destructor. Calls the destroy() function. Line:

            /**
            * List manipulation functions.
            **/
            void destroy(); // Destroys the list by de-allocating memory of the nodes. Line:
            void add(T newData); // Adds a new node with specified data. Line:
            void remove(int pos);  // Removes the element at a specified position. Line:
            void remove(int start, int end); // Removes the elements between the two positions. Line:
            void push_back(); // Deletes the first element in the list. Line:
            void pop_back(); // Deletes the last element in the list. Line:
            void sort(bool asc); // Sorts the list in ascending or descending order. Line:
            void swap(node<T> *i, node<T> *j); // Swaps the data of two nodes. Line:

            /**
            * Position-based functions.
            **/
            T front(); // Returns the data of the first node in the list. Line:
            T back(); // Returns the data of the last node in the list. Line:
            T get(int pos); // Gets the data at specified position. Line:
            void set(int pos, T newData); // Sets the data at specified position. Line:
            int find(T key); // Finds the position of the node containing the key. Line:

            /**
            * Size-based functions.
            **/
            bool isEmpty(); // Returns true if the list is empty. Line:
            int length(); // Returns the current value of the size variable. Line:

            /**
            * List print functions.
            **/
            void printList(); // Prints the entire list using the "cout" stream. Line:
            void printElem(int pos); // Prints a specified element using the "cout" stream. Line:
            void printElem(int start, int end); // Prints the elements between the specified positions using the "cout" stream. Line:
        private:
            node<T> *first; // Pointer to first node in the list.
            node<T> *last; // Pointer to last node in the list.

            int size; // Size of the list.
    };

    // Begin constructors and destructor.
    /**
    * Default constructor. Creates a new List object.
    **/
    template< typename T >
    List<T>::List() {
        first = NULL;
        last = NULL;
        size = 0;
    }
    /**
    * Destructor. Destroys the list and de-allocates node memory.
    **/
    template< typename T >
    List<T>::~List() {
        destroy();
    }
    // End constructors and destructor.

    // Begin manipulation functions.
    /**
    * Destroys the list and de-allocates node memory.
    **/
    template< typename T >
    void List<T>::destroy() {
        node<T> *temp;

        while(first != NULL) {
            temp = first;
            first = first->next;
            delete temp;
        }
        size = 0;
    }
    /**
    * Adds a new node to the list with specified data.
    * If the first node is NULL, the new node becomes the first node.
    * Otherwise, the last node's link is set to the address of the
    * new node, then the memory address of the last node is
    * changed to the address of the new node. Size increments by 1.
    **/
    template< typename T >
    void List<T>::add(T newData) {
        node<T> *newNode = new node<T>;
        newNode->data = newData;
        newNode->next = NULL;

        if(first == NULL) {
            first = newNode;
            last = newNode;
            size = 1;
        } else {
            last->next = newNode;
            last = newNode;
            size++;
        }
    }
    /**
    * Removes the element at a specified position.
    * Prints error message using "cout" stream if position
    * does not exist.
    **/
    template< typename T >
    void List<T>::remove(int pos) {
        if((pos >= 0)&&(pos < size)) {
            node<T> *current;
            node<T> *temp;
            int i = 0;

            for(current = first;current != NULL;current = current->next) {
                if((i + 1) == pos) {
                    temp = current->next;
                    current->next = current->next->next;
                    delete temp;
                    size--;
                    break;
                }
                i++;
            }
        } else {
            cout << "Invalid position accessed." << endl;
        }
    }
    /**
    * Removes the nodes between the two specified positions.
    * Includes the nodes at the start and end positions.
    * Prints an error message with the "cout" stream if the start
    * position is lower than 0 or greater than the end position,
    * and if the end position is lower than the start position or
    * greater than the size of the list - 1.
    **/
    template< typename T >
    void List<T>::remove(int start, int end) {
        if((start >= 0)&&(end > start)&&(end < size)) {
            node<T> *startNode;
            node<T> *endNode;
            node<T> *current;
            node<T> *temp;
            int i = 0;

            for(current = first;current != NULL;current = current->next) {
                if((i + 1) == start) {
                    startNode = current->next;
                    temp = current;
                } else if(i == end) {
                    endNode = current;
                    temp->next = current->next;
                    temp = current->next;
                    current->next = NULL;
                    break;
                }
                i++;
            }
            for(current = startNode;current != endNode;current = current->next) {
                temp = startNode;
                startNode = current->next;
                delete temp;
                size--;
            }
            delete endNode;
            size--;
        } else {
            cout << "Invalid index range specified." << endl;
        }
    }
    /**
    * Removes the first node in the list.
    * Prints an error message with the "cout" stream if list is empty.
    **/
    template< typename T >
    void List<T>::push_back() {
        if(!isEmpty()) {
            node<T> *temp = first;
            first = first->next;
            delete temp;
            size--;
        } else {
            cout << "List is empty. Cannot push back." << endl;
        }
    }
    /**
    * Removes the last node in the list.
    * Prints an error with the "cout" stream if the list is empty.
    **/
    template< typename T >
    void List<T>::pop_back() {
        if(!isEmpty()) {
            node<T> *current;
            node<T> *temp;
            int i = 0;

            for(current = first;current != NULL;current = current->next) {
                if(current->next == last) {
                    temp = last;
                    current->next = NULL;
                    last = current;
                    delete temp;
                    size--;
                }
                i++;
            }
        } else {
            cout << "List is empty. Cannot pop back." << endl;
        }
    }
    /**
    * Sorts the list according to the boolean parameter.
    * If asc is true, list is sorted in ascending order.
    * If asc is false, list is sorted in descending order.
    **/
    template< typename T >
    void List<T>::sort(bool asc) {
        node<T> *i;
        node<T> *j;

        for(i = first;i->next != NULL;i = i->next) {
            for(j = i->next;j != NULL;j = j->next) {
                if(asc) {
                    if(j->data < i->data) {
                        swap(i,j);
                    }
                } else {
                    if(j->data > i->data) {
                        swap(i,j);
                    }
                }
            }
        }
    }
    /**
    * Swaps the data in two nodes.
    **/
    template< typename T >
    void List<T>::swap(node<T> *i, node<T> *j) {
        T temp = i->data;
        i->data = j->data;
        j->data = temp;
    }
    // End manipulation functions.

    // Begin position-based functions.
    /**
    * Retrieves the data in the first node of the list.
    * Returns NULL if first node is NULL.
    **/
    template< typename T >
    T List<T>::front() {
        if(!isEmpty()) {
            return first->data;
        } else {
            return NULL;
        }
    }
    /**
    * Retrieves the data in the last node of the list.
    * Returns NULL if last node is NULL.
    **/
    template< typename T >
    T List<T>::back() {
        if(!isEmpty()) {
            return last->data;
        } else {
            return NULL;
        }
    }
    /**
    * Retrieves the data at the specified position in the list.
    * Returns NULL if the index specified is out of bounds.
    **/
    template< typename T >
    T List<T>::get(int pos) {
        if((pos < size)&&(pos >= 0)) {
            node<T> *current;
            int i = 0;

            for(current = first;current != NULL;current = current->next) {
                if(i == pos) {
                    return current->data;
                }
                i++;
            }
        } else {
            return NULL;
        }

        return NULL;
    }
    /**
    * Sets the data at the specified position to the new data.
    * Prints an error message with "cout" stream if the position
    * specified is out of bounds.
    **/
    template< typename T >
    void List<T>::set(int pos, T newData) {
        if((pos < size)&&(pos >= 0)) {
            node<T> *current;
            int i = 0;

            for(current = first;current != NULL;current = current->next) {
                if(i == pos) {
                    current->data = newData;
                    break;
                }
                i++;
            }
        } else {
            cout << "Could not append data. Invalid index.";
        }
    }
    /**
    * Finds the position of the node containing the key.
    * Returns NULL if key is not found.
    **/
    template< typename T >
    int List<T>::find(T key) {
        node<T> *current;
        int i = 0;

        for(current = first;current != NULL;current = current->next) {
            if(current->data == key) {
                return i;
            }
            i++;
        }

        return NULL;
    }
    // End position-based functions.

    // Begin size-based functions.
    /**
    * Returns true if the list is empty.
    * Returns false if the list has at least one node.
    **/
    template< typename T >
    bool List<T>::isEmpty() {
        return (first == NULL);
    }
    /**
    * Returns the current value of the size variable.
    **/
    template< typename T >
    int List<T>::length() {
        return size;
    }
    // End size-based functions.

    // Begin print functions.
    /**
    * Prints the entire list using the "cout" stream.
    * Each element is separated by spaces.
    **/
    template< typename T >
    void List<T>::printList() {
        node<T> *current;

        for(current = first;current != NULL;current = current->next) {
            cout << current->data;
            if(!(current == last)) {
                cout << " ";
            }
        }
        cout << endl;
    }
    /**
    * Prints the element at the specified position using the "cout" stream.
    * Prints an error message using the "cout" stream if position is out of bounds.
    **/
    template< typename T >
    void List<T>::printElem(int pos) {
        if((pos < size)&&(pos >= 0)) {
            node<T> *current;
            int i = 0;

            for(current = first;current != NULL;current = current->next) {
                if(i == pos) {
                    cout << current->data << endl;
                    break;
                }
                i++;
            }
        } else {
            cout << "That position is out of bounds." << endl;
        }
    }
    /**
    * Prints the elements between the specified positions in the list using the "cout" stream.
    * Prints an error message using the "cout" stream if invalid indexes are specified.
    **/
    template< typename T >
    void List<T>::printElem(int start, int end) {
        if(((start < size)&&(start >= 0))&&((end > start)&&(end < size))) {
            node<T> *current;
            int i = 0;

            for(current = first;current != NULL;current = current->next) {
                if((i >= start)&&(i <= end)) {
                    cout << current->data;
                    if(i < end) {
                        cout << " ";
                    }
                }
                i++;
            }
            cout << endl;
        } else {
            cout << "Invalid sub-list indexes." << endl;
        }
    }
    // End print functions.
}

#endif // LIST_H
