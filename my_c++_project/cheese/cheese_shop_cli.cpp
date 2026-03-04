#include "splashkit.h"
#include "utilities.h"
#include "cheese_shop.h"
#include <format>

using std::format;


/**
 * The list of option in the main menu.
 * 
 * @option EXIT_MAIN_MENU The option to exit the main menu
 * @option ADD_CHEESE_MENU The option to add a cheese to the stock list
 * @option EDIT_CHEESE_MENU The option to edit a cheese in the stock list
 * @option DELETE_CHEESE_MENU The option to delete a cheese from the stock list
 * @option PRINT_STOCK_LIST_MENU The option to print the stock list
 * @option SUPPLIER_MENU The option to manage suppliers
 * @option SUPPLIER_ORDER_MENU The option to manage supplier orders
 * @option CUSTOMER_ORDER_MENU The option to manage customer orders
 */
enum main_menu_option{
    EXIT_MAIN_MENU,
    ADD_CHEESE_MENU,
    EDIT_CHEESE_MENU,
    DELETE_CHEESE_MENU,
    PRINT_STOCK_LIST_MENU,
    SUPPLIER_MENU,
    SUPPLIER_ORDER_MENU,
    CUSTOMER_ORDER_MENU
};

/**
 * Print the cheese data to the console.
 * 
 * @param cheese The cheese data to print
 */
void print_cheese(const cheese_data &cheese, bool with_full_details){
    write_line(cheese_to_string(cheese, with_full_details));
}


/**
 * read data from the user and populate and return the cheese data to the caller
 * 
 * @return cheese_data populate with the data read from the user
 */
cheese_data read_cheese(){
    cheese_data result;

    result.name = read_string("Enter the name of the cheese: ");
    result.weight = read_double("Enter the weight of the cheese (kg): ");
    result.price_per_kg= read_integer("Enter the price per kg (cents): ");

    return result;
}

/**
 * Perform the steps needed to add a cheese to the shop
 * 
 * @param shop the shop where the cheese is to be added
 */
void handle_add_cheese(shop_data &shop){
    cheese_data cheese = read_cheese();

    add_cheese(shop, cheese);
}

/**
 * Perform the steps needed to print the shop's stock list
 *
 * @param shop the shop whose stock list is to be printed
 */
void print_stock_list(shop_data &shop){
   if (shop.cheeses.size() == 0){
       write_line("No cheeses in stock!");
       return;
   }
   write_line("================================");
   write_line("Cheese Stock List");
   write_line("================================");

   for (int i = 0; i < shop.cheeses.size(); i++){
       print_cheese(shop.cheeses[i], true);
   }

   write_line();
}


/**
 * Allow the user to edit the passed in cheese 
 * 
 * @param cheese a refrence to the cheese to be updated
 */
void edit_cheese(cheese_data &cheese){


    write_line("================================");
    write_line("Edit cheese: ");
    write_line("================================");
    write_line("Editing cheese: " + cheese_to_string(cheese,true));

    if (read_integer_limit("Do you want to edit the name? (1 for yes, 0 for no): ",0,1) == 1){
        cheese.name = read_string("Enter the new name of the cheese: ");
    }
    if (read_integer_limit("Do you want to edit the weight? (1 for yes, 0 for no): ",0,1) == 1){
        cheese.weight = read_double("Enter the new weight in stock (kg): ");
    }
    if (read_integer_limit("Do you want to edit the price per kg? (1 for yes, 0 for no): ",0,1) == 1){
        cheese.price_per_kg = read_integer("Enter the new price per kg (cents): ");
    }
}

/**
 * output these cheese - optionally with the index
 * 
 * @param cheese the details to output
 * @param with_ids true if an index (1 based) should be included in the output
 */
void print_cheese_list(const vector<cheese_data> &cheeses, bool with_ids){
    for (int i = 0; i < cheeses.size(); i++){
        cheese_data cheese = cheeses[i];
        if (with_ids){
            write(format("{}: ", i+1));
        }
        print_cheese(cheeses[i], true);
    }
}

/**
 * Ask the user to select a cheese from the supplied list. this return teh index of the chosen cheese, or -1 if none are selected.
 * 
 * @param cheese the cheese to output
 * @return int the index of the chosen cheese or -1 if none
 * 
 */
