#include <iostream>
using namespace std;

struct node
{
    int data;
    node* prev;
    node* next;
};

class List {
private:
    node* head;
    node* tail;
public:
    List()
    {
        head = NULL;
        tail = NULL;
    }

    // Display the list
    void display()
    {
        if (head == NULL)
        {
            cout << "List is empty" << endl;
            return;
        }

        node* current = head;

        do {
            cout << current->data << "\t";
            current = current->next;
        } while (current != head);
        cout << endl;
    }

    // Insert a new element at the beginning of the list
    void insert_start(int value)
    {
        node* temp = new node;
        temp->data = value;

        // If it's the first element being created
        if (head == NULL)
        {
            head = temp;
            tail = temp;
            head->next = head;
            head->prev = head;
        }
        else {
            temp->next = head;
            temp->prev = tail;
            tail->next = temp;
            head->prev = temp;
            head = temp;
        }
    }

    // Insert a new element at the end of the list
    void insert_end(int value)
    {
        node* temp = new node;
        temp->data = value;

        if (head == NULL)
        {
            head = temp;
            tail = temp;
            head->next = head;
            head->prev = head;
        }
        else {
            temp->next = head;
            temp->prev = tail;
            tail->next = temp;
            head->prev = temp;
            tail = temp;
        }
    }

    // Insert a new element at a specified position in the list
    void insert_position(int pos, int value)
    {
        node* pre = new node;
        node* cur = new node;
        node* temp = new node;

        if (head == NULL)
        {
            if (pos == 1) {
                head = temp;
                tail = temp;
                head->next = head;
                head->prev = head;
            }
            else {
                cout << "The list is empty, cannot insert at position " << pos << endl;
                delete temp;
            }
        }
        else {
            cur = head;
            for (int i = 1; i < pos; i++)
            {
                pre = cur;
                cur = cur->next;
            }

            temp->data = value;
            pre->next = temp;

            temp->prev = pre;
            temp->next = cur;
        }
    }

    // Remove the first element from the list
    void delete_first()
    {
        node* temp = new node;
        temp = head;

        // If there is only one element in the list
        if (head == NULL) {
           cout << "The list is empty, cannot delete" << endl;
        }
        else if (head == tail) {
            head = NULL;
            tail = NULL;
        }
        else {
            head = head->next;
            head->prev = tail;
            tail->next = head;
        }
        delete temp;
    }

    // Remove the last element from the list
    void delete_last()
    {
        if (head == NULL)
        {
            cout << "The list is empty, cannot delete" << endl;
        }
        else {
            node* current = new node;
            node* previous = new node;

            if (tail == head)
            {
                tail = NULL;
                head = NULL;
            }
            else {
                current = tail;
                previous = tail->prev;
                tail = previous;
                previous->next = head;
                head->prev = tail;
            }
            delete current;
        }
    }

    // Remove an element by its value from the list
    void delete_by_value(int value)
    {
        if (head == NULL)
        {
            cout << "The list is empty, cannot delete" << endl;
            return;
        }

        node* current = new node;
        node* previous = new node;
        bool isFound = false;
        current = head;

        do {
            if (value == current->data)
            {
                isFound = true;
                break;
            }
            previous = current;
            current = current->next;

        } while (current != head);

        if (isFound == true) {
            if (current == head && current == tail) {
                delete current;
                head = NULL;
                tail = NULL;
            }
            else if (current == head) {
                head = head->next;
                head->prev = tail;
                tail->next = head;
                delete current;
            }
            else if (current == tail) {
                tail = tail->prev;
                tail->next = head;
                head->prev = tail;
                delete current;
            }
            else {
                previous->next = current->next;
                current->next->prev = previous;
                delete current;
            }
        }
        else {
            cout << "Element with the specified value not found";
        }
    }

    // Find an element by its position in the list
    void find_by_pos(int pos) {
        node* current = head;

        if (head == NULL)
        {
            cout << "The list is empty, cannot find" << endl;
            return;
        }

        for (int i = 1; i < pos; i++)
        {
            current = current->next;
        }
        cout << "Found element: " << current->data << endl;
    }

    // Check if the list is empty
    void check_if_empty() {
        if (head == NULL)
        {
            cout << "The list is empty." << endl;
        }
        else {
            cout << "The list is not empty";
        }
    }

};

void operationList() {
    List intList;
    int operation, pos, elValue;
    do {
    cout << "1. Add an element to the beginning of the list" << endl;
    cout << "2. Add an element at a specified position in the list" << endl;
    cout << "3. Add an element to the end of the list" << endl;
    cout << "4. Remove the first element from the list" << endl;
    cout << "5. Remove an element by its value from the list" << endl;
    cout << "6. Remove the last element from the list" << endl;
    cout << "7. Find an element by position in the list" << endl;
    cout << "8. Check if the list is empty" << endl;
    cout << "9. Display the list" << endl;
    cout << "0. Exit" << endl;
    cout << "-----------------------------";
    cout << endl;
    cout << endl;

    cout << "Choose an operation: ";
    cin >> operation;

    switch (operation) {
    case 1:
        cout << "Enter element value: ";
        cin >> elValue;
        intList.insert_start(elValue);
        intList.display();
        break;
    case 2:
        cout << "Enter position: ";
        cin >> pos;
        cout << "Enter element value: ";
        cin >> elValue;
        intList.insert_position(pos, elValue);
        intList.display();
        break;
    case 3:
        cout << "Enter element value: ";
        cin >> elValue;
        intList.insert_end(elValue);
        intList.display();
        break;
    case 4:
        intList.delete_first();
        intList.display();
        break;
    case 5:
        cout << "Enter element value: ";
        cin >> elValue;
        intList.delete_by_value(elValue);
        intList.display();
        break;
    case 6:
        intList.delete_last();
        intList.display();
        break;
    case 7:
        cout << "Enter element position: ";
        cin >> pos;
        intList.find_by_pos(pos);
        break;
    case 8:
        intList.check_if_empty();
        intList.display();
        break;
    case 9:
        intList.display();
        break;
    case 0:
        cout << "Exiting the program." << endl;
        break;
    default:
        cout << "Operation not available." << endl;
    }
    cout << endl;
    cout << endl;
    cout << "++++++++++++++++++++" << endl;
    cout << endl;
    cout << endl;

    } while (operation != 0);
}

int main()
{
    operationList();
}
