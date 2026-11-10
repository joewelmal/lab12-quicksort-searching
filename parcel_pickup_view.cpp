
/*
 * Course: COEN 2220 - Programming 2
 * Name: [Joewel Maldonado]
 * Lab: Lab 12 - Quicksort and Searching
 * Description: Preserve parcel arrival records and search a ready-only view
 * Due date: [10 November 2026]
 */

#include <iostream>
#include <string>
using namespace std;

struct Parcel
{
    int pickupCode; // Unique lookup key supplied by the recipient.
    string locker; // Physical location, not a sorting key.
    bool ready;    // Only ready parcels belong in the lookup view.
};

void displayParcels(const Parcel parcels[], int count);
void displayReady(Parcel *view[], int count);
void swapParcelPointers(Parcel *&left, Parcel *&right);
int partitionReady(Parcel *view[], int first, int last);
void quickSortReady(Parcel *view[], int first, int last);
int binaryFindReady(Parcel *view[], int count, int target);

int main()
{
    const int CAPACITY = 8;
    Parcel parcels[CAPACITY] = {
        {640, "L-4", true},  {215, "L-8", false},
        {580, "L-2", true},  {325, "L-6", true},
        {710, "L-1", true},  {460, "L-5", false},
        {190, "L-3", true},  {505, "L-7", true}
    };

    Parcel *readyView[CAPACITY]; // Borrow addresses; do not delete these objects.
    int readyCount = 0;

    cout << boolalpha << "Original arrival records:" << endl;
    displayParcels(parcels, CAPACITY);

    for (int index = 0; index < CAPACITY; index++)
    {
        if (parcels[index].ready)
        {
            readyView[readyCount] = &parcels[index];
            readyCount++; // Count initialized view positions only.
        }
    }

    quickSortReady(readyView, 0, readyCount - 1);

    cout << "Ready parcels by pickup code:" << endl;
    displayReady(readyView, readyCount);

    cout << "Original arrival records after sorting:" << endl;
    displayParcels(parcels, CAPACITY);

    // --- STEP D1: Activate after completing the search function ---

    int target;
    cout << "Enter a pickup code: ";
    if (!(cin >> target))
    {
        cout << "Invalid code input." << endl;
        return 1;
    }

    int position = binaryFindReady(readyView, readyCount, target);
    if (position == -1)
    {
        cout << "No ready parcel with that code." << endl;
    }
    else
    {
        cout << "Pickup code " << readyView[position]->pickupCode
             << " | Locker: " << readyView[position]->locker << endl;
    }

    return 0;
}

// ===== Resolve only these TODOs now (Part C) =====

void swapParcelPointers(Parcel *&left, Parcel *&right)
{
    // TODO (Part C): Exchange the two borrowed addresses without changing objects.
    Parcel *temporary = left;
    left = right;
    right = temporary;
}

int partitionReady(Parcel *view[], int first, int last)
{
    // TODO (Part C): Select the central record and partition by ascending pickupCode.
    int middle = first + (last - first) / 2;
    swapParcelPointers(view[first], view[middle]);
    int pivotCode = view[first]->pickupCode;

    // TODO (Part C): Follow the lecture's pivot-at-first scheme and return its final index.
    int boundary = first;

    for (int scan = first + 1; scan <= last; scan++)
    {
        if (view[scan]->pickupCode < pivotCode)
        {
            boundary++;
            swapParcelPointers(view[boundary], view[scan]);
        }
    }

    swapParcelPointers(view[first], view[boundary]);
    return boundary;
}

void quickSortReady(Parcel *view[], int first, int last)
{
    // TODO (Part C): Handle base cases and request partitioning and recursive sorting.
    if (first >= last)
    {
        return;
    }

    int pivotIndex = partitionReady(view, first, last);

    quickSortReady(view, first, pivotIndex - 1);
    quickSortReady(view, pivotIndex + 1, last);
}

// ===== Resolve this TODO later (Part D) =====

int binaryFindReady(Parcel *view[], int count, int target)
{
    // TODO (Part D): Implement iterative binary search by pickupCode on the sorted view.
    int first = 0;
    int last = count - 1;

    while (first <= last)
    {
        int middle = first + (last - first) / 2;

        if (view[middle]->pickupCode == target)
        {
            return middle;
        }

        if (view[middle]->pickupCode < target)
        {
            first = middle + 1;
        }
        else
        {
            last = middle - 1;
        }
    }

    return -1; // Code not found in the ready view.
}

