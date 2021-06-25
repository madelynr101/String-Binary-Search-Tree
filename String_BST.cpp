#include <iostream>
using namespace std;

// left subtree must be <= to right subtree 
struct BstNode
{
  std::string data; // stores data 
  BstNode* left; 
  BstNode* right; 
}; 

// finds minimum in tree
BstNode* FindMin(BstNode* root)
{
  while(root->left != NULL) root = root -> left; 
  return root; 
}

 // take an std::string as argument, creates a node in heap using "new", 
 // and returns address of new node 
BstNode* GetNewNode(std::string data) 
{
  BstNode* newNode = new BstNode(); // returns address of newly created node 
  // BELOW can be written as (*newNode).data... * dereference pointer 
  // . accesses 3 fields in node - data and two pointers to node, left and right 
  newNode->data = data; // access fields of newly created node and 
  newNode->left = newNode->right = NULL; // sets left and right child to NULL
  return newNode; // returns address of new node 
}

// searches for and deletes a value from tree
struct BstNode* Delete(struct BstNode *root, std::string data)
{
  if(root == NULL) return root; 
  else if(data < root->data) root-> left = Delete(root->left, data); 
  else if(data > root->data) root -> right = Delete(root->right, data);
  // data now found, now delete
  else
  {
    // no child case
    if(root->left == NULL && root-> right == NULL)
    {
      delete root; 
      root = NULL; 
    }
    // one child case 
    else if(root -> left == NULL)
    {
      struct BstNode *temp = root; 
      root = root -> right; 
      delete temp; 
    }
    else if(root -> right == NULL)
    {
      struct BstNode *temp = root; 
      root = root -> left; 
      delete temp; 
    }
    // two children case 
    else
    {
      struct BstNode *temp = FindMin(root -> right); 
      root->data = temp->data; 
      root->right = Delete(root->right, temp->data); 
    }
  }  
  return root; 
}

void Inorder(BstNode *root)
{
  if(root == NULL) return; 

  Inorder(root->left); // visit left subtree 
  cout << root->data << endl; // print data
  Inorder(root->right); // visit right subtree
}

// Inserts data into BST, returns address of root node
BstNode* Insert(BstNode* root, std::string data) 
{
  if(root == NULL) // empty tree case 
  {
    root = GetNewNode(data); // sets root as address of new node 
  }
  // data inserted is lesser or equal, insert left 
  // data inserted is greater, insert right
  else if(data <= root-> data) // not empty tree
  {
    root->left = Insert(root->left, data); // passing address of left child and 
                                           // and data as argument and after data is 
                                           // inserted in left subtree, the root of the left
                                           // subtree can change (will return address of left sub.)
                                           // and set it as left child of current node 
  }
  else
  {
    root->right = Insert(root->right, data); 
  }
  return root; 
}


// takes in argument address of root node and returns true if data is in tree
bool Search(BstNode* root, std::string data)
{
  if(root == NULL) return false; 
  else if(root->data == data) return true; 
  // search left subtree 
  else if(data <= root->data) return Search(root->left,data); 
  // search right subtree
  else return Search(root->right,data); 
}

int main()
{
  // nodes are created in heap using new op 
  BstNode* root; // stores address of root node (rootPtr)
  root = NULL; // sets tree as empty 
  root = Insert(root, "cat"); root = Insert(root, "dog"); root = Insert(root, "rabbit");  
  root = Insert(root, "squirrel"); root = Insert(root, "chipmunk"); root = Insert(root, "frog"); 
  std::string letter; 
  cout << "Enter animal to be searched\n"; 
  cin >> letter; 
  if(Search(root,letter)==true) cout << "Found\n"; 
  else cout << "Not found\n"; 
  cout << "Inorder: "; 
  Inorder(root); 
  cout << "\n"; 
  cout << "New order with deletion: " << endl; 
  root = Delete(root, "frog");  
  Inorder(root); 
}

