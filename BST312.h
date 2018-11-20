
/*  BST312.h
  CS 312 Fall 2018

  a simple implementation of a binary search tree


*/

#ifndef BST_312_H
#define BST_312_H

#include <cstdlib>  // Provides size_t
#include <iostream>
#include <vector>

using namespace std;

template<class ItemType>
class BST_312 {
public:

    BST_312();

    //Copy constructor
    BST_312(const BST_312 & src);

    ~BST_312();

/****************************
makeEmpty

Function: Removes all the items from the BST.
Preconditions: BST has been initialized
Postconditions: All the items have been removed
*****************************/
    void makeEmpty();

/****************************
isEmpty

Function: Checks to see if there are any items in the BST.
Preconditions: BST has been initialized
Postconditions: Returns true if there are no items in the BST, else false.
*****************************/
    bool isEmpty() const;

/****************************
isFull

Function: Determines if you have any more room to add items to the BST
Preconditions: BST has been initialized
Postconditions: Returns true if there is no more room to add items, else false
*****************************/
    bool isFull() const;

/****************************
insertItem

Function: Adds newItem to the BST.
Preconditions: BST has been initialized and is not full.
Postconditions: newItem is in the proper position for a BST.
*****************************/
    void insertItem(const ItemType &);

/****************************
deleteItem

Function: Removes target from BST.
Preconditions: BST has been initialized.
Postconditions: If found, element has been removed from BST.
*****************************/
    void deleteItem(const ItemType& newItem);

/****************************
countNodes

Function: Counts the number of nodes in the BST
Preconditions: BST has been initialized.
Postconditions: returns the number of nodes in the BST
*****************************/
    int countNodes();

/****************************
preOrderTraversal

Function: Returns the preOder (Node, Left, Right) as a vector of ItemTypes
Preconditions: BST has been initialized.
Postconditions: none
*****************************/
    vector<ItemType> preOrderTraversal();

/****************************
inOrderTraversal

Function: Returns the inOder (Left, Node, Right) as a vector of ItemTypes
Preconditions: BST has been initialized.
Postconditions: none
*****************************/
    vector<ItemType> inOrderTraversal();

/****************************
postOrderTraversal

Function: returns the postOder (Left, Right, Node) as a vector of ItemTypes
Preconditions: BST has been initialized.
Postconditions: none
*****************************/
    vector<ItemType> postOrderTraversal();

/********************
 isItemInTree

Function: Determines if a given Item is in tree.
Preconditions: BST has been initialized.
Postconditions: none
*****************************/

    bool isItemInTree(const ItemType& item);



private:
    struct TreeNode {
        ItemType data;
        TreeNode *left;
        TreeNode *right;
    };

    TreeNode * root;


    void insertItem(TreeNode*& t, const ItemType& newItem);
    void inOrderTraversal(TreeNode* t,vector<ItemType>& result) const;
    int countNodes(TreeNode* t) const;
    void deleteNode(TreeNode*& node);
    void makeEmpty(TreeNode*& t);
    void deleteItem(TreeNode*& t, const ItemType& newItem);
    void getPredecessor(TreeNode* t, ItemType& data);
    void preOrderTraversal(TreeNode* t,vector<ItemType>& result) const;
    void postOrderTraversal(TreeNode* t,vector<ItemType>& result) const;
    void copyTree(TreeNode*& copy, const TreeNode *originalTree);


};

/*******************************
//Function implementations
********************************/

template<class ItemType>
BST_312<ItemType>::BST_312 ()//bst constructor
{
    root = NULL;
}

template<class ItemType>
BST_312<ItemType>::BST_312(const BST_312 & src)//bst constroctir when given a start
{
    copyTree(root, src.root);
}

template<class ItemType>
BST_312<ItemType>::~BST_312()// destructor that deallocates all memory
{
    makeEmpty();

}


template<class ItemType>
void BST_312<ItemType>::copyTree(TreeNode*& copy, const TreeNode* originalTree)//a functioon recieving a  src tree and making another treee
{
    if (originalTree == NULL)
        copy = NULL;
    else
    {
        copy = new TreeNode;
        copy->data = originalTree->data;

        copyTree(copy->left, originalTree->left);
        copyTree(copy->right, originalTree->right);
    }
}


template<class ItemType>
void BST_312 <ItemType>::deleteNode(TreeNode*& t)//function that deletes bst nodes
{
    ItemType info;
    TreeNode *tempPtr;

    tempPtr = t;

    if (t->left == NULL)
    {
        t = t->right;
        delete tempPtr;
    }
    else if (t->right == NULL)
    {
        t = t->left;
        delete tempPtr;
    }
    else
    {
        getPredecessor(t->left, info);
        t->data = info;
        deleteItem(t->left, info);
    }
}



//find largest in left subtree
template<class ItemType>
void BST_312 <ItemType>::getPredecessor(TreeNode* t, ItemType& data)
{

    while (t->right != NULL)
        t = t->right;

    data = t->data;

}


