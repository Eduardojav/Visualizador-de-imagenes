#ifndef LINKED_LIST_H
#define LINKED_LIST_H
#include<iostream>
#include"image.h"
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
        node* p_del_aux;

    public:
        node* n;
        linked_list():p_head(NULL),p_end(NULL),n(NULL),p_del_aux(NULL){}
        ~linked_list(){
            while(p_head){
                remove_front();
            }
            delete p_del_aux;
        }

        void push_front(T&d){
            node* p_aux=p_head;
            p_head=new node(d,p_head,NULL);
            if(p_aux==NULL){
                p_end=p_head; //cuando inicie con push_front
                n=p_head;
            }
            else if(p_aux->p_prev==NULL){
                p_aux->p_prev=p_head;
            }
            n=p_head;
        }

        void push_back(const T &d){
            node* p_aux=p_end;
            T _d=d;
            p_end=new node(_d,NULL,p_end);
            if(p_aux==NULL){
                p_head=p_end; //cuando inicie con push_back
                n=p_end;
            }
            else if(p_aux->p_next==NULL){
                p_aux->p_next=p_end;
            }
            n=p_head;
        }

        void remove_front(){
            if(!p_head) return;
            node* del=p_head;
            p_head=p_head->p_next;
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
                iterator& operator ++(){	//siguiente
                    m=m->p_next;
                    return *this;
                }
                bool operator !=(const iterator& it){
                    return m!=it.m;
                }
            };

        void remove(){
            Image a;
            node* p_aux;
            node* del=n;
            node* m=p_head;
            if(n==p_head)
                p_head=n->p_next;
            if(n==p_end)
                p_end=n->p_prev;
            p_aux=n->p_prev;
            p_aux->p_next=n->p_next;
            p_aux=n->p_next;
            p_aux->p_prev=n->p_prev;
            del->p_next=NULL;
            del->p_prev=NULL;



            delete del;
        }
        iterator now(){
            return iterator(n);
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
        iterator position(string a){
            if(a=="next"){
                n=n->p_next;
                if(n==NULL){
                    n=p_head;
                }
            }
            else if(a=="prev"){
                n=n->p_prev;
                if(n==NULL){
                    n=p_end;
                }
            }
            return iterator(n);
        }
};



#endif // LINKED_LIST_H
