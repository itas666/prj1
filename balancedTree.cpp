#include "balancedTree.h"

int max(int a, int b){
    return (a > b)? a : b;
}

int height(Node *N){
    if (N == NULL)
        return 0;
    return N->height;
}

Node* newNode(std::shared_ptr<Event> key){
    Node* node = new Node();
    node->key = key;
    node->left = NULL;
    node->right = NULL;
// new node is initially added at leaf
    node->height = 1;
    return(node);
}

Node* rightRotate(Node* y){
    Node *x = y->left;
    Node *T2 = x->right;
 
    // Perform rotation
    x->right = y;
    y->left = T2;
 
    // Update heights
    y->height = std::max(height(y->left),
                    height(y->right)) + 1;
    x->height = std::max(height(x->left),
                    height(x->right)) + 1;
 
    // Return new root
    return x;
}

Node* leftRotate(Node *x){
    Node *y = x->right;
    Node *T2 = y->left;
 
    // Perform rotation
    y->left = x;
    x->right = T2;
 
    // Update heights
    x->height = std::max(height(x->left),   
                    height(x->right)) + 1;
    y->height = std::max(height(y->left),
                    height(y->right)) + 1;
 
    // Return new root
    return y;
}

int getBalance(Node *N){
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

Node* insert(Node* node, std::shared_ptr<Event> key){
    /* 1. Perform the normal BST insertion */
    if (node == NULL){
		return(newNode(key));
	}
	
    if (key->getEventDate() < node->key->getEventDate()){
        node->left = insert(node->left, key);
	}else if(key->getEventDate() > node->key->getEventDate()){
        node->right = insert(node->right, key);
	}else{
	// I do not allow events at the same time
		std::cout << "There is already an event at this time" << std::endl;
        return node;
	}

    /* 2. Update height of this ancestor node */
    node->height = 1 + std::max(height(node->left),
                        height(node->right));
 
    /* 3. Get the balance factor of this ancestor
        node to check whether this node became
        unbalanced */
    int balance = getBalance(node);
 
    // If this node becomes unbalanced, then there are 4 cases
 
    // Left Left Case
    if (balance > 1 && key->getEventDate() < node->left->key->getEventDate()){
        return rightRotate(node);
	}
 
    // Right Right Case
    if (balance < -1 && key->getEventDate() > node->right->key->getEventDate()){
        return leftRotate(node);
	}
 
    // Left Right Case
    if (balance > 1 && key->getEventDate() > node->left->key->getEventDate()){
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
 
    // Right Left Case
    if (balance < -1 && key->getEventDate() < node->right->key->getEventDate()){
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
 
    /* return the (unchanged) node pointer */
    return node;
}

void inOrder(Node *root){
    if(root != NULL)
    {
        inOrder(root->left);
        root->key->readEventData();
        inOrder(root->right);
    }
}

Node* search(Node* root, std::string eventName){
	Node* auxNode = NULL;
    if(root != NULL){
		if(root->key->getEventName() == eventName) return root;
		
        auxNode = search(root->left, eventName);
		if (auxNode == NULL){
			auxNode = search(root->right, eventName);
		}
	}
	return auxNode;
}

std::string send_tree_to_file(Node* root){
	std::string result = "";
    if(root != NULL)
    {
        result = result + send_tree_to_file(root->left);
		
        result = result + root->key->saveEventDataString();
		
        result = result + send_tree_to_file(root->right);
    }

	return result;
}