int select_cheese(const vector<cheese_data> &cheeses){
    write_line("================================");
    write_line("Select cheese: ");
    write_line("================================");
    if (cheeses.size() == 0){
        write_line("No cheeses in stock!");
        return -1;
    }   
    write_line("0. select none");
    print_cheese_list(cheeses, true);
    return read_integer_limit("Select a cheese (0-" + std::to_string(cheeses.size()) + "): ", 0, cheeses.size()) - 1;
}

/**
 * Perform the steps needed to handle the user's choice in the main menu
 *
 * @param choice the user's choice
 * @param shop the shop where the cheese is to be added
 */
main_menu_option read_main_menu_choice(){
    write_line("================================");
    write_line("Main Menu: ");
    write_line("================================");
    write_line("0. Exit");
    write_line("1. Add cheese");
    write_line("2. Edit cheese");
    write_line("3. Delete cheese");
    write_line("4. Print cheese list");
    write_line("5. Manage suppliers");
    write_line("6. Manage supplier orders");
    write_line("7. Manage customer orders");

    return (main_menu_option)read_integer_limit("Select an option (0-7): ",0,7);
}

/**
 * Perform the steps to allow the user to edit a cheese in the shop
 * 
 * @param shop the shop whose cheese is to be edited
 */
void handle_edit_cheese(shop_data &shop){
    int index = select_cheese(shop.cheeses);
    write_line("");
    if (index != -1){
        edit_cheese(shop.cheeses[index]);
    }
}

/**
 * Perform the steps to allow the user to delete a cheese from the shop
 * 
 * @param shop the shop whose cheese is to be deleted
 */
void handle_delete_cheese(shop_data &shop){
    int index = select_cheese(shop.cheeses);
    write_line("");
    if (index != -1){
        delete_cheese(shop, index);
        write_line("Cheese deleted successfully.");
    }
}

/**
 * Handle supplier management menu
 * 
 * @param shop the shop whose suppliers are to be managed
 */
void handle_supplier_menu(shop_data &shop){
    write_line("================================");
    write_line("Supplier management: ");
    write_line("================================");
    write_line("1. Add supplier");
    write_line("2. Add cheese to supplier");
    write_line("3. List suppliers for cheese");
    int choice = read_integer_limit("Select option (1-3): ", 1, 3);
    
    if (choice == 1) {
        supplier_data supplier;
        supplier.name = read_string("Enter supplier name: ");
        add_supplier(shop, supplier);
        write_line("Supplier added successfully.");
    } else if (choice == 2) {
        if (shop.suppliers.empty()) {
            write_line("No suppliers available.");
            return;
        }
        write_line("Select supplier:");
        for (int i = 0; i < shop.suppliers.size(); i++) {
            write_line(format("{}: {}", i+1, shop.suppliers[i].name));
        }
        int supplier_idx = read_integer_limit("Select supplier: ", 1, shop.suppliers.size()) - 1;
        cheese_data cheese = read_cheese();
        add_cheese_to_supplier(shop, supplier_idx, cheese);
        write_line("Cheese added to supplier.");
    } else {
        string cheese_name = read_string("Enter cheese name: ");
        vector<string> suppliers = get_suppliers_for_cheese(shop, cheese_name);
        if (suppliers.empty()) {
            write_line("No suppliers found for this cheese.");
        } else {
            write_line("Suppliers for " + cheese_name + ":");
            for (const string &supplier : suppliers) {
                write_line("- " + supplier);
            }
        }
    }
}

/**
 * Handle supplier order management menu
 * 
 * @param shop the shop whose supplier orders are to be managed
 */
