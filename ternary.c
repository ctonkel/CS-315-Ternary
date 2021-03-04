#define NULL 0
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct leaf{
	int value_a;
	int value_b; //since each leaf has two values
	struct leaf *smaller; // Pointer for the values less than both of the values
	struct leaf *middle; // Pointer for values in between the two in the leaf
	struct leaf *larger; // Pointer for the values larger than both of the values
}leaf;

////////////////////// struct for leaf ////////////////////////

leaf *makeFirstLeaf(int first_value, int second_value){
	leaf *first_leaf = (leaf *)malloc(sizeof(leaf));
	if (first_value <= second_value){
		first_leaf->value_a = first_value;
		first_leaf->value_b = second_value;
	}
	else{
		first_leaf->value_a = second_value;
		first_leaf->value_b = first_value;
	}
	// Since it is the first leaf, it will always be pointing to NULL until another leaf exists
	first_leaf->smaller = NULL;
	first_leaf->middle = NULL;
	first_leaf->larger = NULL;
	
	return(first_leaf);
}

/////////////////////// makeFirstLeaf ///////////////////////////

void makeNewLeaf(leaf *attaching_leaf, int value, int what_child){
	leaf *new_leaf = (leaf *)malloc(sizeof(leaf));
	new_leaf->value_a = value;
	new_leaf->value_b = -1; // To know when there is only one value in the leaf so you add to it instead of making a new whole leaf
	new_leaf->smaller = NULL;
	new_leaf->middle = NULL;
	new_leaf->larger = NULL;
	
	if(what_child == 1){ //smaller child
		attaching_leaf = new_leaf;
	}
	else if(what_child == 2){ //middle child
		attaching_leaf = new_leaf;
	}
	else if(what_child == 3){ //larger child
		attaching_leaf = new_leaf;
	}
}

////////////////////// makeNewLeaf ///////////////////////////

void sortTree(int what_child, int value, leaf *given_tree){
	
	leaf *temp_leaf;
	int child_num = 0;
	if(what_child == 1){ // for the left child
		temp_leaf = given_tree;
		
		while(temp_leaf != NULL && temp_leaf->value_b != -1){ // To check for if a thing has 2 values set b to -1 so that you know it is a new node also go through the process of which child
			if(value <= temp_leaf->value_a){
				
				temp_leaf = temp_leaf->smaller;
				child_num = 1;
			} //for if the value continues to be smaller
			else if(value > temp_leaf->value_a && value <= temp_leaf->value_b){
				temp_leaf = temp_leaf->middle;
				child_num = 2;
			}//for middle values
			else if(value > temp_leaf->value_b){
				temp_leaf = temp_leaf->larger;
				child_num = 3;
			}
		}
		if(temp_leaf == NULL){
			makeNewLeaf(temp_leaf, value, child_num);
		}
		else if(temp_leaf->value_b == -1){// For if there is one value in the leaf
			if(value > temp_leaf->value_a){
				temp_leaf->value_b = value;
			}
			else if(value <= temp_leaf->value_a){
				int temp_value = temp_leaf->value_a;
				temp_leaf->value_b = temp_value;
				temp_leaf->value_a = value;
			}
		}
		//else{
		//	makeNewLeaf(temp_leaf, value, child_num);
			//Make a new leaf due to being full otherwise and make it be the larger smaller etc pointer depending on size 1 = smaller 2 = middle 3 = larger
		//}
	}
	else if(what_child == 2){ // for the middle child
		temp_leaf = given_tree;
		
		while(temp_leaf != NULL && temp_leaf->value_b){
			if(value <= temp_leaf->value_a){
				temp_leaf = temp_leaf->smaller;
				child_num = 1;
			}
			else if(value > temp_leaf->value_a && value <= temp_leaf->value_b){
				temp_leaf = temp_leaf->middle;
				child_num = 2;
			}
			else if(value > temp_leaf->value_b){
				temp_leaf = temp_leaf->larger;
				child_num = 3;
			}
		}
		if(temp_leaf == NULL){
			makeNewLeaf(temp_leaf, value, child_num);
		}
		else if(temp_leaf->value_b == -1){// For if there is one value in the leaf
			if(value > temp_leaf->value_a){
				temp_leaf->value_b = value;
			}
			else if(value <= temp_leaf->value_a){
				int temp_value = temp_leaf->value_a;
				temp_leaf->value_b = temp_value;
				temp_leaf->value_a = value;
			}
		}
		//else if(temp_leaf->value_b != -1){
		//	makeNewLeaf(temp_leaf, value, child_num); // Make a new leaf for the tree
		//}
	}
	else if(what_child == 3){ // for the right child
		temp_leaf = given_tree;
		
		while(temp_leaf != NULL && temp_leaf->value_b != -1){
			if(value <= temp_leaf->value_a){
			        temp_leaf = temp_leaf->smaller;
			        child_num = 1;
			}
			else if(value > temp_leaf->value_a && value <= temp_leaf->value_b){
			        temp_leaf = temp_leaf->middle;
			        child_num = 2;
			}
			else if(value > temp_leaf->value_b){
			        temp_leaf = temp_leaf->larger;
			        child_num = 3;
			}
		}
		if(temp_leaf == NULL){
			makeNewLeaf(temp_leaf, value, child_num);
		}
		else if(temp_leaf->value_b == -1){// For if there is one value in the leaf
		        if(value > temp_leaf->value_a){
		                temp_leaf->value_b = value;
			}
		        else if(value <= temp_leaf->value_a){
		                int temp_value = temp_leaf->value_a;
		                temp_leaf->value_b = temp_value;
		                temp_leaf->value_a = value;
		        
			}
		}
		
		//else{
		//	makeNewLeaf(temp_leaf, value, child_num); // Make a new leaf for the tree
		//}						        
	}
	
}

