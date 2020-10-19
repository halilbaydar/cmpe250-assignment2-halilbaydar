/*
Student Name:Halil BAYDAR
Student Number:2017400297
Project Number: 2
Compile Status: [SUCCESS/FAIL]
Running Status: [SUCCESS/FAIL]
Notes: Anything you want to say about your code that will be helpful in the grading process.
*/
#include "RestaurantOrganizer.h"


using namespace std;
RestaurantOrganizer::RestaurantOrganizer(const vector<int>& tableCapacityInput){
    numberOfTables = tableCapacityInput.size();
    for(int i=0;i<numberOfTables;i++){
        tableCapacity[i] = tableCapacityInput[i];
        heap[i] = i;
        heapUp(i);
    }
}

void RestaurantOrganizer::addNewGroup(int groupSize, ofstream& outFile){
    // IMPLEMENT ME!
    if(tableCapacity[heap[0]]>=groupSize)
    {
        tableCapacity[heap[0]]-=groupSize;
        outFile<<heap[0]<<endl;
        heapDown(0);
    } else
    {
        outFile<<-1<<endl;
    }
}

void RestaurantOrganizer::heapUp(int index){
    // IMPLEMENT ME!
    int parent;
    if(index==0)
        return;
    parent = (index-1)/2;
    if(tableCapacity[heap[parent]]<tableCapacity[heap[index]])
    {
        swap(heap[index],heap[parent]);
        heapUp(parent);
    }
    else if(tableCapacity[heap[parent]]==tableCapacity[heap[index]])
    {
        if(heap[parent]>heap[index])
        {
            swap(heap[parent],heap[index]);
            heapUp(parent);
        }
    }
}
bool compare(RestaurantOrganizer* me, int x, int y)
{
    return (me->tableCapacity[me->heap[x]] < me->tableCapacity[me->heap[y]] || (me->tableCapacity[me->heap[x]] == me->tableCapacity[me->heap[y]] && me->heap[x] > me->heap[y]));
    //gives true ify>x
}
void RestaurantOrganizer::heapDown(int index) {
    // IMPLEMENT ME!
    int left = index * 2 + 1;
    int right = index * 2 + 2;

    if (left >= numberOfTables)
        return;

    if(left==numberOfTables-1)
        if(compare(this,index, left))
        {
            swap(heap[left] , heap[index]);
            return;
        }

    if (compare(this,index, left) && compare(this, index,right)) {
        if (compare(this,left, right)) {
            swap(heap[right] , heap[index]);
            heapDown(right);
        } else{
            swap(heap[left] , heap[index]);
            heapDown(left);
        }
    }
    else if(compare(this,index,right) )
    {
        swap(heap[right] , heap[index]);
        heapDown(right);
    }
    else if(compare(this, index, left)) {
        swap(heap[left] , heap[index]);
        heapDown(left);
    }
}
void RestaurantOrganizer::printSorted(ofstream& outFile){
    for(int i=0; i<numberOfTables; i++) {
        if(i+1==numberOfTables)
            outFile<<tableCapacity[heap[0]];
        else{
            outFile<<tableCapacity[heap[0]]<<" ";
            tableCapacity[heap[0]]=-10;
            heapDown(0);
        }

    }
}

// YOU CAN ADD YOUR HELPER FUNCTIONS