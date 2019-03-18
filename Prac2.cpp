//==============================================================================
// Copyright (C) John-Philip Taylor
// tyljoh010@myuct.ac.za
//
// This file is part of the EEE4084F Course
//
// This file is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>
//==============================================================================

#include "Prac2.h"
using namespace std;
//------------------------------------------------------------------------------

int main(int argc, char** argv){

   int j;
   for(int repeat = 1; repeat <4; repeat ++){

      cout<<"Repeat :"<<repeat<<endl;

      char* images[] = {"Data/fly.jpg", "Data/small.jpg", "Data/greatwall.jpg"};

      for(int i = 0; i<3; i++){

         // Read the input image
         if(!Input.Read(images[i])){
         printf("Cannot read image\n");
         return -1;
         }

         // Allocated RAM for the output image
         if(!Output.Allocate(Input.Width, Input.Height, Input.Components)) return -2;

         // run sequential test -- golden measure.
         sequential_test();


         //16 threads
         multithreaded_test(16);

         //32 threads
         multithreaded_test(32);

         //64 threads
         multithreaded_test(64);

         //128 threads
         multithreaded_test(128);

         //256 threads
         multithreaded_test(256);

         //512 threads
         multithreaded_test(512);

         //1024 threads
         multithreaded_test(1024);

         //16 threads, random allocation
         multithreaded_test(16, "random");

      }
   }

   // Write output image. Doesn't matter which test was run last

   if(!Output.Write("Data/Output.jpg")){
      printf("Cannot write image\n");
      return -3;
   }
   
   return 0;
}

#pragma region Sequential Test
/* This runs the sequential version of a 9x9 median filter*/ 
void sequential_test(){

   tic();
   int x, y;
   string sorting_algorithm = "bubble_sort";

   //    0- Red | 1- Green | 2- Blue
   int rgbIndices [3] = {0,1,2};

   //for each component
   for (int i = 0 ;i < sizeof(rgbIndices)/sizeof(int); i++){

      int component = rgbIndices[i];

      //for each row in the image
      for (int rowNo = 0; rowNo < Input.Height-9; rowNo++){
         
         //for each column in the image 
         for (int col = component ; col < Input.Width*3 -27; col+=3){
               //fill buffer
               int index  = 0;
               int buffer[81];
               
            //for row each row in the pixel   
            for(y = rowNo; y < rowNo+9; y++){
               
               //for each column in 9 pixels
               for(x = col; x < col+27 ; x+=3){

                  buffer[index] = Input.Rows[y][x];
                  index++;
               
               }
               
            }

            int median = calculate_median(&buffer[0],sorting_algorithm);
            
            //write output
            for(y = rowNo; y < rowNo+9; y++){
               for(x = col; x < col+27 ; x+=3){

                  Output.Rows[y][x] = median; 

               }
            }
            
         }
      }


   }
   cout<<"Time taken for golden measure test: "<<(double)toc()/1e-3<< endl;
   return;
}
#pragma endregion Sequential Test

