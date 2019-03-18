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

#ifndef Prac2_h
#define Prac2_h
//------------------------------------------------------------------------------

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <vector>
#include <iostream>
#include <string.h>
//------------------------------------------------------------------------------

#include "JPEG.h"
#include "Timer.h"
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------

// Input and output buffers
JPEG Input;
JPEG Output;
int Thread_Count = 16;   //not constant, changed depending on experiment.
//------------------------------------------------------------------------------

pthread_mutex_t Mutex; // General-purpose MutEx
//------------------------------------------------------------------------------

// The thread "main" function.  Receives a unique thread ID as parameter
void* Thread_Main(void* Parameter);
void sequential_test();
void bubble_sort(int* arr);
void quick_sort(int arr[], int low, int high);
int partition (int arr[], int low, int high);
void swap(int* a, int* b);
void multithreaded_test(int thread_count,std::string test = "ordered");
void random_partition_test();
int calculate_median(int* colorValues, std::string sorting_algorithm);
//------------------------------------------------------------------------------

#endif
//------------------------------------------------------------------------------
