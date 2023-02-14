#include "bst.hpp"




Tree::Tree() : root(nullptr) {}

void Tree::insert(std::string val) {
    if (root) {
        root->insert_node(new node(std::move(val)));
    }
    else {
        root = new node(std::move(val));
    }
}

Tree::node::node(std::string v) : val(std::move(v)), parent(nullptr), left(nullptr), right(nullptr) {}

void Tree::node::insert_node(node* n) {
    if (n->val < val) {
        if (left) {
            left->insert_node(n);
        }
        else {
            left = n;
            left->parent = this;
        }
    }
    else if (val < n->val) {
        if (right) {
            right->insert_node(n);
        }
        else {
            right = n;
            right->parent = this;
        }
    }
    else {
        delete n;
    }
}



bool Tree::find(const std::string& s) const {
    node* n = root;
    
    while(n) { // keep searching until there's no more nodes
        
        if( s < n->val ) {
            n = n->left;
        }
        else if ( s > n->val ) {
            n = n->right;
        }
        else if ( s == n->val ) {
            return true;
        }
        
    }
    return false;
}




void Tree::swap(Tree& t) {
    std::swap(root, t.root);
}

void swap(Tree& t1, Tree& t2) {
    t1.swap(t2);
}



void Tree::delete_tree(node* n) {
    if(n) {
        if (n->left)  { delete_tree(n->left);  }
        if (n->right) { delete_tree(n->right); }
        delete n;
    }
    
}

Tree::~Tree() {
    delete_tree(root);
}



Tree::iterator::iterator(const Tree* t, node* n) : container(t), curr(n) {}


const std::string& Tree::iterator::operator*() const {
    return (curr->val);
}

bool operator!=(const Tree::iterator& it1, const Tree::iterator& it2) {
    return (it1.curr != it2.curr) || (it1.container != it2.container);
}

Tree::iterator Tree::iterator::operator++(int) {
    Tree::iterator pre_increment(*this);
    ++(*this);
    return pre_increment;
}


Tree::iterator Tree::iterator::operator--(int) {
    Tree::iterator pre_decrement(*this);
    --(*this);
    return pre_decrement;
}






Tree::node* Tree::node::far_right() {
    node* n = this;

    while (n->right) {
        n = n->right;
    }
    return n;
}





Tree::Tree(Tree&& other) : Tree() {
    swap(other);
}

Tree& Tree::operator=(Tree other) {
    swap(other);
    return *this;
}




void Tree::traverse_insert(node* n) {
    if (n) {
        insert(n->val);
        if (n->left)  { traverse_insert(n->left);  }
        if (n->right) { traverse_insert(n->right); }
    }
}





 Tree::Tree(const Tree& other) : Tree() { traverse_insert(other.root); }





const std::string* Tree::iterator::operator->() const {
    return &(curr->val);
}









Tree::node* Tree::node::far_left() {
    node* n = this;

    while (n->left) {
        n = n->left;
    }
    return n;
}






Tree::iterator Tree::begin() const {
    if (root) {
        return iterator(this, root->far_left());
    }
    return iterator(this, nullptr);
}
Tree::iterator Tree::end() const {
    return iterator(this, nullptr);
}









Tree::iterator& Tree::iterator::operator++() {
    if (!curr) {
        return *this;
    }
    else if(curr->right) {
        curr = curr->right->far_left();
    }
    else {
        while( (curr->parent) && (curr->parent->left != curr) ) { // if node we're on now(curr) is NOT the parents left node meaning STOP when where we're at (parent) is GREATER than curr
            curr = curr->parent;
    }
        curr = curr->parent;
    }

    return *this;
}





Tree::iterator& Tree::iterator::operator--() {
    if (!curr) {
        if (container && container->root) {
            curr = container->root->far_right();
        }
        return *this;
    }

    else if(curr->left) {
        curr = curr->left->far_right();
    }
    else {
        while( (curr->parent) && (curr->parent->right != curr) ) { // if node we're on now is NOT the parents right node, if node we're on rn(the parent's) right child IS THE CURRENT node, means the node we're at has a value immediately LESS THAN all the previous ones so it the one we're looking for
            curr = curr->parent;
    }
        curr = curr->parent;
    }

    return *this;
}




void Tree::erase(iterator it) {
    if (!it.curr || (it.container != this)) {
        return;
    }

    if (it.curr->left) {
        it.curr->val = std::move(it.curr->left->far_right()->val);
        erase(--it);
        return;
    }
    if (it.curr->right) {
        it.curr->val = std::move(it.curr->right->far_left()->val);
        erase(++it);
        return;
    }
    if (it.curr == root) {
        delete root; root = nullptr;
        return;
    }

    if (it.curr->parent->left == it.curr) {
        it.curr->parent->left = nullptr;
    }
    else {
        it.curr->parent->right = nullptr;
    }
    delete it.curr;
    return;
}