template<class ItemType>
void BST_312 <ItemType>::deleteItem(TreeNode*& t, const ItemType& newItem)//item deleter if the item exists
{
    if (t == NULL)
        return;
    else if (newItem < t->data)
        deleteItem(t->left, newItem);
    else if (newItem > t->data)
        deleteItem(t->right, newItem);
    else
        deleteNode(t);
}


template<class ItemType>
void BST_312 <ItemType>::deleteItem(const ItemType& newItem)// caller from object basically that calls the deleter
{
    deleteItem(root, newItem);

}

template<class ItemType>
void BST_312 <ItemType>::makeEmpty(TreeNode*& t)// deletes entire tree
{
    if(t!=NULL){
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete(t);
    }
}

template<class ItemType>
void BST_312 <ItemType>::makeEmpty()//caller from object  of makeEmpty
{
    makeEmpty(root);
    root = NULL;
}

template<class ItemType>
bool BST_312 <ItemType>::isEmpty() const// says if the tree isnt emptyt or is
{
    return root == NULL;
}



template<class ItemType>
bool BST_312 <ItemType>::isFull() const//says if it is full or not
{
    try
    {
        TreeNode *temp = new TreeNode;
        delete temp;
        return false;
    }
    catch (std::bad_alloc)
    {
        return true;
    }

}


template<class ItemType>
void BST_312 <ItemType>::insertItem(TreeNode*& t, const ItemType& newItem)// inserts an item into the tree
{
    TreeNode *temp = new TreeNode;
    temp->data=newItem;
    temp->left=NULL;
    temp->right=NULL;
    if(root==NULL){
        delete(temp);
        root=new TreeNode;
        root->right=NULL;
        root->left=NULL;
        root->data=newItem;
        return;
    }
  //  TreeNode * prev=t;
    while(t!=NULL) {
        if(newItem==t->data){
            return;
        }
        if (newItem > t->data) {
            if(t->right==NULL){
                t->right=temp;
                return;
            }
            else{
                t=t->right;
            }
        }
        if (newItem < t->data) {
            if(t->left==NULL){
            t->left=temp;
                return;
              }
            else {
             t = t->left;
        }
        }
    }

}

template<class ItemType>
void BST_312 <ItemType>::insertItem(const ItemType& newItem)//caller from object
{
    TreeNode * ptr;
    ptr=root;// ptr to tree so dont have to change root
    if(!isFull()){
    insertItem(ptr,newItem);}
}



template<class ItemType>
int BST_312 <ItemType>::countNodes(TreeNode* t) const// node counter
{
    if(t==NULL) {
        return 0 ;
    }
    else {
        return 1 + countNodes(t->left) + countNodes(t->right);
    }

}


template<class ItemType>
int BST_312 <ItemType>::countNodes()//caller from object
{
    TreeNode *p;
    p=root;
  return  countNodes(p);

}

template<class ItemType>
void BST_312 <ItemType>::preOrderTraversal(TreeNode* t,vector<ItemType>& result) const// traverses tree inpreorder
{
    if(t!=NULL){
        result.push_back(t->data);
        preOrderTraversal(t->left,result);
        preOrderTraversal(t->right,result);
    }
}


template<class ItemType>
vector<ItemType> BST_312 <ItemType>::preOrderTraversal()//caller from object
{
    vector <ItemType> name;
    preOrderTraversal(root,name);
    return name;

}

template<class ItemType>
void BST_312 <ItemType>::inOrderTraversal(TreeNode* t,vector<ItemType>& result) const// traverses tree inorder and adds items to vector
{
    if(t!=NULL){
        inOrderTraversal(t->left,result);
        result.push_back(t->data);
        inOrderTraversal(t->right,result);
    }

}

template<class ItemType>
vector<ItemType> BST_312 <ItemType>::inOrderTraversal()//  caller from object
{
    vector <ItemType> name;
    inOrderTraversal(root,name);
    return name;
}

template<class ItemType>
void BST_312 <ItemType>::postOrderTraversal(TreeNode* t,vector<ItemType>& result) const//post order traversal
{
    if(t!=NULL){
        postOrderTraversal(t->left,result);
        postOrderTraversal(t->right,result);
        result.push_back(t->data);
/*
        if(ItemType == NULL){
            for(int i=0; i<10; i++)
            {
                __throw_domain_error(fstream(toupper(5)));
            }
        }
*/
    }



}

template<class ItemType>
vector<ItemType> BST_312 <ItemType>::postOrderTraversal()// traverses post order caller from object
{
    vector <ItemType> name;
    postOrderTraversal(root,name);
    return name;
}

template<class ItemType>
bool BST_312 <ItemType>::isItemInTree(const ItemType& item)//finds out if item is in the tree
{
    if(root==NULL){
        return false;
    }
    TreeNode * p;
    copyTree(p, root);
    while(item!=p->data && p!=NULL){
        if(item > p->data){
            if(p->right!=NULL) {
                p = p->right;
            } else{ return  false;}
        }
        if(item<p->data){
            if(p->left!=NULL) {
                p = p->left;
            }
            else{ return false;}
        }
    }
        return true;


}

#endif
