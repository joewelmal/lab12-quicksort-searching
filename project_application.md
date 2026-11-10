
# Lab 12 - Project Application

Course: COEN 2220 - Programming 2

Name: Joewel Maldonado

Project: Campus Cafeteria Order Management

## E1 - Project Connection

My final project is Campus Cafeteria Order Management.

The program manages cafeteria orders, including delivery orders.

In this lab, I used Quicksort to organize active delivery orders
and linear search to find an order by its ID.

This makes it easier to display and search delivery information.

## E2 - Temporary View

The temporary view contains only active DELIVERY orders.

An active delivery order has the status PENDING or IN_PROGRESS.

The program uses an array of pointers to reference the original
orders instead of copying the records.

Orders that are DINE_IN or COMPLETED are not included in the view.

## E3 - Sorting Criteria

The delivery report is sorted using three fields:

1. Building in alphabetical order.
2. Priority from highest to lowest.
3. Order ID from lowest to highest.

I used Quicksort to sort the pointers in the temporary view.

The sorted delivery order IDs are:

205, 310, 420, 180

The program uses linear search to find an order by ID because
the view is not sorted by order ID alone.

## E4 - Original Data

The original orders remain in their arrival order.

The temporary view contains pointers to the selected orders.

Quicksort changes the positions of the pointers in the view,
but it does not change the original order records.

The program displays the original orders before and after
sorting to verify that their order remains the same.

## Testing

I tested the program using these order IDs:

- 205: Active delivery order found.
- 420: Active delivery order found.
- 650: Not found because it is a DINE_IN order.
- 900: Not found because it is COMPLETED.
- 999: Not found because the order does not exist.

The program also checks for invalid input.

## Conclusion

This practice helped me understand how to use Quicksort
with pointers and how to search a temporary view.

I can apply these concepts to my final cafeteria project
without changing the original order records.