////////////////////// sortTree //////////////////////////////

void printTree(leaf *tree_to_print){
// recursive function going until the smallest then printing and then going to the right if it exists and if not goes back to the previous left most prints then goes the the right if it exists etc
	if(tree_to_print != NULL){
		printf("%d : ", tree_to_print->value_b);
		printTree(tree_to_print->smaller); // To reach the left-most node
		printf("%d : ", tree_to_print->value_a);
		printTree(tree_to_print->middle); // To then go down the middle
		//printf("%d : ", tree_to_print->value_a);
		if(tree_to_print->value_b != -1){
			printf("%d : ", tree_to_print->value_b);
		}
		printTree(tree_to_print->larger);
		//if(tree_to_print->value_b != -1){
		//	printf("%d : ", tree_to_print->value_b);
	
		//}

	}
	
}

///////////////////// printTree //////////////////////////////

int main(int argc, char *argv[]){
	
	if(argc < 2){
		printf("Too few arguments");			
		return (-1);
	}	
	int num_values = atoi(argv[1]);
	int values[num_values];
	int rand_num;
	for(int i = 0; i < num_values; i++){ // for loop to get the values for the values array
		rand_num = rand();
		values[i] = (rand_num % 10000) + 1;
	
	}
	leaf *leaf_tree = makeFirstLeaf(values[0], values[1]); // This is the first leaf, which is used to compare the rest of the tree to know where to put them
	
	for(int j = 2; j < num_values; j++){
		int temp_value;
	
		temp_value = values[j];		
		if(temp_value <= leaf_tree->value_a){
			sortTree(1, values[j], leaf_tree);	
			//put in here some way to insert left of the main value and go down that line until it is no longer less than or it can be inserted
		} // To be less than both of the values, also the ones that are equal to always go left
		else if(temp_value <= leaf_tree->value_b && temp_value > leaf_tree->value_a){
			sortTree(2, values[j], leaf_tree);
		
		
			// Find a way to go through the middle children to find its spot
		} // For the middle child being less than largest and greater than smallest
		else if(temp_value > leaf_tree->value_b){
			sortTree(3, values[j], leaf_tree);
		
			// Find a way to go through the right children to find its spot
		} // For the right child being more than both values
	}
	printTree(leaf_tree);
	return 0;
}

/////////////////////// main //////////////////////////////////////////
