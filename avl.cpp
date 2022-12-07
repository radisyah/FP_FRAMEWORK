#include<stdio.h>
#include<stdlib.h>

struct node{
  int key;
  int height;
  struct node *left, *right;
};

int max(int a, int b){
  if(a>b) 
    return a;
  else
    return b;
}


int getHeight(struct node *root){
  if(root==NULL) return 0;
  return root->height;
}

int getBF(struct node *root){
  if(root==NULL)
    return 0;
  return getHeight(root->left)-getHeight(root->right);
  
}

struct node *newNode(int x){
  struct node *curr = (struct node *)malloc(sizeof(struct node));
  curr->key=x;
  curr->height=1;
  curr->left=curr->right= NULL;
  return curr;
}

struct node *rightRotate(struct node *y){
  struct node *x = y->left;
  struct node *B = x->right;

  // rotate
  x->right = y;
  y->left = B;

  y->height = max(getHeight(y->left), getHeight(y->right))+1;
  x->height = max(getHeight(x->left), getHeight(x->right))+1;

  return x;
}

struct node *leftRotate(struct node *x){
  struct node *y = x->right;
  struct node *B = y->right;

  // rotate
  y->left = x;
  x->right = B;

  y->height = max(getHeight(y->left), getHeight(y->right))+1;
  x->height = max(getHeight(x->left), getHeight(x->right))+1;

  return y;
}

struct node *insert(struct node *root, int value){
  if(root == NULL) return newNode(value);
  else if(value<root->key){
    root->left = insert(root->left, value);
  }else{
    root->right = insert(root->right, value);
  }

  root->height = max(getHeight(root->left), getHeight(root->right))+1;
  int bfactor = getBF(root);

  if(bfactor > 1 && value<root->left->key){
    return rightRotate(root);
  }

  if(bfactor<-1 && value<root->right->key){
    return leftRotate(root);
  }

  if(bfactor>1 && value>root->left->key){
    root->left = leftRotate(root->left);
    return rightRotate(root);
  }

   if(bfactor<-1 && value<root->right->key){
    root->right = rightRotate(root->right);
    return leftRotate(root);
  }

  return root;
}

void printAll(struct node *root){
  if(root==NULL) return;
  printAll(root->left);
  printf("%d ", root->key);
  printAll(root->right);
}

struct node *freeAll(struct node *root){
  if(root==NULL) return NULL;
  root->left = freeAll(root->left);
  root->right = freeAll(root->right);
  free(root);
  return NULL;
}

int main(){
  //Deklarasi 
  struct node * root = NULL;

  root = insert(root, 10);
  root = insert(root, 5);
  root = insert(root, 7);

  printAll(root);printf("\n");

  root = freeAll(root);
 return 0;
}