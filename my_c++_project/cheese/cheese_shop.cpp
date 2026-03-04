#include "cheese_shop.h"
#include <string>
#include <vector>
#include <format>

using std::string;
using std::format;

cheese_data new_cheese(string name, double weight, int price_per_kg){
    cheese_data cheese;
    cheese.name = name;
    cheese.weight = weight;
    cheese.price_per_kg = price_per_kg;
    return cheese;
}

string cheese_to_string(const cheese_data& cheese, bool full_details){
    
    if (full_details){
        return std::format("Cheese: {}, weight: {:.2f} kg, price per kg: ${:.2f}, total cost: ${:.2f}", cheese.name, cheese.weight, cheese.price_per_kg/100.0, total_cost(cheese)/100.0);
    }
    else{
        return cheese.name;
    }
}

int total_cost(const cheese_data &cheese){
    return static_cast<int>(cheese.weight * cheese.price_per_kg);
}

double reduce_weight(cheese_data &cheese, double amount){
    if (amount <= 0) return 0.0;
    
    double actual_removed = (amount > cheese.weight) ? cheese.weight : amount;
    cheese.weight -= actual_removed;
    return actual_removed;
}

void increase_weight(cheese_data &cheese, double amount){
    if (amount > 0) {
        cheese.weight += amount;
    }
}

void add_cheese(shop_data &shop, const cheese_data &cheese){
    shop.cheeses.push_back(cheese);
}

void delete_cheese(shop_data &shop, int index){
    if (index >= 0 && index < shop.cheeses.size()) {
        shop.cheeses.erase(shop.cheeses.begin() + index);
    }
}

//--------------------------
void add_supplier(shop_data &shop, const supplier_data &supplier){
    shop.suppliers.push_back(supplier);
}

void add_cheese_to_supplier(shop_data &shop, int supplier_index, const cheese_data &cheese){
    if (supplier_index >= 0 && supplier_index < shop.suppliers.size()) {
        shop.suppliers[supplier_index].cheeses.push_back(cheese);
    }
}

vector<string> get_suppliers_for_cheese(const shop_data &shop, const string &cheese_name){
    vector<string> suppliers;
    for (const auto &supplier : shop.suppliers) {
        for (const auto &cheese : supplier.cheeses) {
            if (cheese.name == cheese_name) {
                suppliers.push_back(supplier.name);
                break;
            }
        }
    }
    return suppliers;
}

void add_supplier_order(shop_data &shop, const supplier_order_data &order){
    shop.supplier_orders.push_back(order);
}

void receive_supplier_order(shop_data &shop, int order_index){
    if (order_index >= 0 && order_index < shop.supplier_orders.size()) {
        auto &order = shop.supplier_orders[order_index];
        if (!order.received) {
            for (const auto &cheese : order.cheeses) {
                cheese_data* existing = find_cheese_in_stock(shop, cheese.name);
                if (existing) {
                    increase_weight(*existing, cheese.weight);
                } else {
                    add_cheese(shop, cheese);
                }
            }
            order.received = true;
        }
    }
}

void add_cheese_to_supplier_order(shop_data &shop, int order_index, const cheese_data &cheese){
    if (order_index >= 0 && order_index < shop.supplier_orders.size()) {
        shop.supplier_orders[order_index].cheeses.push_back(cheese);
    }
}

void add_customer_order(shop_data &shop, const customer_order_data &order){
    shop.customer_orders.push_back(order);
}

void fulfill_customer_order(shop_data &shop, int order_index){
    if (order_index >= 0 && order_index < shop.customer_orders.size()) {
        auto &order = shop.customer_orders[order_index];
        if (!order.fulfilled) {
            bool can_fulfill = true;
            for (const auto &cheese : order.cheeses) {
                if (!has_sufficient_stock(shop, cheese)) {
                    can_fulfill = false;
                    break;
                }
            }
            if (can_fulfill) {
                for (const auto &cheese : order.cheeses) {
                    cheese_data* stock_cheese = find_cheese_in_stock(shop, cheese.name);
                    if (stock_cheese) {
                        reduce_weight(*stock_cheese, cheese.weight);
                    }
                }
                order.fulfilled = true;
            }
        }
    }
}

void add_cheese_to_customer_order(shop_data &shop, int order_index, const cheese_data &cheese){
    if (order_index >= 0 && order_index < shop.customer_orders.size()) {
        shop.customer_orders[order_index].cheeses.push_back(cheese);
    }
}

cheese_data* find_cheese_in_stock(shop_data &shop, const string &name){
    for (auto &cheese : shop.cheeses) {
        if (cheese.name == name) {
            return &cheese;
        }
    }
    return nullptr;
}

bool has_sufficient_stock(const shop_data &shop, const cheese_data &required_cheese){
    for (const auto &cheese : shop.cheeses) {
        if (cheese.name == required_cheese.name && cheese.weight >= required_cheese.weight) {
            return true;
        }
    }
    return false;
}