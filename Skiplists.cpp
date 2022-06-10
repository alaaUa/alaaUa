#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>

const float P = 1;
using namespace std;

//Skip Node Declaration

struct node
{
    int value;
    node **forw;
    node(int level, int &value)
    {
        forw = new node * [level + 1];
        memset(forw, 0, sizeof(node*) * (level + 1));
        this->value = value;
    }
    ~node()
    {
        delete [] forw;
    }
};

//Skip List Declaration

struct skiplist
{
    node *head;
    int value;
    int level;
    skiplist()
    {
        int MAX_LEVEL;
        head = new node(MAX_LEVEL, value);
        level = 0;
    }
    ~skiplist()
    {
        delete head;
    }
    void display();
    bool contains(int &);
    void insert_element(int &);
    void delete_element(int &);
};

// Random Value Generator

float frand()
{
    return (float) rand() / RAND_MAX;
}

// Random Level Generator

int random_level()
{
    int MAX_LEVEL;
    static bool first = true;
    if (first)
    {
        srand((unsigned)time(NULL));
        first = false;
    }
    int lvl = (int)(log(frand()) / log(1.-P));
    return lvl < MAX_LEVEL ? lvl : MAX_LEVEL;
}

// Insert Element in Skip List

void skiplist::insert_element(int &value)
{
    int MAX_LEVEL;
    node *x = head;
    node *update[MAX_LEVEL + 1];
    memset(update, 0, sizeof(node*) * (MAX_LEVEL + 1));
    for (int i = level;i >= 0;i--)
    {
        while (x->forw[i] != NULL && x->forw[i]->value < value)
        {
            x = x->forw[i];
        }
        update[i] = x;
    }
    x = x->forw[0];
    if (x == NULL || x->value != value)
    {
        int lvl = random_level();
        if (lvl > level)
        {
            for (int i = level + 1;i <= lvl;i++)
            {
                update[i] = head;
            }
            level = lvl;
        }
        x = new node(lvl, value);
        for (int i = 0;i <= lvl;i++)
        {
            x->forw[i] = update[i]->forw[i];
            update[i]->forw[i] = x;
        }
    }
}

// Delete Element from Skip List

void skiplist::delete_element(int &value)
{
    int MAX_LEVEL;
    node *x = head;
    node *update[MAX_LEVEL + 1];
    memset (update, 0, sizeof(node*) * (MAX_LEVEL + 1));
    for (int i = level;i >= 0;i--)
    {
        while (x->forw[i] != NULL && x->forw[i]->value < value)
        {
            x = x->forw[i];
        }
        update[i] = x;
    }
    x = x->forw[0];
    if (x->value == value)
    {
        for (int i = 0;i <= level;i++)
        {
            if (update[i]->forw[i] != x)
                break;
            update[i]->forw[i] = x->forw[i];
        }
        delete x;
        while (level > 0 && head->forw[level] == NULL)
        {
            level--;
        }
    }
}

// Display Elements of Skip List

void skiplist::display()
{
    const node *x = head->forw[0];
    while (x != NULL)
    {
        cout << x->value;
        x = x->forw[0];
        if (x != NULL)
            cout << " - ";
    }
    cout <<endl;
}

// Search Elements in Skip List

bool skiplist::contains(int &s_value)
{
    node *x = head;
    for (int i = level;i >= 0;i--)
    {
        while (x->forw[i] != NULL && x->forw[i]->value < s_value)
        {
            x = x->forw[i];
        }
    }
    x = x->forw[0];
    return x != NULL && x->value == s_value;
}

// Main

int main()
{
    skiplist s;
    int choice, n;
    while (1)
    {

        cout<<"WELCOME TO SKIP LIST PROGRAM! "<<endl;
        cout<<"   "<< endl;
        cout<<"PLEASE CHOOSE ONE OF OPERATIONS BELOW! "<<endl;
        cout<<"  "<< endl;
        cout<<"------------------------------------- "<<endl;
        cout<<"SKIP LIST OPERATIONS: "<<endl;
        cout<<"--------------------------------------"<<endl;
        cout<<"1.Insert Element"<<endl;
        cout<<"2.Delete Element"<<endl;
        cout<<"3.Search Element"<<endl;
        cout<<"4.Display List "<<endl;
        cout<<"5.Exit "<<endl;
        cout<<"Enter your choice : ";
        cin>>choice;

        switch(choice)
        {
        case 1:
             cout<<"Enter the element to be inserted: ";
             cin>>n;
             s.insert_element(n);
             if(s.contains(n))
                 cout<<"Element Inserted"<<endl;
             break;
        case 2:
             cout<<"Enter the element to be deleted: ";
             cin>>n;
             if(!s.contains(n))
             {
                 cout<<"Element not found"<<endl;
                 break;
             }
             s.delete_element(n);
             if(!s.contains(n))
                 cout<<"Element Deleted"<<endl;
             break;
        case 3:
             cout<<"Enter the element to be searched: ";
             cin>>n;
             if(s.contains(n))
                 cout<<"Element "<<n<<" is in the list"<<endl;
             else
                 cout<<"Element not found"<<endl;
        case 4:
             cout<<"The List is: ";
             s.display();
             break;
        case 5:
             exit(1);
             break;
        default:
             cout<<"Wrong Choice"<<endl;
        }
    }
    return 0;
}





