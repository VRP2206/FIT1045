#include "catch_amalgamated.hpp"
#include "cheese_shop.h"

using Catch::Approx;

TEST_CASE("cheese - Create new cheese with default valuse"){
    cheese_data cheese;
    cheese = new_cheese();

    REQUIRE(cheese.name == "");
    REQUIRE(cheese.weight == 0.0);
    REQUIRE(cheese.price_per_kg == 0);
}

TEST_CASE("cheese - Create new cheese with non - default valuse"){
    cheese_data cheese;
    cheese = new_cheese("cheddar", 2.3,4000);

    REQUIRE(cheese.name == "cheddar");
    REQUIRE(cheese.weight == Approx(2.3));
    REQUIRE(cheese.price_per_kg == 4000);
}
   
TEST_CASE("cheese - Create new cheese with mix of default and non - default valuse"){
    cheese_data cheese;
    cheese = new_cheese("cheddar");

    REQUIRE(cheese.name == "cheddar");
    REQUIRE(cheese.weight == 0.0);
    REQUIRE(cheese.price_per_kg == 0);
}

TEST_CASE("total_cost - Calculate cost for different cheese values"){
    cheese_data cheese1 = new_cheese("Cheddar", 1.5, 2000);
    REQUIRE(total_cost(cheese1) == 3000);
    
    cheese_data cheese2 = new_cheese("Brie", 0.5, 4000);
    REQUIRE(total_cost(cheese2) == 2000);
    
    cheese_data cheese3 = new_cheese("Gouda", 2.0, 1500);
    REQUIRE(total_cost(cheese3) == 3000);
    
    cheese_data cheese4 = new_cheese("Empty", 0.0, 1000);
    REQUIRE(total_cost(cheese4) == 0);
}

TEST_CASE("reduce_weight - Normal weight reduction"){
    cheese_data cheese = new_cheese("Cheddar", 2.0, 1000);
    double removed = reduce_weight(cheese, 0.5);
    
    REQUIRE(removed == Approx(0.5));
    REQUIRE(cheese.weight == Approx(1.5));
}

TEST_CASE("reduce_weight - Reduce more than available weight"){
    cheese_data cheese = new_cheese("Cheddar", 1.5, 1000);
    double removed = reduce_weight(cheese, 1.7);
    
    REQUIRE(removed == Approx(1.5));
    REQUIRE(cheese.weight == Approx(0.0));
}

TEST_CASE("reduce_weight - Ignore negative values"){
    cheese_data cheese = new_cheese("Cheddar", 2.0, 1000);
    double removed = reduce_weight(cheese, -0.5);
    
    REQUIRE(removed == Approx(0.0));
    REQUIRE(cheese.weight == Approx(2.0));
}

TEST_CASE("reduce_weight - Zero reduction"){
    cheese_data cheese = new_cheese("Cheddar", 2.0, 1000);
    double removed = reduce_weight(cheese, 0.0);
    
    REQUIRE(removed == Approx(0.0));
    REQUIRE(cheese.weight == Approx(2.0));
}

TEST_CASE("increase_weight - Normal weight increase"){
    cheese_data cheese = new_cheese("Cheddar", 1.0, 1000);
    increase_weight(cheese, 0.5);
    
    REQUIRE(cheese.weight == Approx(1.5));
}

TEST_CASE("increase_weight - Ignore negative values"){
    cheese_data cheese = new_cheese("Cheddar", 1.0, 1000);
    increase_weight(cheese, -0.5);
    
    REQUIRE(cheese.weight == Approx(1.0));
}

TEST_CASE("increase_weight - Zero increase"){
    cheese_data cheese = new_cheese("Cheddar", 1.0, 1000);
    increase_weight(cheese, 0.0);
    
    REQUIRE(cheese.weight == Approx(1.0));
}

TEST_CASE("delete_cheese - Delete from middle of list"){
    shop_data shop;
    add_cheese(shop, new_cheese("Cheddar", 1.0, 1000));
    add_cheese(shop, new_cheese("Brie", 2.0, 2000));
    add_cheese(shop, new_cheese("Gouda", 1.5, 1500));
    
    delete_cheese(shop, 1);
    
    REQUIRE(shop.cheeses.size() == 2);
    REQUIRE(shop.cheeses[0].name == "Cheddar");
    REQUIRE(shop.cheeses[1].name == "Gouda");
}

TEST_CASE("delete_cheese - Delete invalid index"){
    shop_data shop;
    add_cheese(shop, new_cheese("Cheddar", 1.0, 1000));
    
    delete_cheese(shop, -1);
    delete_cheese(shop, 5);
    
    REQUIRE(shop.cheeses.size() == 1);
    REQUIRE(shop.cheeses[0].name == "Cheddar");
}

TEST_CASE("delete_cheese - Delete last remaining cheese"){
    shop_data shop;
    add_cheese(shop, new_cheese("Cheddar", 1.0, 1000));
    
    delete_cheese(shop, 0);
    
    REQUIRE(shop.cheeses.size() == 0);
}
   
TEST_CASE("Shop - Can add cheese to the shop")
{
    shop_data shop;

    cheese_data cheese = new_cheese("Cheddar", 1.5, 2000);
    add_cheese(shop, cheese);

    REQUIRE(shop.cheeses.size() == 1);
    REQUIRE(shop.cheeses[0].name == "Cheddar");
    REQUIRE(shop.cheeses[0].weight == Approx(1.5));
    REQUIRE(shop.cheeses[0].price_per_kg == 2000);

    // Add another cheese
    cheese = new_cheese("Gouda", 2.0, 1500);
    add_cheese(shop, cheese);

    REQUIRE(shop.cheeses.size() == 2);
    REQUIRE(shop.cheeses[1].name == "Gouda");
    REQUIRE(shop.cheeses[1].weight == Approx(2.0));
    REQUIRE(shop.cheeses[1].price_per_kg == 1500);
    // Check the first cheese again
    REQUIRE(shop.cheeses[0].name == "Cheddar");
    REQUIRE(shop.cheeses[0].weight == Approx(1.5));
    REQUIRE(shop.cheeses[0].price_per_kg == 2000);
}