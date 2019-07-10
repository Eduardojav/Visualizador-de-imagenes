#ifndef BST_H
#define BST_H

#include<iostream>
#include<string>

using namespace std;

template<class K>

class bst{
    struct node{
        K* key;
        node* p_child[2]; //0:left child  1:right child
        node(K* &k){
            key=&(*k);
            p_child[0]=p_child[1]=NULL;
        }
        ~node(){}
    };
    private:
        node* p_roct;

        bool find(node** &n,K* &k){
            n=&p_roct;

            while(*n){

                if(*k==*(*n)->key)	return true;
                n=&(*n)->p_child[*k>*(*n)->key];
            }
            return false;
        }

    public:
        bst():p_roct(NULL){}

    bool find(K* &k){
        node** n;
        return find(n,k);
    }

    bool insert(K* &k){
        node** n;

        if(find(n,k)) return false;

        *n=new node(k);

        return true;
    }

    bool remove(K* &k){
        node**n;
        if(!find(n,k)) return false;
        return true;
    }

};


#endif // BST_H
