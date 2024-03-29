#include<iostream>
#include<cstdlib>
#include<malloc.h>
#include<conio.h>
using namespace std;

struct node{
	int info;
    struct node *next;
};

class stack{
    struct node *top;
    public:
        stack();
        void push();
        void pop();
        void display();
};

stack::stack(){
    top = NULL;
}

void stack::push(){
    int data;
    struct node *p;
    if((p=(node*)malloc(sizeof(node)))==NULL){
        cout<<"Memory Exhausted";
        exit(0);
	}
    cout<<"Insert a number : ";
    cin>>data;
    p = new node;
    p->info = data;
    p->next = NULL;
    if(top!=NULL){
        p->next = top;
    }
    top = p;
    cout<<"Insert successfully\n"<<endl;
}

void stack::pop(){
    struct node *temp;
    if(top==NULL){
        cout<<"The stack is Empty\n"<<endl;
    }else{
        temp = top;
        top = top->next;
        cout<<"Popped "<<temp->info<<endl;
        cout<<endl;
        delete temp;
    }
}

void stack::display(){
    struct node *p = top;
    if(top==NULL){
        cout<<"Can't display\n"<<endl;
    }else{
        cout<<"Item in stack :";
        while(p!=NULL){
            cout<<p->info<<" ";
            p = p->next;
        }
        cout<<endl;
    }
}

int main(){
    stack s;
    int choice;
    do{
    	cout<<"\t   Stack";
        cout<<"\n\t1. PUSH\n\t2. POP\n\t3. DISPLAY\n\t4. EXIT\n";
        cout<<"\nEnter your choice : ";
        cin>>choice;
        switch(choice){
            case 1:
                s.push();
                break;
            case 2:
                s.pop();
                break;
            case 3:
                s.display();
                break;
            case 4:
                exit(0);
                break;
            default:
                cout<<"Invalid Choice";
                break;
        }
    }while(choice);
    getch();
    return 0;
}