void handle_supplier_order_menu(shop_data &shop){
    write_line("================================");
    write_line("supplier order management: ");
    write_line("================================");
    write_line("1. Create supplier order");
    write_line("2. Add cheese to order");
    write_line("3. Receive order");
    int choice = read_integer_limit("Select option (1-3): ", 1, 3);
    
    if (choice == 1) {
        supplier_order_data order;
        order.supplier_name = read_string("Enter supplier name: ");
        order.received = false;
        add_supplier_order(shop, order);
        write_line("Supplier order created.");
    } else if (choice == 2) {
        if (shop.supplier_orders.empty()) {
            write_line("No supplier orders available.");
            return;
        }
        write_line("Select order:");
        for (int i = 0; i < shop.supplier_orders.size(); i++) {
            write_line(format("{}: {} ({})", i+1, shop.supplier_orders[i].supplier_name, 
                      shop.supplier_orders[i].received ? "Received" : "Pending"));
        }
        int order_idx = read_integer_limit("Select order: ", 1, shop.supplier_orders.size()) - 1;
        cheese_data cheese = read_cheese();
        add_cheese_to_supplier_order(shop, order_idx, cheese);
        write_line("Cheese added to order.");
    } else {
        if (shop.supplier_orders.empty()) {
            write_line("No supplier orders available.");
            return;
        }
        write_line("Select order to receive:");
        for (int i = 0; i < shop.supplier_orders.size(); i++) {
            if (!shop.supplier_orders[i].received) {
                write_line(format("{}: {}", i+1, shop.supplier_orders[i].supplier_name));
            }
        }
        int order_idx = read_integer_limit("Select order: ", 1, shop.supplier_orders.size()) - 1;
        receive_supplier_order(shop, order_idx);
        write_line("Order received and stock updated.");
    }
}

/**
 * Handle customer order management menu
 * 
 * @param shop the shop whose customer orders are to be managed
 */
void handle_customer_order_menu(shop_data &shop){
    write_line("================================");
    write_line("customer order management: ");
    write_line("================================");
    write_line("1. Create customer order");
    write_line("2. Add cheese to order");
    write_line("3. Fulfill order");
    int choice = read_integer_limit("Select option (1-3): ", 1, 3);
    
    if (choice == 1) {
        customer_order_data order;
        order.customer_name = read_string("Enter customer name: ");
        order.fulfilled = false;
        add_customer_order(shop, order);
        write_line("Customer order created.");
    } else if (choice == 2) {
        if (shop.customer_orders.empty()) {
            write_line("No customer orders available.");
            return;
        }
        write_line("Select order:");
        for (int i = 0; i < shop.customer_orders.size(); i++) {
            write_line(format("{}: {} ({})", i+1, shop.customer_orders[i].customer_name,
                      shop.customer_orders[i].fulfilled ? "Fulfilled" : "Pending"));
        }
        int order_idx = read_integer_limit("Select order: ", 1, shop.customer_orders.size()) - 1;
        cheese_data cheese = read_cheese();
        add_cheese_to_customer_order(shop, order_idx, cheese);
        write_line("Cheese added to order.");
    } else {
        if (shop.customer_orders.empty()) {
            write_line("No customer orders available.");
            return;
        }
        write_line("Select order to fulfill:");
        for (int i = 0; i < shop.customer_orders.size(); i++) {
            if (!shop.customer_orders[i].fulfilled) {
                write_line(format("{}: {}", i+1, shop.customer_orders[i].customer_name));
            }
        }
        int order_idx = read_integer_limit("Select order: ", 1, shop.customer_orders.size()) - 1;
        fulfill_customer_order(shop, order_idx);
        write_line("Order fulfilled and stock updated.");
    }
}

int main()
{
   shop_data shop;
   main_menu_option choice;

   do {
    choice = read_main_menu_choice();

    switch (choice)
    {
        case EXIT_MAIN_MENU:
            write_line("Exiting....");
            break;
        
        case ADD_CHEESE_MENU:
            write_line("");
            handle_add_cheese(shop);
            write_line("");
            break;
        
        case EDIT_CHEESE_MENU:
            write_line("");
            handle_edit_cheese(shop);
            write_line("");
            break;

        case DELETE_CHEESE_MENU:
            write_line("");
            handle_delete_cheese(shop);
            write_line("");
            break;

        case PRINT_STOCK_LIST_MENU:
            write_line("");
            print_stock_list(shop);
            write_line("");
            break;
        
        case SUPPLIER_MENU:
            write_line("");
            handle_supplier_menu(shop);
            write_line("");
            break;
        
        case SUPPLIER_ORDER_MENU:
            write_line("");
            handle_supplier_order_menu(shop);
            write_line("");
            break;
        
        case CUSTOMER_ORDER_MENU:
            write_line("");
            handle_customer_order_menu(shop);
            write_line("");
            break;
        
    }
   }while (choice != EXIT_MAIN_MENU);  
   return 0;
}