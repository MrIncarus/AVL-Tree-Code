//###############################//
//#######    Mr.Incarus   #######//
//###############################//

#include <iostream>
#include <stdlib.h> //  atoi
#include <fstream>  //  filling dot file
#include <algorithm> 
#include <iostream> //  cout
#include <ctime>  //time
#include <ratio>
#include <chrono> // high resolution clock
#include <string> //  words in file
#include <stdio.h>  // for stream
#include <string.h>
#include <sstream>  //  stringstream
using namespace std;
struct node
{
  int element;
  node *left;
  node *right;
  int height;  //   height is the main point of AVL tree, so we hold this info to rotate when height difference is high
};

typedef struct node *myTree;   

class bstree
{

  public:
    void insert(int,myTree &);       //  insert method gets and integer and my tree referance, so we can reach the tree
void del(int, myTree &);         //  del method gets the same parameters as insert 
void find(int,myTree &);         //  find method finds a given number, if its in the tree 
void preorder(myTree);           //  
void inorder(myTree);            //  these are for just checking the three if its working very well or not.
void postorder(myTree);          //
int bsheight(myTree);            //  this is so important because we always need to calculate the height of the tree.


myTree LeftRotation(myTree &);   //  LEFT ROTATION MEANS, LEFT IS HEAVY SO ROTATE RIGHT  #########//
myTree RightRotation(myTree &);  //  RIGHT ROTATION MEANS, RIGHT IS HEAVY SO ROTATE LEFT #########//
myTree DoubleLeft(myTree &);     //  left right rotation
myTree DoubleRight(myTree &);    //  right left rotation


int max(int,int);                //  when we need to find height of the root, we can add 1 to max of left or right subtree height
int deletemin(myTree &);
};

//######### BSTree class ends here ##########//


//#############  Finding an element  #############//
//  If the given number is bigger than root,     #//
//   then we extend and search the right subtree #//
//  but if the number is less than root,         #//
//   then extend and search left subtree         #//
//################################################//
void bstree::find(int findThisItem,myTree &myRoot)
{
  if (myRoot==NULL){}
  //cout<<"Element cannot be found in the AVL tree.";
  else if (findThisItem < myRoot->element)
    find(findThisItem,myRoot->left);
  else if (findThisItem>myRoot->element)
    find(findThisItem,myRoot->right);
  else{}
  //cout<<"We have found the item that you are looking for.";
}
//###############################################//


//############ Insert method #############//
//# Adds given integer value to the tree #//
//########################################//
void bstree::insert(int addThisToTree,myTree &myRoot)
{
  if (myRoot == NULL)  // this means that tree is empty, so we are creating the  root
  {
    myRoot = new node;
    myRoot->element = addThisToTree;
    myRoot->left=NULL;
    myRoot->right = NULL;
    myRoot->height=0;
  }
  else
  {
    if (addThisToTree<myRoot->element) //  if we are adding a small number than root, then go left
    {
      insert(addThisToTree,myRoot->left); //  calls the recursive function so it can go to left sub tree
      if ((bsheight(myRoot->left) - bsheight(myRoot->right))==2)  //  if our height difference between left and right subtree
      {                                                           //  then rotate either left or right, so we always make the tree balanced
        if (addThisToTree < myRoot->left->element)
          myRoot=LeftRotation(myRoot);      // left rotation means that right subtree is heavy
        else 
          myRoot = DoubleLeft(myRoot);      //   double right means first left right rotation means that left subtree is heavy
      }
    }
    else if (addThisToTree>myRoot->element)  //  if we are adding a bigger number than root, then move right
    {
      insert(addThisToTree,myRoot->right); //  go right
      if ((bsheight(myRoot->right) - bsheight(myRoot->left))==2) //  check if we need to balance the tree
      {
        if (addThisToTree > myRoot->right->element)
          myRoot=RightRotation(myRoot);    //  ROTATE TO LEFT, BECAUSE RIGHT IS HEAVY
        else
          myRoot = DoubleRight(myRoot);  
      }
    }
    else{}
    //cout<<"Your element is already in the tree";
  }

  //################################################
  int height_LeftSub,height_RightSub,height_Root;
  height_LeftSub=bsheight(myRoot->left);
  height_RightSub=bsheight(myRoot->right);
  height_Root=max(height_LeftSub,height_RightSub);
  myRoot->height = height_Root + 1;
  // After all actions on the tree, we need to get
  // new height for the root of the AVL tree
  // so we can rotate if there is a problem.
  // To get root's height, we are adding 1 to max of
  // left and right subtrees
  //################################################
}




