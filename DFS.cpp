#include <iostream>
#include <stack>
using namespace std;

class Edge
{
  int destination;

public:
    Edge() {}
    Edge(int des)
    {
        this->destination = des;
    }
    void setDestination(int des)
    {
        this->destination = des;
    }
    int getDestination()
    {
        return destination;
    }
};

class Node
{
    Edge edge;
    Node *next;

public:
    Node()
    {
        this->next = NULL;
    }
    Node(int data)
    {
        edge.setDestination(data);
        this->next = NULL;
    }
    void setData(int des)
    {
        this->edge.setDestination(des);
    }
    void setNext(Node *next)
    {
        this->next = next;
    }
    Edge getData()
    {
        return edge;
    }
    Node *getNext()
    {
        return next;
    }
};

class Linklist
{
    Node *head;
    Node *tail;

public:
    Linklist()
    {
        setHead(NULL);
        setTail(NULL);
    }
    void setHead(Node *Head)
    {
        this->head = Head;
    }
    void setTail(Node *Tail)
    {
        this->tail = Tail;
    }
    Node *getHead()
    {
        return this->head;
    }
    Node *getTail()
    {
        return tail;
    }
    bool isEmpty()
    {
        return this->head == NULL;
    }

    void addOnTail(int data)
    {
        Node *newNode = new Node(data);
        if (isEmpty())
        {
            setHead(newNode);
            setTail(newNode);
        }
        else
        {
            getTail()->setNext(newNode);
            setTail(newNode);
        }
    }
    void addOnHead(int data)
    {
        Node *newNode = new Node(data);
        if (isEmpty())
        {
            setHead(newNode);
            setTail(newNode);
        }
        else
        {
            newNode->setNext(getHead());
            setHead(newNode);
        }
    }

    void removeFromTail()
    {
        Node *tempNode = getHead();
        if (isEmpty())
        {
            cout << "nothing to remove" << endl;
            return;
        }
        else
        {
            if (getHead()->getNext() == NULL) // if there is only one Node in list
            {
                delete tempNode;
                setHead(NULL);
                setTail(NULL);
                return;
            }

            while (tempNode != NULL)
            {
                if (tempNode->getNext()->getNext() == NULL)
                {
                    delete tempNode->getNext();
                    tempNode->setNext(NULL);
                    setTail(tempNode);
                }
                tempNode = tempNode->getNext();
            }
        }
    }
    void removeNode(int n)
    {
        if (isEmpty())
        {
            cout << "there is no such data";
        }
        else
        {
            Node *tempNode = getHead();
            if (getHead()->getData().getDestination() == n)
            {
                Node *rmNode = getHead();
                setHead(getHead()->getNext());
                delete rmNode;
                rmNode = NULL;
                return;
            }
            while (tempNode != NULL)
            {
                if (tempNode->getNext() != NULL && tempNode->getNext()->getData().getDestination() == n)
                {
                    tempNode->setNext(tempNode->getNext()->getNext());
                    delete tempNode->getNext();
                    return;
                }
                tempNode = tempNode->getNext();
            }
            cout << "there is no " << n << " in the list" << endl;
        }
    }

    void printList()
    {
        Node *tempNode = getHead();
        while (tempNode != NULL)
        {
            cout << tempNode->getData().getDestination() << endl;
            tempNode = tempNode->getNext();
        }
    }
};

class StackNode
{
    int data;
    StackNode *next;
public:
    StackNode(int data)
    {
        this->data = data;
        next = NULL;
    }
    int getData()
    {
        return data;
    }
    void setData(int data)
    {
        this->data = data;
    }
    void setNext(StackNode *next)
    {
        this->next = next;
    }
    StackNode *getNext()
    {
        return next;
    }
};

class Stack
{
    StackNode *head;
    StackNode *tail;
public:
    void setHead(StackNode *Head)
    {
        this->head = Head;
    }
    bool empty()
    {
        return head == NULL;
    }
    void setTail(StackNode *Tail)
    {
        this->tail = Tail;
    }
    StackNode *getHead()
    {
        return this->head;
    }
    StackNode *getTail()
    {
        return tail;
    }

    int getTop()
    {
        return getHead()->getData();
    }

    //addOnHead
    void push(int data)
    {
        StackNode *newNode = new StackNode(data);
        if(empty()){
            setHead(newNode);
            setTail(newNode);
        } else {
            newNode->setNext(getHead());
            setHead(newNode);
        }
    }

    //removeFromHead
    void pop()
    {
        if(empty()){
            cout << "nothing to pop" << endl;
        } else {
            if(getHead()->getNext() == NULL) {
                delete getHead();
                setHead(NULL);
                setTail(NULL);
            } else {
                StackNode *rmNode = getHead();
                setHead(rmNode->getNext());
                delete rmNode;
                rmNode = NULL;
            }
        }
    }
};

// graph class
class Graph
{
    Linklist *listAdj;
    int V; // No. of vertices
public:
    Graph(int V) // graph Constructor
    {
        this->V = V;
        listAdj = new Linklist[V];
    }
    void addEdge(int src, int destination) // add an edge to graph
    {
        listAdj[src].addOnTail(destination); // Add "destination" to src's list.
    }
    void print()
    {
        for (int i = 0; i < V; i++)
        {
            listAdj[i].printList();
        }
    }
    void DFS()
    {
        // Mark all the vertices as not visited
        bool visited[V];
        for (int i = 0; i < V; i++)
        {
            visited[i] = false;
        }
        for (int node = 0; node < V; node++)
        {
            if (!visited[node])
            {
                Stack stack;

                // Push the current source node.
                stack.push(node);

                while (!stack.empty())
                {
                    // Pop a vertex from stack and print it
                    int node = stack.getTop();
                    stack.pop();

                    // check if the vertex visited (in case same vertex already exists)
                    if (!visited[node])
                    {
                        cout << node << " ";
                        visited[node] = true;
                    }

                    // Get adjacent vertices of the popped vertex node
                    // push a vertex if any adj node has not been visited 
                    Node *currentNode = listAdj[node].getHead();
                    while (currentNode != NULL)
                    {
                      int x = currentNode->getData().getDestination();
                      if (!visited[x])
                      {
                          stack.push(x);
                      }
                      currentNode = currentNode->getNext();
                    }
                }
            }
        }
    }
};

int main()
{
    
    // Total 5 vertices in graph
    Graph graph(5); 
    graph.addEdge(1, 0);
    graph.addEdge(0, 2);
    graph.addEdge(2, 1);
    graph.addEdge(0, 3);
    graph.addEdge(1, 4);

    //show vertices using DFS!
    graph.DFS();
}
