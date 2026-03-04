# Cheese Shop Extension Design

## Data Structure Overview

```
┌─────────────────────────────────────────────────────────────┐
│                        shop_data                            │
├─────────────────────────────────────────────────────────────┤
│  vector<cheese_data> cheeses                                │
│  ┌─────────────────────────────────────────────────────┐    │
│  │                cheese_data [0]                      │    │
│  │  ┌─────────────────────────────────────────────┐    │    │
│  │  │ string name                                 │    │    │
│  │  │ double weight (kg)                          │    │    │
│  │  │ int price_per_kg (cents)                    │    │    │
│  │  └─────────────────────────────────────────────┘    │    │
│  └─────────────────────────────────────────────────────┘    │
│  ┌─────────────────────────────────────────────────────┐    │
│  │                cheese_data [1]                      │    │
│  │  ┌─────────────────────────────────────────────┐    │    │
│  │  │ string name                                 │    │    │
│  │  │ double weight (kg)                          │    │    │
│  │  │ int price_per_kg (cents)                    │    │    │
│  │  └─────────────────────────────────────────────┘    │    │
│  └─────────────────────────────────────────────────────┘    │
│                        ...                                  │
└─────────────────────────────────────────────────────────────┘
```

## New Functions Added

### Core Operations
- **`total_cost(cheese_data)`** - Calculates total value (weight × price_per_kg)
- **`reduce_weight(cheese_data&, amount)`** - Safely reduces weight, returns actual removed
- **`increase_weight(cheese_data&, amount)`** - Adds weight, ignores negatives
- **`delete_cheese(shop_data&, index)`** - Removes cheese from vector by index

### CLI Integration
- Extended menu with delete option (0-4 range)
- `handle_delete_cheese()` uses existing `select_cheese()` for consistency
- Enhanced `cheese_to_string()` displays total cost in detailed view

## Key Design Decisions

**Weight Management**: `reduce_weight()` prevents negative weights and returns actual amount removed, enabling accurate stock tracking for future order fulfillment.

**Data Integrity**: All operations include bounds checking and input validation to prevent invalid states.

**User Interface**: Reuses existing selection mechanism (`select_cheese()`) for consistent user experience across edit/delete operations.

**Cost Calculation**: `total_cost()` provides real-time inventory valuation, automatically displayed in detailed cheese listings.