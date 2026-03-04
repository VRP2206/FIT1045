#include "splashkit.h"
#include <stdio.h>

const int MAX_PRODUCT = 100;


/**
 * struct representing a single product in the shop
 *
 * @field name       - the name of the product
 * @field cost       - the cost price of the product
 * @field sale       - the sale price of the product
 * @field stock_have - the number of units currently in stock
 */
struct product_data{
    string name;
    double cost;
    double sale;
    int stock_have;     
};

/**
 * struct representing the shop's product database
 *
 * @field product - an array of products stored in the shop
 * @field current_product - the number of products currently stored
 * @field sales - the total sales value recorded
 * @field profit - the total profit recorded
 */
struct shop_data{
    product_data product[MAX_PRODUCT];
    int current_product = 0; 
    double sales = 0;
    double profit = 0;
};

/** Add a new product to the shop database.
 *
 * @param shop passed by reference; new product details are added to the shop
 */
void add_new_product(shop_data &shop){
    int i = shop.current_product;

    if(i>99)
    {
        write_line("All avaliable space for product have been allocated :(");
        return;
    }

    write("Enter the name of product: ");
    shop.product[i].name = read_line();
    write("Enter cost: ");
    shop.product[i].cost = convert_to_double(read_line());
    write("Enter sale: ");
    shop.product[i].sale = convert_to_double(read_line());
    write("Enter number available: ");
    shop.product[i].stock_have = stoi(read_line());   
    shop.current_product += 1;
}

/** Search for products matching a given name.
 *
 * @param shop passed by reference; the shop database to search
 * @param name the search keyword to match against product names
 * @param matches output array; stores indexes of matching products
 *
 * @return the number of matching products found
 */
int search_product(shop_data &shop, string name, int matches[])
{
    int count = 0;
    for (int i = 0; i < shop.current_product; i++)
    {
        if (contains(shop.product[i].name, name))
        {
            write_line(std::to_string(count + 1) + ". " + shop.product[i].name +
                       " (Cost: " + std::to_string(shop.product[i].cost) +
                       ", Sale: " + std::to_string(shop.product[i].sale) +
                       ", Qty: " + std::to_string(shop.product[i].stock_have) + ")");
            matches[count] = i;
            count++;
        }
    }
    return count;
}

/** Delete a product from the shop database by name (and user selection).
 *
 * @param shop passed by reference; product is removed from the shop
 */
void delete_product(shop_data &shop){
    write("Enter name to search: ");
    string name = read_line();
    int matches[MAX_PRODUCT];
    int count = search_product(shop, name, matches);

    if (count == 0)
    {
        write_line("No products found.");
        return;
    }

    write("Select product number to delete: ");
    int choice = stoi(read_line());

    while (!(choice >0 && choice <= count) || choice == -1)
    {
        write_line("Invalid choice.  {Enter -1 if you want to cancel}");
        write("Select product number to delete: ");
        choice = stoi(read_line());
    }
    if (choice == -1){
        return;
    }

    int idx = matches[choice - 1];
    for (int i = idx; i < shop.current_product - 1; i++)
    {
        shop.product[i] = shop.product[i + 1];
    }
    shop.current_product--;

    write_line("Product deleted.");
}

/** Update the details of an existing product.
 *
 * @param shop passed by reference; product information is updated
 */
