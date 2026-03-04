#include <string>
#include <vector>

using std::string;
using std::vector;

/**
 * data about a cheese within an oder or in stock.
 * 
 * @field name The name of the cheese
 * @field weight The weight of the cheese(kg)
 * @field price_per_kg The price of the cheese per kg(cents)
 */
struct cheese_data
{
    string name;
    double weight;
    int price_per_kg;
};

/**
 * Initialise a cheese_data value - with parameters to initialise the name.
 * weight, and price_per_kg
 *
 * @param name The name of the cheese. Defaults to an empty string.
 * @param weight The weight of the cheese in stock (kg). Defaults to 0.0
 * @param price_per_kg The price of the cheese per kg (cents). Defaults to 0.
 */
cheese_data new_cheese(string name = "", double weight = 0.0, int price_per_kg = 0);

/**
 * Convert a cheese_data value to a string.
 *
 * @param cheese The cheese_data value to convert.
 * @param full_details If true, include full details of the cheese. default to false.
 * 
 * @return A string representation of the cheese_data value.
 */
string cheese_to_string(const cheese_data &cheese, bool full_details = false);

/**
 * Calculate the total cost of a cheese in cents.
 *
 * @param cheese The cheese_data value to calculate cost for.
 * @return The total cost in cents.
 */
int total_cost(const cheese_data &cheese);

/**
 * Reduce the weight of a cheese by a specified amount.
 *
 * @param cheese Reference to the cheese_data to modify.
 * @param amount The amount to reduce (negative values ignored).
 * @return The actual amount removed.
 */
double reduce_weight(cheese_data &cheese, double amount);

/**
 * Increase the weight of a cheese by a specified amount.
 *
 * @param cheese Reference to the cheese_data to modify.
 * @param amount The amount to add (negative values ignored).
 */
void increase_weight(cheese_data &cheese, double amount);

/**
 * Data about a cheese within an order of in stock
 * 
 * @field name The name of the cheese
 * @field weight The weight of the cheese(kg)
 * @field price_per_kg The price of the cheese per kg(cents)
 */
struct cheese_order
{
    string name;
    double weight;
    int price_per_kg;
};

/**
 * Data about a supplier
 * 
 * @field name The name of the supplier
 * @field cheeses The list of cheeses this supplier provides
 */
struct supplier_data
{
    string name;
    vector<cheese_data> cheeses;
};

/**
 * Data about a supplier order
 * 
 * @field supplier_name The name of the supplier
 * @field cheeses The list of cheeses in the order
 * @field received Whether the order has been received
 */
struct supplier_order_data
{
    string supplier_name;
    vector<cheese_data> cheeses;
    bool received;
};

/**
 * Data about a customer order
 * 
 * @field customer_name The name of the customer
 * @field cheeses The list of cheeses in the order
 * @field fulfilled Whether the order has been fulfilled
 */
struct customer_order_data
{
    string customer_name;
    vector<cheese_data> cheeses;
    bool fulfilled;
};

/**
 * Data about the cheese shop - stock on hand
 * 
 * @field cheese The list of cheeses in stock
 * @field suppliers The list of suppliers
 * @field supplier_orders The list of supplier orders
 * @field customer_orders The list of customer orders
 */
struct shop_data
{
    vector<cheese_data> cheeses;
    vector<supplier_data> suppliers;
    vector<supplier_order_data> supplier_orders;
    vector<customer_order_data> customer_orders;
};

/**
 * Add a new cheese to the shop's stock.
 *
 * @param shop The cheese_shop to add
 * @param cheese The cheese_data to add.
 */
void add_cheese(shop_data &shop, const cheese_data &cheese);

/**
 * Delete a cheese from the shop's stock by index.
 *
 * @param shop The cheese_shop to delete from
 * @param index The index of the cheese to delete.
 */
void delete_cheese(shop_data &shop, int index);

/**
 * Add a new supplier to the shop.
 *
 * @param shop The shop to add the supplier to.
 * @param supplier The supplier data to be added.
 */
void add_supplier(shop_data &shop, const supplier_data &supplier);

/**
 * Add a cheese to a specific supplier.
 *
 * @param shop The shop containing the supplier.
 * @param supplier_index The index of the supplier in the shop's list.
 * @param cheese The cheese to add to the supplier.
 */
void add_cheese_to_supplier(shop_data &shop, int supplier_index, const cheese_data &cheese);

/**
 * Get the names of all suppliers that provide a specific cheese.
 *
 * @param shop The shop to search.
 * @param cheese_name The name of the cheese to look for.
 * @return A vector of supplier names that supply the given cheese.
 */
vector<string> get_suppliers_for_cheese(const shop_data &shop, const string &cheese_name);


/**
 * Add a new supplier order to the shop.
 *
 * @param shop The shop to add the order to.
 * @param order The supplier order data to be added.
 */
void add_supplier_order(shop_data &shop, const supplier_order_data &order);

/**
 * Mark a supplier order as received and update stock accordingly.
 *
 * @param shop The shop containing the order.
 * @param order_index The index of the order to mark as received.
 */
void receive_supplier_order(shop_data &shop, int order_index);

/**
 * Add a cheese item to a supplier order.
 *
 * @param shop The shop containing the order.
 * @param order_index The index of the supplier order.
 * @param cheese The cheese to add to the order.
 */
void add_cheese_to_supplier_order(shop_data &shop, int order_index, const cheese_data &cheese);

/**
 * Add a new customer order to the shop.
 *
 * @param shop The shop to add the customer order to.
 * @param order The customer order data to be added.
 */
void add_customer_order(shop_data &shop, const customer_order_data &order);

/**
 * Fulfill a customer order by reducing stock accordingly.
 *
 * @param shop The shop containing the customer order.
 * @param order_index The index of the customer order to fulfill.
 */
void fulfill_customer_order(shop_data &shop, int order_index);

/**
 * Add a cheese item to a customer order.
 *
 * @param shop The shop containing the order.
 * @param order_index The index of the customer order.
 * @param cheese The cheese to add to the order.
 */
void add_cheese_to_customer_order(shop_data &shop, int order_index, const cheese_data &cheese);
/**
 * Find a cheese in the shop's stock by name.
 *
 * @param shop The shop to search.
 * @param name The name of the cheese to find.
 * @return A pointer to the cheese_data if found, nullptr otherwise.
 */
cheese_data* find_cheese_in_stock(shop_data &shop, const string &name);

/**
 * Check if the shop has sufficient stock of a required cheese.
 *
 * @param shop The shop to check.
 * @param required_cheese The cheese and quantity required.
 * @return True if there is enough stock, false otherwise.
 */
bool has_sufficient_stock(const shop_data &shop, const cheese_data &required_cheese);