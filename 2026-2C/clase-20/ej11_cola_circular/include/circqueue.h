/* ej11_cola_circular · circqueue.h — cola circular sobre un vector en el heap */
#ifndef CIRCQUEUE_H
#define CIRCQUEUE_H

class CircQueue
{
private:
    int  m_count;
    int* m_datoCola;
    int  m_front;
    int  m_rear;
    int  m_tamMax;
public:
    CircQueue (int);
    ~CircQueue ();
    void enqueue (int);
    int  dequeue (void);
    int  getFront (void);
    bool isEmpty (void);
    bool isFull (void);
    int  getSize (void);
};

#endif // CIRCQUEUE_H
