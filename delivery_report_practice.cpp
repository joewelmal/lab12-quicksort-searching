
/*
 * Course: COEN 2220 - Programming 2
 * Name: [Joewel Maldonado]
 * Lab: Lab 12 - Quicksort and Searching
 * Description: Campus Cafeteria Delivery Report Practice
 * Due date: [10 November 2026]
 */

#include <iostream>
#include <string>
using namespace std;

struct Order
{
    int orderId;
    string orderType;
    string status;
    string building;
    int priority;
};

void displayOrders(const Order orders[], int count);
void displayDelivery(Order *view[], int count);
bool isActiveDelivery(const Order& order);
bool comesBefore(const Order *left, const Order *right);
void swapOrderPointers(Order *&left, Order *&right);
int partitionDelivery(Order *view[], int first, int last);
void quickSortDelivery(Order *view[], int first, int last);
int linearFindDelivery(Order *view[], int count, int target);

int main()
{
    const int CAPACITY = 6;

    Order orders[CAPACITY] = {
        {420, "DELIVERY", "PENDING", "Biblioteca", 1},
        {180, "DELIVERY", "IN_PROGRESS", "Ingenieria", 3},
        {650, "DINE_IN", "PENDING", "Cafeteria-Lunch", 1},
        {310, "DELIVERY", "PENDING", "Biblioteca", 3},
        {205, "DELIVERY", "PENDING", "Biblioteca", 3},
        {900, "DELIVERY", "COMPLETED", "Ingenieria", 2}
    };

    Order *deliveryView[CAPACITY];
    int deliveryCount = 0;

    // Display the original orders.
    cout << "Original order records:" << endl;
    displayOrders(orders, CAPACITY);

    // Create a temporary view of active delivery orders.
    for (int index = 0; index < CAPACITY; index++)
    {
        if (isActiveDelivery(orders[index]))
        {
            deliveryView[deliveryCount] = &orders[index];
            deliveryCount++;
        }
    }

    cout << endl;
    cout << "Active delivery orders before sorting:" << endl;
    displayDelivery(deliveryView, deliveryCount);

    // Sort the temporary view using Quicksort.
    quickSortDelivery(deliveryView, 0, deliveryCount - 1);

    cout << endl;
    cout << "Active delivery orders after sorting:" << endl;
    displayDelivery(deliveryView, deliveryCount);

    // Verify that the original array did not change.
    cout << endl;
    cout << "Original order records after sorting:" << endl;
    displayOrders(orders, CAPACITY);

    // Search for an active delivery order by ID.
    int target;

    cout << endl;
    cout << "Enter an order ID: ";

    if (!(cin >> target))
    {
        cout << "Invalid order ID." << endl;
        return 1;
    }

    int position = linearFindDelivery(deliveryView, deliveryCount, target);

    if (position == -1)
    {
        cout << "Active delivery order not found." << endl;
    }
    else
    {
        cout << "Found order " << deliveryView[position]->orderId
             << " | Building: " << deliveryView[position]->building
             << " | Priority: " << deliveryView[position]->priority
             << endl;
    }

    return 0;
}

// Display all original order records.
void displayOrders(const Order orders[], int count)
{
    for (int index = 0; index < count; index++)
    {
        cout << "Order ID: " << orders[index].orderId
             << " | Type: " << orders[index].orderType
             << " | Status: " << orders[index].status
             << " | Building: " << orders[index].building
             << " | Priority: " << orders[index].priority
             << endl;
    }
}

// Display the temporary delivery view.
void displayDelivery(Order *view[], int count)
{
    for (int index = 0; index < count; index++)
    {
        cout << "View index: " << index
             << " | Order ID: " << view[index]->orderId
             << " | Building: " << view[index]->building
             << " | Priority: " << view[index]->priority
             << endl;
    }
}

// Check if an order is an active delivery.
bool isActiveDelivery(const Order& order)
{
    return order.orderType == "DELIVERY" &&
           (order.status == "PENDING" ||
            order.status == "IN_PROGRESS");
}

// Compare orders using the delivery report criteria.
bool comesBefore(const Order *left, const Order *right)
{
    // First: Building in alphabetical order.
    if (left->building != right->building)
    {
        return left->building < right->building;
    }

    // Second: Highest priority first.
    if (left->priority != right->priority)
    {
        return left->priority > right->priority;
    }

    // Third: Lowest order ID first.
    return left->orderId < right->orderId;
}

// Exchange borrowed pointers without changing original orders.
void swapOrderPointers(Order *&left, Order *&right)
{
    Order *temporary = left;
    left = right;
    right = temporary;
}

// Partition the delivery view using the central record.
int partitionDelivery(Order *view[], int first, int last)
{
    int middle = first + (last - first) / 2;

    swapOrderPointers(view[first], view[middle]);

    Order *pivot = view[first];
    int boundary = first;

    for (int scan = first + 1; scan <= last; scan++)
    {
        if (comesBefore(view[scan], pivot))
        {
            boundary++;
            swapOrderPointers(view[boundary], view[scan]);
        }
    }

    swapOrderPointers(view[first], view[boundary]);

    return boundary;
}

// Sort the temporary delivery view using Quicksort.
void quickSortDelivery(Order *view[], int first, int last)
{
    if (first >= last)
    {
        return;
    }

    int pivotIndex = partitionDelivery(view, first, last);

    quickSortDelivery(view, first, pivotIndex - 1);
    quickSortDelivery(view, pivotIndex + 1, last);
}

// Search by order ID using linear search.
int linearFindDelivery(Order *view[], int count, int target)
{
    for (int index = 0; index < count; index++)
    {
        if (view[index]->orderId == target)
        {
            return index;
        }
    }

    return -1;
}
