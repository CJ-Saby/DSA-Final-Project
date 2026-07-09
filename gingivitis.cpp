#include <iostream>

class list {
    private:
        struct NodeSingly { //singly linked list
            std::string product_name, product_type, product_ID;
            int quantity;
            double unit_cost;
            NodeSingly *next;
        };
        NodeSingly *head = nullptr;
    public:
}
