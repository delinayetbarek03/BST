#ifndef bst_hpp
#define bst_hpp




#include <string>
#include <utility>




class Tree {
public:
    Tree();

    Tree(const Tree&);
    ~Tree();

    Tree(Tree&&);
    Tree& operator=(Tree);


    class iterator;
    using const_iterator = iterator;
    iterator begin() const;
    iterator end()   const;


    void insert(std::string);
    void erase(iterator);

    bool find(const std::string&) const;
    void swap(Tree&);


private:
    class node {
        node(std::string);

        std::string val;
        node* parent;
        node* left;
        node* right;

        void insert_node(node*);
        node* far_left();
        node* far_right();

        friend Tree;
    };


    node* root;

    void traverse_insert(node*);
    void delete_tree(node*);
};


void swap(Tree&, Tree&);




class Tree::iterator {
public:
    const std::string& operator*() const;
    const std::string* operator->() const;

    iterator& operator++();
    iterator& operator--();
    iterator  operator++(int);
    iterator  operator--(int);

private:
    iterator(const Tree*, node*);

    const Tree* container;
    node* curr;

    friend Tree;
    friend bool operator!=(const iterator&, const iterator&);
};




#endif /* bst_hpp */