//#############  Deleting an element  ############//
//  Find the given number in the tree and then   #//
//   delete it                                   #//
//################################################//
void bstree::del(int deleteThisItem,myTree &myRoot)
{
  myTree myNode;
  if (myRoot==NULL){}
  //cout<<"Element cannot be found in the AVL tree ";
  else if ( deleteThisItem < myRoot->element)
    del(deleteThisItem,myRoot->left);
  else if (deleteThisItem > myRoot->element)
    del(deleteThisItem,myRoot->right);
  else if ((myRoot->left == NULL) && (myRoot->right == NULL))  //  If we have only root as node, and we are trying to delete it, this works
  {
    myNode=myRoot;
    free(myNode);  //Deallocate memory block so we can use them again and again
    myRoot=NULL;
    //cout<<"deleted !";
  }
  else if (myRoot->left == NULL)   // If we hava a root and right node
  {
    myNode=myRoot;
    free(myNode);
    myRoot=myRoot->right;
    //cout<<"deleted !";
  }
  else if (myRoot->right == NULL)  //  If we have root and left node
  {
    myNode=myRoot;
    myRoot=myRoot->left;
    free(myNode);
    //cout<<"deleted !";
  }
  else{
    myRoot->element = deletemin(myRoot->right);  // In my design, im looking for the min element of the right subtree
   	if ((bsheight(myRoot->left) - bsheight(myRoot->right))==2)  //  if our height difference between left and right subtree
          myRoot=LeftRotation(myRoot);      // left rotation means that right subtree is heavy
 	
	if ((bsheight(myRoot->right) - bsheight(myRoot->left))==2) //  check if we need to balance the tree
          myRoot=RightRotation(myRoot);    //  ROTATE TO LEFT, BECAUSE RIGHT IS HEAVY
             
}
//  in lots of examples, they used the max of the left subtree
}
//############## deleting ends here ##################//


//### Deleting minimum number of given node's subtree ###//
//# When we are trying to delete a node, which is in a  #//
//#  critical place like it has 2 childs and they have  #//
//#  also childs, then the program deletes it and       #//
//#  replaces it with the min number of right subtree   #//
//#######################################################//
int bstree::deletemin(myTree &myRoot)
{
  int temp;       
  if (myRoot->left == NULL)
  {
    temp = myRoot->element;
    myRoot = myRoot->right;
    return temp;
  }
  else
  {
    temp = deletemin(myRoot->left); // go left until we find the last element before NULL
    return temp;
  }
}
//#######################################################//


//######  THESE ARE THE PRINTING METHODS  ######//
void bstree::inorder(myTree myRoot)
{
  if (myRoot!=NULL)
  {
    inorder(myRoot->left);
    cout<<myRoot->element<<"-->";
    inorder(myRoot->right);
  }
}
//###############################################//


//################ BS height ####################//
//  finds and returns the height of the AVL tree
int bstree::bsheight(myTree myRoot)
{
  int theHeight;
  if (myRoot == NULL)
    return -1;
  else
  {
    theHeight = myRoot->height;
    return theHeight;
  }
}
//#################################################//


//  Finds and returns the max value between two integers
//  This is used to find which sub tree is higher
int bstree::max(int value1, int value2)
{
  return ((value1 > value2) ? value1 : value2);
}
//################################################


//########### Left rotation #############//
//# Left rotation is the method that I  #//
//# used to rotate the subtree to right #//
//# because right is heavier than left  #//
//#######################################//
//IF tree is right heavy  
//  IF tree's right subtree is left heavy  
//     Do Double Left rotation   
//  ELSE 
//     Do Single Left rotation 
//ELSE IF tree is left heavy 
//  IF tree's left subtree is right heavy  
//     Do Double Right rotation   
//  ELSE 
//     Do Single Right rotation 
// This is the pseudocode of rotations
//#######################################//


myTree bstree::RightRotation(myTree &mainNode)// ACTUALLY LEFT ROTATION
{
  myTree newNode;
  newNode = mainNode -> right;
  mainNode -> right = newNode -> left;
  newNode -> left = mainNode;

  mainNode->height = max(bsheight(mainNode->left),bsheight(mainNode->right)) + 1;
  newNode->height = max(mainNode->height,bsheight(newNode->right)) + 1;
  return newNode;
}