void displayParcels(const Parcel parcels[], int count)
{
    for (int index = 0; index < count; index++)
    {
        cout << "Code: " << parcels[index].pickupCode
             << " | Locker: " << parcels[index].locker
             << " | Ready: " << parcels[index].ready << endl;
    }
}

void displayReady(Parcel *view[], int count)
{
    for (int index = 0; index < count; index++)
    {
        cout << "View index: " << index
             << " | Code: " << view[index]->pickupCode
             << " | Locker: " << view[index]->locker << endl;
    }
}

/*
 * Analysis Answers
 *
 * C3 - Partition decisions
 * Trace the first partition of the six-pointer ready view. Record first, last,
 * middle, pivotCode, boundary, scan, and codes before and after each comparison.
 * Include the loop's final false test and the final pivot exchange.
 * Answer:
 * The initial ready view is [640, 580, 325, 710, 190, 505].
 * first = 0, last = 5, middle = 2, and pivotCode = 325.
 * The middle pointer is swapped with the first pointer.
 * The view becomes [325, 580, 640, 710, 190, 505].
 * boundary starts at 0.
 *
 * scan = 1: 580 < 325 is false. boundary = 0.
 * View: [325, 580, 640, 710, 190, 505].
 * scan = 2: 640 < 325 is false. boundary = 0.
 * View: [325, 580, 640, 710, 190, 505].
 * scan = 3: 710 < 325 is false. boundary = 0.
 * View: [325, 580, 640, 710, 190, 505].
 * scan = 4: 190 < 325 is true. boundary becomes 1.
 * Swap positions 1 and 4.
 * View: [325, 190, 640, 710, 580, 505].
 * scan = 5: 505 < 325 is false. boundary = 1.
 * View: [325, 190, 640, 710, 580, 505].
 *
 * The final loop test is scan = 6, and 6 <= 5 is false.
 * Finally, positions 0 and 1 are swapped.
 * View: [190, 325, 640, 710, 580, 505].
 * The function returns boundary = 1.
 *
 * C4 - Data and memory
 * Explain what changes when swapping two Parcel pointers by reference.
 * Identify who owns the objects and why the view must not delete them.
 * Answer:
 * Swapping two Parcel pointers changes the addresses stored
 * in the readyView array, not the original Parcel objects.
 * The original parcels array owns the objects.
 * The readyView array only stores borrowed pointers to them.
 * The view must not delete these pointers because the
 * objects were not created with new.
 * Sorting the pointers does not change the arrival order
 * or the information stored in the original parcels array.
 *
 * D3 - Search positions and absence
 * Trace code 505 and the absent ready-view code 460. Give the checked ranges
 * and explain why a view index cannot be used as an index into parcels.
 * Answer:
 * The sorted ready view is [190, 325, 505, 580, 640, 710].
 *
 * Searching for code 505:
 * first = 0, last = 5, middle = 2, code = 505.
 * The target is found at view index 2.
 *
 * Searching for code 460:
 * First check: first = 0, last = 5, middle = 2, code = 505.
 * Since 460 is smaller, the next range is 0 to 1.
 *
 * Second check: first = 0, last = 1, middle = 0, code = 190.
 * Since 460 is greater, the next range is 1 to 1.
 *
 * Third check: first = 1, last = 1, middle = 1, code = 325.
 * Since 460 is greater, the next range is 2 to 1.
 *
 * The range is empty, so the function returns -1.
 * Code 460 exists in the original array but is not ready.
 * Therefore, it is not included in readyView.
 *
 * A view index cannot be used directly as an index into parcels
 * because the view contains only ready parcels and is sorted
 * independently of the original arrival order.
 *
 * D4 - Time and auxiliary space
 * For n ready parcels and q queries, compare sorting once then using binary
 * search with scanning the unsorted ready view for every query. Give worst-case
 * bounds for this quicksort, balanced-partition bounds, and iterative-search
 * auxiliary space. Distinguish the view storage from recursive-call storage.
 * Answer:
 * Sorting once and using binary search for q queries takes
 * O(n log n + q log n) time with balanced partitions.
 *
 * In the worst case, quicksort takes O(n^2) time,
 * making the total O(n^2 + q log n).
 *
 * Scanning the unsorted ready view for every query takes
 * O(qn) time in the worst case.
 *
 * The readyView array uses O(n) space for borrowed pointers.
 * Quicksort uses O(log n) recursive-call space with balanced
 * partitions and O(n) in the worst case.
 *
 * Iterative binary search uses O(1) auxiliary space
 * because it does not create recursive calls.
 */
