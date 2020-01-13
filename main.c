


//          OSMAN MANTICI
//              150117505
//     DATA STRUCTURES PROJECT #2





    #include<stdlib.h>
    #include<stdio.h>
    #include<stdbool.h>
    #include<limits.h>


    struct bst{

        int data;
        struct bst* left;
        struct bst* right;
    };

    typedef struct bst treeNode;


    treeNode* newNode(int data){

        treeNode *temp = (treeNode*)malloc(sizeof(treeNode));
        temp->data = data;
        temp->left = NULL;
        temp->right = NULL;

        return temp;
    }


    treeNode* insertTree(treeNode* root, int data ){

        if(root == NULL){

            return newNode(data);
        }

        if(data<root->data){

            root->left = insertTree(root->left, data);
        }
        else if(data>root->data){
            root->right = insertTree(root->right, data);
        }

        return root;
    }

    void swap(int *a, int *b){
        int temp;
        temp = *a;
        *a = *b;
        *b = temp;
    }


    void printArray(int arr[], int size)
    {
        int i;

        printf("Sequence: \n");
        for(i=0; i<size; i++)
        {
            printf("%d\t", arr[i]);
        }
        printf("\n");
    }


    bool isSameSequenceControl(int a[], int b[], int i1, int i2, int min, int max, int numberOfNodes){
        int j, k;

        /* Search for a value satisfying the constraints of min and max in a[] and
           b[]. If the parent element is a leaf node then there must be some
           elements in a[] and b[] satisfying constraint. */
        for (j=i1; j<numberOfNodes; j++)
            if (a[j]>min && a[j]<max)
                break;
        for (k=i2; k<numberOfNodes; k++)
                if (b[k]>min && b[k]<max)
                break;

        /* If the parent element is leaf in both arrays */
        if (j==numberOfNodes && k==numberOfNodes)
                return true;

        /* Return false if any of the following is true
           a) If the parent element is leaf in one array, but non-leaf in other.
           b) The elements satisfying constraints are not same. We either search
              for left child or right child of the parent element (decinded by min
              and max values). The child found must be same in both arrays */
        if (((j==numberOfNodes)^(k==numberOfNodes)) || a[j]!=b[k])
                return false;

        /* Make the current child as parent and recursively check for left and right
           subtrees of it. Note that we can also pass a[k] in place of a[j] as they
           are both are same */
        return isSameSequenceControl(a, b, j+1, k+1, a[j], max, numberOfNodes) &&  // Right Subtree
                    isSameSequenceControl(a, b, j+1, k+1, min, a[j], numberOfNodes);    // Left Subtree
    }

    bool isSameSequence(int a[], int b[], int numberOfNodes)   {
        return isSameSequenceControl(a, b, 0, 0, INT_MIN, INT_MAX, numberOfNodes);
    }


    void findSameSequence(int array[], int contArray[], int start, int end, int numberOfNodes){

        bool flag;

        if(start==end){

            flag = isSameSequence(array, contArray, numberOfNodes);

            if(flag){
                printArray(array, end );
            }
        }
        int i;
        for(i=start; i<=end; i++){
            //swapping numbers
            swap((array+i), (array+start));
            //fixing one first digit
            //and calling permutation on
            //the rest of the digits
            findSameSequence(array, contArray, start+1, end, numberOfNodes);
            swap((array+i), (array+start));
        }
    }




    void printOrder(treeNode * tree, int* array, int *i){

        if (tree == NULL)
            return;

        if(tree){

            array[*i] = tree->data;
            (*i)++;

            printOrder(tree->left, array, i);
            printOrder(tree->right, array, i);
        }
    }


    void printPreOrder(treeNode * tree){

        if(tree){
            printf("%d\t", tree->data);
            printPreOrder(tree->left);
            printPreOrder(tree->right);
        }
    }




    int main(){

        FILE *fileptr = fopen("C:\\Users\\osman\\CLionProjects\\BST\\input.txt", "r");

        char str[5];
        int number;

        int array[15];
        int contArray[15];

        int iter = 0;
        int numberOfNodes = 0;

        treeNode *rootForTree = NULL;
        treeNode *temp = NULL;

        temp = rootForTree;

        while(!feof(fileptr)){

            fscanf(fileptr, "%s", str);
            number = atoi(str);
            rootForTree = insertTree(rootForTree, number);
            array[iter] = number;
            iter++;
            numberOfNodes++;
        }



        temp = rootForTree;

        printf("Here is the constructed Binary Search Tree will be printed in preorderly.\n");

        printPreOrder(temp);

        temp = rootForTree;



        int i = 0;
        printOrder(temp, contArray, &i);


        int count = 0;
        printf("count before printing sequences %d\n ", count);

        findSameSequence(array, contArray, 0, 15, numberOfNodes);// (arr, 0, size-1);

        printf("count after printing sequences%d ", count);

        fclose(fileptr);
        return 0;
    }