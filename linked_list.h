#ifndef LINKED_LIST_H
#define LINKED_LIST_H
#include<iostream>
#include<direct.h>
#include<QDebug>

using namespace std;

template<class T>
class linked_list{
    struct node{
        T date;
        node* p_next;
        node* p_prev;
        node(const T &d,node* n=NULL,node* m=NULL){
            date=d;
            p_next=n;
            p_prev=m;
        }
    };

    private:
        node* p_head;
        node* p_end;
    public:

        linked_list():p_head(NULL),p_end(NULL){}
        ~linked_list(){
            while(p_head){
                remove_front();
            }
        }

        void push_front(T&d){
            /*
            node* p_aux=p_head;
            p_head=new node(d,p_head,NULL);
            if(p_aux==NULL){
                p_end=p_head; //cuando inicie con push_front
            }
            else{
                p_aux->p_prev=p_head;
            }
            */
        }

        void push_back(const T &d){
            node* p_aux=p_end;
            p_end=new node(d,p_head,p_end);
            if(p_aux==NULL){
                p_head=p_end; //cuando inicie con push_back
                p_end->p_next=p_head;
                p_head->p_prev=p_end;
            }
            else{
                p_aux->p_next=p_end;
                p_head->p_prev=p_end;
            }

        }

        void remove_front(){
            if(!p_head) return;
            node* del=p_head;
            p_head=p_head->p_next;
            delete del;
        }

        void remove_back(){
            if(!p_end) return;
            node* del=p_end;
            p_end=p_end->p_prev;
            delete del;
        }

        class iterator{
            private:
                node* m;
            public:
                iterator(node* _m=NULL){
                    m=_m;
                }
                ~iterator(){}

                T& operator*(){	//contenido
                    return m->date;
                }
                node*& nod(){
                    return m;
                }
                iterator& operator ++(){	//next
                    m=m->p_next;
                    return *this;
                }
                iterator& operator --(){    //prev
                    m=m->p_prev;
                    return *this;
                }
                bool operator !=(const iterator& it){
                    return m!=it.m;
                }
                bool operator ==(const iterator& it){
                    return m==it.m;
                }
            };

        void remove(node* aux){

            if(aux==p_head)
            {
                remove_front();


            }
            else if(aux==p_end)
                remove_back();
            else {
            aux->p_next->p_prev=aux->p_prev;
            aux->p_prev->p_next=aux->p_next;
            aux->p_prev=NULL;
            aux->p_next=NULL;
            delete aux;}

        }

        iterator begin(){
            return iterator(p_head);
        }
        iterator ult(){
            return iterator(p_end);
        }
        iterator end(){
            return iterator(NULL);
        }
};



#endif // LINKED_LIST_H