#pragma region Random Partitioning Test
void* Thread_Random(void* id){

   tic();
   int x, y;
   int thread_id = *((int*)id);
   string sorting_algorithm = "quick_sort";

   //    0- Red | 1- Green | 2- Blue
   int rgbIndices [3] = {0,1,2};

   //Amount of work done by a thread - start,stop and work(range of rows)
   int thread_work = Input.Height/Thread_Count;
   int row_stop = 0; 
   int row_start = 0;
   
   //allocate data according to the ID of the thread
   
   //take row 3
   if (thread_id == 1){
      row_stop = thread_id*thread_work*3;
      row_start = row_stop-thread_work;

   //take row 6
   }else if(thread_id == 2){
      row_stop = thread_id*thread_work*6;
      row_start = row_stop-thread_work;

   //take row 10
   }else if(thread_id == 3){
      row_stop = thread_id*thread_work*10;
      row_start = row_stop-thread_work;

   //take row 13
   }else if(thread_id == 4){
      row_stop = thread_id*thread_work*13;
      row_start = row_stop-thread_work;

   //take row 1
   }else if(thread_id == 5){
      row_stop = thread_id*thread_work;
      row_start = row_stop-thread_work;

   //take row 15
   }else if(thread_id == 6){
      row_stop = thread_id*thread_work*15;
      row_start = row_stop-thread_work;

   //take row 11
   }else if(thread_id ==7){
      row_stop = thread_id*thread_work*11;
      row_start = row_stop-thread_work;

   //take row 4
   }else if(thread_id ==8){
      row_stop = thread_id*thread_work*4;
      row_start = row_stop-thread_work;
   
   //take row 7
   }else if(thread_id ==9){
      row_stop = thread_id*thread_work*7;
      row_start = row_stop-thread_work;

   //take row 14
   }else if(thread_id ==10){
      row_stop = thread_id*thread_work*14;
      row_start = row_stop-thread_work;
   
   //take row 12
   }else if(thread_id ==11){
      row_stop = thread_id*thread_work*12;
      row_start = row_stop-thread_work;

   //take row 9
   }else if(thread_id ==12){
      row_stop = thread_id*thread_work*9;
      row_start = row_stop-thread_work;

   //take row 1
   }else if(thread_id ==13){
      row_stop = thread_id*thread_work*2;
      row_start = row_stop-thread_work;

   //take row 5
   }else if(thread_id ==14){
      row_stop = thread_id*thread_work*5;
      row_start = row_stop-thread_work;

   //take row 16
   }else if(thread_id ==15){
      row_stop = thread_id*thread_work*16;
      row_start = row_stop-thread_work;

   //take row 8
   }else if(thread_id ==16 ){
      row_stop = thread_id*thread_work*8;
      row_start = row_stop-thread_work;
   
   //invalid thread id
   }else{
      cerr<<"Thread could not be allocated work to carry out"<<endl;
   }
   
   //start processing. . .

   //for each component
   for (int i = 0 ;i < sizeof(rgbIndices)/sizeof(int); i++){

      int component = rgbIndices[i];

      //for each row in the image
      for (int rowNo = row_start; rowNo < row_stop+1-9; rowNo++){
         
         //for each column in the image 
         for (int col = component ; col < Input.Width*3 -27; col+=3){
               //fill buffer
               int index  = 0;
               int buffer[81];
               
            //for row each row in the pixel   
            for(y = rowNo; y < rowNo+9; y++){
               
               //for each column in 9 pixels
               for(x = col; x < col+27 ; x+=3){

                  buffer[index] = Input.Rows[y][x];
                  index++;
               
               }
               
            }

            int median = calculate_median(&buffer[0],sorting_algorithm);
            
            //write output
            for(y = rowNo; y < rowNo+9; y++){
               for(x = col; x < col+27 ; x+=3){

                  Output.Rows[y][x] = median; 

               }
            }
            
         }
      }
   }
   //DEBUG - print thread status.

   // pthread_mutex_lock(&Mutex);
   // cout<<"Thread "<<thread_id<<" ended."<<endl;
   // pthread_mutex_unlock(&Mutex);
   return 0;
}
#pragma endregion Random Partitioning Test

#pragma region Thread Main

void* Thread_Main(void* id){

   tic();
   string sorting_algorithm = "quick_sort";

   // 1 -> n , n - number of threads
   int thread_id = *((int*)id);

   //Amount of work done by a thread - start,stop and work(range of rows)
   int thread_work = Input.Height/Thread_Count;
   int row_stop = thread_id*thread_work; 
   int row_start = row_stop-thread_work;

   int x, y;

   //DEBUG - print thread status.

   // pthread_mutex_lock(&Mutex);
   // cout<<"Starting Thread "<<thread_id<<endl;
   // pthread_mutex_unlock(&Mutex);

   //    0- Red | 1- Green | 2- Blue
   int rgbIndices [3] = {0,1,2};

   //for each component
   for (int i = 0 ;i < sizeof(rgbIndices)/sizeof(int); i++){

      int component = rgbIndices[i];

      //for each row in the image
      for (int rowNo = row_start; rowNo < row_stop+1-9; rowNo++){
         
         //for each column in the image 
         for (int col = component ; col < Input.Width*3 -27; col+=3){
               //fill buffer
               int index  = 0;
               int buffer[81];
               
            //for row each row in the pixel   
            for(y = rowNo; y < rowNo+9; y++){
               
               //for each column in 9 pixels
               for(x = col; x < col+27 ; x+=3){

                  buffer[index] = Input.Rows[y][x];
                  index++;
               
               }
               
            }

            int median = calculate_median(&buffer[0],sorting_algorithm);
            
            //write output
            for(y = rowNo; y < rowNo+9; y++){
               for(x = col; x < col+27 ; x+=3){

                  Output.Rows[y][x] = median; 

               }
            }
            
         }
      }
   }
   //DEBUG - print thread status.

   // pthread_mutex_lock(&Mutex);
   // cout<<"Thread "<<thread_id<<" ended."<<endl;
   // pthread_mutex_unlock(&Mutex);
   return 0;

}
#pragma endregion Thread Main

#pragma region Multithreaded Test
/* This runs the multithreaded version of a 9x9 median filter*/