myTree bstree::LeftRotation(myTree &mainNode)//RIGHT ROTATION
{
  myTree newNode;
  newNode = mainNode -> left;
  mainNode -> left = newNode -> right;
  newNode -> right = mainNode;

  mainNode->height = max(bsheight(mainNode->left),bsheight(mainNode->right)) + 1;	//ALWAYS CHECK HEIGHT
  newNode->height = max(bsheight(newNode->left),mainNode->height) + 1;			//SET ROOT HEIGHT
  return newNode;
}
myTree bstree::DoubleLeft(myTree &mainNode) //left right like zigzag
{
  mainNode->right = LeftRotation(mainNode->right);
  return RightRotation(mainNode);
}
myTree bstree::DoubleRight(myTree &mainNode)//right left like zigzag as well
{
  mainNode->left=RightRotation(mainNode->left);
  return LeftRotation(mainNode);
}



//###################################################################################//
//                       This part of code is belongs to                             //
//   http://eli.thegreenplace.net/2009/11/23/visualizing-binary-trees-with-graphviz  //
//   I wrote some functions to create dot file as this one as well,but used this one //
//###################################################################################//


void printNullPoint(int key, int nullcount, FILE* stream) //  This method prints a null pointer into the avlTree.dot file
{
  fprintf(stream, "    null%d [shape=point];\n", nullcount);  //  Shape=point, because of the NIL, if we dont write this, then we cannot get the dot for null
  fprintf(stream, "    %d -> null%d;\n", key, nullcount);
}

void printNodeElement(myTree node, FILE* stream)
{
  static int nullcount = 0;

  if (node->left)
  {
    fprintf(stream, "    %d -> %d;\n", node->element, node->left->element);
    printNodeElement(node->left, stream);
  }
  else
    printNullPoint(node->element, nullcount++, stream);

  if (node->right)
  {
    fprintf(stream, "    %d -> %d;\n", node->element, node->right->element);
    printNodeElement(node->right, stream);
  }
  else
    printNullPoint(node->element, nullcount++, stream);
}

void createDotFile(myTree tree, FILE* stream) // This is the first called function to generate dot file
{
  fprintf(stream, "digraph AVLTree {\n");

  if (!tree)
    fprintf(stream, "\n");
  else if (!tree->right && !tree->left)
    fprintf(stream, "    %d;\n", tree->element);
  else    // If tree has elements, then call printNodeElement funciton
    printNodeElement(tree, stream);

  fprintf(stream, "}\n");
}
//################################################################################//

int main()
{

  using namespace std::chrono;  // To use high_resolution_clock


  FILE *fileDirectory_Dot = fopen("printAVL.dot","w+");
                            //  I want to put dot file into the graphviz folder, so I can directly use
                            //  dot -Tpng avlTree.dot>>avl.png
                            //  OR dot -Tpng avlTree.dot -O
  myTree root;
  bstree myBSTree;
  root = NULL;
  ifstream is("case0.txt");
  string arr[512];
  int indexOfArr=0;
  string word; 
  while( is >> word ) {
    arr[indexOfArr]=word;
    indexOfArr++;

  }
  // I wanted to put every word in the text file to my arr array
  //  so that i can reach every word easily

  int index=0;  // for checking array elements

  high_resolution_clock::time_point t1 = high_resolution_clock::now();  //  Doing actions start here 

  while(index<indexOfArr){

    if(arr[index].compare("i")==0){         // If the word is i, then call insert method
      myBSTree.insert(atoi(arr[index+1].c_str()) , root );  // I used atoi method to convert string to integer, so I can add them into tree
    }

    if(arr[index].compare("f")==0){         //  If the word is f,
      if (root != NULL)
        myBSTree.find(atoi(arr[index+1].c_str()),root);     // I used atoi method to convert string to integer, so I can add them into tree
    }

    if(arr[index].compare("d")==0){
      if (root != NULL)
        myBSTree.del(atoi(arr[index+1].c_str()),root);      // I used atoi method to convert string to integer, so I can add them into tree
    }
    index++;  //  To check every element in the text file
  }

  is.close();

  high_resolution_clock::time_point t2 = high_resolution_clock::now();
  duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
  cout << "AVLTree  " << time_span.count()*10000;


 createDotFile(root,fileDirectory_Dot);

  fclose (fileDirectory_Dot);
  cout<<"\t";
  //myBSTree.inorder(root);  //  This code is to check if the tree is generated correct or not.
	
  return 0;
}

 
//###############################//
//#######    Mr.Incarus   #######//
//###############################//