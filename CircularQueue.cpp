/*
Implement Circular Queue using Array. Perform following operations on it.
a) Insertion (Enqueue)
b) Deletion (Dequeue)
c) Display
(Note: Handle queue full condition by considering a fixed size of a queue.)
*/
#include <iostream>
using namespace std;
class CircularQueue {
private:
    int* queue;
    int front;
    int rear;
    int size;
public:
    CircularQueue(int capacity) {
        size = capacity;
        queue = new int[size];
        front = -1;
        rear = -1;
    }
    ~CircularQueue() {
        delete[] queue;
    }
    bool isFull() {
        return (front == (rear + 1) % size);
    }

    bool isEmpty() {
        return (front == -1);
    }

    void enqueue(int value) {
        if (isFull()) {
            cout << "Queue is full. Cannot insert " << value << endl;
            return;
        }
        if (front == -1) front = 0;
        rear = (rear + 1) % size;
        queue[rear] = value;
        cout << "Inserted " << value << " into the queue." << endl;
    }

    int dequeue() {
        if (isEmpty()) {
            cout << "Queue is empty. Cannot dequeue." << endl;
            return -1;
        }
        int value = queue[front];
        if (front == rear) {
            front = rear = -1;
        } else {
            front = (front + 1) % size;
        }
        cout << "Removed " << value << " from the queue." << endl;
        return value;
    }

    void display() {
        if (isEmpty()) {
            cout << "Queue is empty." << endl;
            return;
        }
        cout << "Queue elements: ";
        int i = front;
        while (i != rear) {
            cout << queue[i] << " ";
            i = (i + 1) % size;
        }
        cout << queue[rear] << endl;
    }
};

int main() {
    CircularQueue q(5);
    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);
    q.enqueue(40);
    q.enqueue(50);
    q.display();
    q.enqueue(60);
    q.dequeue();
    q.dequeue();
    q.display();
    q.enqueue(60);
    q.enqueue(70);
    q.display();
    return 0;
}