void update(shop_data &shop){
    write("Enter name to search: ");
    string name = read_line();
    int matches[MAX_PRODUCT];
    int count = search_product(shop, name, matches);

    if (count == 0)
    {
        write_line("No products found.");
        return;
    }

    write("Select product number to update: ");
    int choice = stoi(read_line());

    while (!(choice >0 && choice <= count) || choice == -1)
    {
        write_line("Invalid choice.  {Enter -1 if you want to cancel}");
        write("Select product number to update: ");
        choice = stoi(read_line());
    }
    if (choice == -1){
        return;
    }

    int idx = matches[choice - 1];

    do
    {
        write_line("What is it you wish to update");
        write_line("1. Update name");
        write_line("2. Update cost");
        write_line("3. Update sale");
        write_line("4. Update number on hand");
        write_line("5. Quit");
        choice = stoi(read_line());

        switch (choice)
        {
        case 1:
            write("Enter new name: ");
            shop.product[idx].name = read_line();
            write_line("Name successfully updated");
            break;
        
        case 2:
            write("Enter new cost price: ");
            shop.product[idx].cost = convert_to_double(read_line());
            write_line("Cost price successfully updated");
            break;

        case 3:
            write("Enter new sale price: ");
            shop.product[idx].sale = convert_to_double(read_line());
            write_line("Sale price successfully updated");
            break;

        case 4:
            write("Enter new number on hand: ");
            shop.product[idx].stock_have = stoi(read_line());
            write_line("Number on hand successfully updated");
            break;

        case 5:
            write_line("");
            write_line("Updated records(if any); ");
            write_line("name: " + shop.product[idx].name + " | Cost: " + std::to_string(shop.product[idx].cost) + " | Sale: " + std::to_string(shop.product[idx].sale) + " | Qty: " + std::to_string(shop.product[idx].stock_have));
            return;
            break;

        default:
            write_line("Invalid choice, try again...");        
            break;
        }
    } while (choice != 5);
      

}

/** Record a sale transaction for a product.
 *
 * @param shop passed by reference; product stock, sales, and profit are updated
 */
void sell(shop_data &shop){
    write("Enter name to search: ");
    string name = read_line();
    int matches[MAX_PRODUCT];
    int count = search_product(shop, name, matches);

    if (count == 0)
    {
        write_line("No products found.");
        return;
    }

    write("Select product number to update: ");
    int choice = stoi(read_line());

    while (!(choice >0 && choice <= count) || choice == -1)
    {
        write_line("Invalid choice.  {Enter -1 if you want to cancel}");
        write("Select product number to update: ");
        choice = stoi(read_line());
    }
    if (choice == -1){
        return;
    }

    int idx = matches[choice - 1];
    write_line("");
    write("Enter number of unit sold: ");
    int sold = stoi(read_line());

    if (sold <= shop.product[idx].stock_have){
        shop.product[idx].stock_have -= sold;
        shop.sales += sold * shop.product[idx].sale;
        shop.profit += (sold * shop.product[idx].sale - sold * shop.product[idx].cost);
    }
    else{
        write_line("Insufficient product in stock");

    }
}

/** Print a detailed report of the shop's current status.
 *
 * @param shop passed by constant reference; no changes are made
 */
void print_shop_details(const shop_data &shop){
    printf("=================REPORT=================\n");
    printf("Total sale value: %lf\n", shop.sales);
    printf("Total profit: %lf\n", shop.profit);
    printf("Number of product: %d\n", shop.current_product);
    double total_cost = 0;
    for(int i =0; i < shop.current_product; i++){
        total_cost += shop.product[i].cost * shop.product[i].stock_have;
    }
    printf("Value of stock on hand %lf\n", total_cost);
    int low_stock = 0 ;
    for (int i =0; i < shop.current_product; i++){
        if (shop.product[i].stock_have < 10){
            low_stock += 1;
        }
    }
    printf("The number of low stock product is: %d\n", low_stock);
}

/** Main entry point of the program.
 *
 * Provides a menu-based interface to manage the shop’s products,
 * including adding, deleting, updating, selling, and printing reports.
 *
 * @return program exit code (0 for successful termination)
 */
int main()
{
    shop_data shop;

    int choice;

    do
    {
        write_line("===== Product Database =====");
        write_line("1. Add Product");
        write_line("2. Delete Product");
        write_line("3. Update Product");
        write_line("4. Sell Product");
        write_line("5. Print Status");
        write_line("6. Quit");

        write("Enter choice: ");
        choice = stoi(read_line());

        switch (choice)
        {
        case 1:
            write_line("");
            add_new_product(shop);
            break;
        case 2:
            write_line("");
            delete_product(shop);
            break;
        case 3:
            write_line("");
            update(shop);
            break;
        case 4:
            write_line("");
            sell(shop);
            break;
        case 5:
            write_line("");
            print_shop_details(shop);
            break;
        case 6:
            write_line("");
            write_line("Exiting...");
            break;
        default:
            write_line("");
            write_line("Invalid choice. Try again.");
        }
        write_line("");
    } while (choice != 6);

    return 0;
}