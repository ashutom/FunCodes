
//Print binary tree in reverse level order

/*

		1						1
	   / \					   /  \
	  2	  3					  2	   3
	 /\	  /\				/	\
	4  5 6  7			   4	5
	
	print == > 4,5,6,7,2,3,1

*/

#include<iostream>
#include<queue>
#include<string.h>

using namespace std;

int FeederArray[]={1,2,3,4,5,6,7,8,9};

//template<class T>
//T max(T i, T j)	{	return ( (i>=j)?i:j);	}

#define max(i,j)	((i>=j)?i:j)	
#define	MAX_TREE_HEIGHT_WIDTH	25

int MaxLeftColFromRoot=0;
int MaxRightColFromRoot=0;
int MaxWidth=0;
bool ColCalculated=false;
bool LevelCalculated = false;
int TreeHeight=0;

int TreeArray[MAX_TREE_HEIGHT_WIDTH][MAX_TREE_HEIGHT_WIDTH];

struct node	{
	int mVal;
	node* mRight;
	node* mLeft;
	int mAtWhicLevel;
	int mAtWhichColumn;
	node(int val=0) :	mVal(val), mRight(NULL), mLeft(NULL), mAtWhicLevel(0),mAtWhichColumn(0)	{}
	~node()	{	
		if(mLeft)	{	delete mLeft;	}
		if(mRight)	{	delete mRight;	}
		mLeft=mRight=NULL; //just for readability else it doesn't adds any value;
	}
};

void DFSTravelNFillTreeArray(node* root)	{
	if(!root)	return;
	
	TreeArray[TreeHeight-root->mAtWhicLevel][root->mAtWhichColumn-MaxLeftColFromRoot]=root->mVal;
	DFSTravelNFillTreeArray(root->mLeft);
	DFSTravelNFillTreeArray(root->mRight);
}


void SetCoumns(node* root, int col)	{ // col is the col number of the root node coming in param
	if(!root)	{	return;	}
	if(root->mLeft)	{	
		root->mLeft->mAtWhichColumn=col-1;	
		if(root->mLeft->mAtWhichColumn < MaxLeftColFromRoot){	
			MaxLeftColFromRoot = root->mLeft->mAtWhichColumn;
		}
	}
	if(root->mRight)	{	
		root->mRight->mAtWhichColumn=col+1;
		if(root->mRight->mAtWhichColumn > MaxRightColFromRoot){	
			MaxRightColFromRoot = root->mRight->mAtWhichColumn;
		}
	}
	if(root->mLeft)	{	SetCoumns(root->mLeft,root->mLeft->mAtWhichColumn);	}
	if(root->mRight)	{	SetCoumns(root->mRight,root->mRight->mAtWhichColumn);	}
}

int Setlevel(node* root)	{
	if(!root)	{	return	-1;	}
	
	root->mAtWhicLevel= max<int>( Setlevel(root->mLeft), Setlevel(root->mRight)	)+1;
	
	return root->mAtWhicLevel;
}

void PrintAtLevel(node* root, int level, bool LeftToRight)	{ // can be used in zigzag as well

	if(!root) 	return;
		if(level == root->mAtWhicLevel)	{	cout<<root->mVal<<"\t";	}
	if(LeftToRight)	{	//printing left to right nodes at this level
		PrintAtLevel(root->mLeft,level,LeftToRight);
		PrintAtLevel(root->mRight,level,LeftToRight);
	}else	{	//printing left to right nodes at this level
		PrintAtLevel(root->mRight,level,LeftToRight);
		PrintAtLevel(root->mLeft,level,LeftToRight);
	}
}


void print_reverse_level(node* root)	{
	
	if(!TreeHeight)	{
		TreeHeight = Setlevel(root);//levels are set;
	}

	LevelCalculated = true;
	for(int counter=0;counter<=TreeHeight;counter++)	{
		PrintAtLevel(root,counter,true);
	}
}


node* ConstructTreeFromArray(int ArraySize)	{
	int counter=0;
	node* root =new node(FeederArray[counter++]);
	node* iterator=root;
	std::queue<node*> Q; Q.push(root);
	while(counter<ArraySize-2)	{
		iterator= Q.front();Q.pop();
		iterator->mLeft= new node(FeederArray[counter++]); Q.push(iterator->mLeft);
		iterator->mRight= new node(FeederArray[counter++]); Q.push(iterator->mRight);
	}
	if(counter<ArraySize)	{
		iterator= Q.front();Q.pop();
		iterator->mLeft= new node(FeederArray[counter++]); Q.push(iterator->mLeft);	
	}
	if(counter<ArraySize)	{
		iterator->mRight= new node(FeederArray[counter++]); Q.push(iterator->mRight);	
	}
	return root;
}

void PrintBinaryTree(node* root)	{

	memset(TreeArray,0,sizeof(TreeArray));
	SetCoumns(root,0);
	ColCalculated = true;
	MaxWidth	=	MaxRightColFromRoot	- (MaxLeftColFromRoot);
	if(!TreeHeight)	{
		TreeHeight = Setlevel(root);//levels are set;
	}
	//Travers Any Way & fill the data
	DFSTravelNFillTreeArray(root);
	
	//Now, just print

	cout<<"\n\n\n";
	for(int i=0;i<=TreeHeight;i++){
		cout<<"\n";
		for(int j =0;j<=MaxWidth;j++)	{
				if(0==TreeArray[i][j])	{	cout<<" ";	}
				else	{	cout<<TreeArray[i][j];	}
				cout<<"  ";
		}
	}

	cout<<"\n\n\n";
	for(int i=0;i<=TreeHeight;i++)	{
		cout<<"\n";
		for(int j =0;j<=MaxWidth;j++)	{
				cout<<TreeArray[i][j]<<"  ";
		}
	}
	
cout<<"\n\n\n";

	
}



//now main
int main()	{
	cout<<endl;
	node* root = ConstructTreeFromArray(sizeof(FeederArray)/sizeof(int));
	PrintBinaryTree(root);
	print_reverse_level(root);
	
	cout<<endl;
	return 0;
}