void multithreaded_test(int thread_count, std::string test){

   Thread_Count = thread_count;

   if (test == "ordered"){
      
      //initialise threads
      pthread_mutex_init(&Mutex, 0);

      // Structure to keep the thread ID
      int       Thread_ID[Thread_Count]; 

      //Pool of threads
      pthread_t Thread   [Thread_Count]; 

      //start time
      tic();

      //create threads and start threads
      for(int j =0 ; j < Thread_Count; j++){
         Thread_ID[j] = j+1;
         pthread_create(Thread+j, 0, Thread_Main, Thread_ID+j);
      }

      // Wait for threads to finish
      for(int j = 0; j < Thread_Count; j++){
         if(pthread_join(Thread[j], 0)){
            pthread_mutex_lock(&Mutex);
            printf("Problem joining thread %d\n", j);
            pthread_mutex_unlock(&Mutex);
         }
      }

      // No more active threads, so no more critical sections required
      cout<<"Time taken for "<<Thread_Count<<" threads to run = "<<toc()/1e-3<<"ms"<<endl;

      // Clean-up
      pthread_mutex_destroy(&Mutex);

   }else if(test =="random"){
      
      random_partition_test();
   }  

}
#pragma endregion Multithreaded Test

#pragma region Random Partition Test

/* Partition data randomly for 16 threads*/
void random_partition_test(){

   // Structure to keep the thread ID
   int       Thread_ID[16]; 

   //Pool of threads
   pthread_t Thread   [16]; 

   //start time
   tic();

   //create threads and start threads
   for(int j =0 ; j < 16; j++){
      Thread_ID[j] = j+1;
      pthread_create(Thread+j, 0, Thread_Random, Thread_ID);
   }

   // Wait for threads to finish
   for(int j = 0; j < Thread_Count; j++){
      if(pthread_join(Thread[j], 0)){
         pthread_mutex_lock(&Mutex);
         printf("Problem joining thread %d\n", j);
         pthread_mutex_unlock(&Mutex);
      }
   }
   // No more active threads, so no more critical sections required
   cout<<"Time taken for "<<Thread_Count<<" threads to run = "<<toc()/1e-3<<"ms"<<endl;

   // Clean-up
   pthread_mutex_destroy(&Mutex);
}
#pragma endregion Random Partition Test

#pragma region BubbleSort
void bubble_sort(int* a){

   bool swapp = true;
   while(swapp){
      swapp = false;
      for (size_t i = 0; i < 80; i++) {
         if (a[i]>a[i+1] ){
               a[i] += a[i+1];
               a[i+1] = a[i] - a[i+1];
               a[i] -=a[i+1];
               swapp = true;
         }
      }
   }
}
#pragma endregion Bubblesort

#pragma region Calculate Median
/* calculates the Median for a length-81 buffer*/
int calculate_median(int* buffer, std::string sorting_algorithm){

  if (sorting_algorithm == "bubble_sort"){
     bubble_sort(buffer);

  }else if(sorting_algorithm == "quick_sort"){
     quick_sort(buffer,0,80);

  }else{
     cerr<<"No valid sorting algorithm selcted"<<endl;
  }
   

   int n = 81;
   // find median 
   if (n % 2 != 0) 
      return buffer[n/2]; 

   return (buffer[(n-1)/2] + buffer[n/2])/2; 
}
#pragma endregion CalculateMedian

#pragma region Swap
// A utility function to swap two elements 
void swap(int* a, int* b) 
{ 
    int t = *a; 
    *a = *b; 
    *b = t; 
} 
#pragma endregion Swap

#pragma region Partition
/* This function takes last element as pivot, places 
   the pivot element at its correct position in sorted 
    array, and places all smaller (smaller than pivot) 
   to left of pivot and all greater elements to right 
   of pivot */
int partition (int arr[], int low, int high) 
{ 
    int pivot = arr[high];    // pivot 
    int i = (low - 1);  // Index of smaller element 
  
    for (int j = low; j <= high- 1; j++) 
    { 
        // If current element is smaller than or 
        // equal to pivot 
        if (arr[j] <= pivot) 
        { 
            i++;    // increment index of smaller element 
            swap(&arr[i], &arr[j]); 
        } 
    } 
    swap(&arr[i + 1], &arr[high]); 
    return (i + 1); 
} 
#pragma endregion Partition

#pragma region Quick Sort
/* The main function that implements QuickSort 
 arr[] --> Array to be sorted, 
  low  --> Starting index, 
  high  --> Ending index */
void quick_sort(int arr[], int low, int high) 
{ 
    if (low < high) 
    { 
        /* pi is partitioning index, arr[p] is now 
           at right place */
        int pi = partition(arr, low, high); 
  
        // Separately sort elements before 
        // partition and after partition 
        quick_sort(arr, low, pi - 1); 
        quick_sort(arr, pi + 1, high); 
    } 
} 
#pragma endregion Quick Sort

