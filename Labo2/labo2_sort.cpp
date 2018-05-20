#include "labo2_sort.h"


void scambia(vector<int>& v, int i, int j)
{ 
  int tmp = v[j];
  v[j] = v[i];
  v[i] = tmp;
}


/**************************************************************************************
				SELECTION SORT
***************************************************************************************/
void selectionSort(vector<int>& v)
{
   int current_min_index;
   unsigned int size = v.size();
   for (unsigned int i=0; i<size; ++i)
   { 
     current_min_index = i;
     for (unsigned int j=i+1;j<size; ++j)
        if (v[current_min_index] > v[j])
            current_min_index = j;
     scambia(v, i, current_min_index);
   }
}



/**************************************************************************************
				INSERTION SORT
***************************************************************************************/
void insertionSort(vector<int>& v)
{
   int current, prev;
   unsigned int size = v.size();
   for (unsigned int i=1; i<size; ++i)
   { current=i; 
     prev=i-1;
     while(prev>=0 && v[current]<v[prev])
        {
         scambia(v, current, prev);
         --current;
         --prev;
        }
   }
}


/**************************************************************************************
				BUBBLESORT
***************************************************************************************/
void bubbleSort(vector<int>& v)
{
   unsigned int size = v.size();
   bool scambiati;
   for (unsigned int i=1; i<size; ++i)
      {
      scambiati = false;
      for (unsigned int j=0; j<size-i; ++j)
          if(v[j]>v[j+1])
            { 
              scambia(v, j, j+1);
              scambiati = true;
            }
      if (!scambiati) return;
      }
}



/**************************************************************************************
				   MERGESORT
***************************************************************************************/
void fondi(vector<int>& v, unsigned int inizio, unsigned int centro, unsigned int fine)
{
   vector<int> vsinistra, vdestra;

   for (unsigned int i=inizio; i<=centro; ++i)
      vsinistra.push_back(v[i]);

   for (unsigned int i=centro+1; i<=fine; ++i)
      vdestra.push_back(v[i]);

   unsigned int indicesinistra = 0;
   unsigned int maxsin = vsinistra.size();
   unsigned int indicedestra = 0;
   unsigned int maxdes = vdestra.size();
   
   for (unsigned int i=inizio; i<=fine; ++i)
   {
      if (indicesinistra < maxsin && indicedestra < maxdes)
         {
         if (vsinistra[indicesinistra]<vdestra[indicedestra])
            {
             v[i] = vsinistra[indicesinistra];
             indicesinistra++; continue;
             }
         else
            { 
            v[i] = vdestra[indicedestra];
            indicedestra++; continue;
            }
         } 
      
      if (indicesinistra == maxsin && indicedestra < maxdes)
         { 
            v[i] = vdestra[indicedestra];
            indicedestra++; continue;
         }

       if (indicedestra == maxdes && indicesinistra < maxsin)
         { 
            v[i] = vsinistra[indicesinistra];
            indicesinistra++; continue;
         }         
   } 
}

void ms(vector<int>& v, unsigned int inizio, unsigned int fine)
{
    if (inizio < fine)
      {
          unsigned int centro = (inizio+fine)/2;
          ms(v, inizio, centro);
          ms(v, centro+1, fine);
          fondi(v, inizio, centro, fine);
      }
}


void mergeSort(vector<int>& v)
{
   if (v.size() != 0)
      ms(v, 0, v.size()-1);
}


/**************************************************************************************
				QUICKSORT CON SCELTA "BANALE" DEL PIVOT
***************************************************************************************/

int triv_partition(vector<int>& v, int first, int last){
  int pivot = v[first];
  int i = first+1;
  for(int j = first+1; j < last; j++){
    if(v[j] <= pivot){
      scambia(v, i, j);
      i++;
    }
  }
  scambia(v, first, i-1);
  return i;
}

void qs(vector<int>& v, int first, int last){
  if(first != last){
    int pivot = triv_partition(v, first, last);
    qs(v, first, pivot-1);
    qs(v, pivot, last);

  }
}

void quickSortTrivial(vector<int>& v)
{
  qs(v, 0, v.size());
}




/**************************************************************************************
				QUICKSORT RANDOMIZZATO
***************************************************************************************/

int rand_partition(vector<int>& v, int first, int last){
  int index = first + (rand() % (last - first));
  scambia(v, index, first);
  int pivot = v[first];
  int i = first+1;
  for(int j = first+1; j < last; j++){
    if(v[j] <= pivot){
      scambia(v, i, j);
      i++;
    }
  }
  scambia(v, first, i-1);
  return i;
}

void rand_qs(vector<int>& v, int first, int last){
  if(first != last){
    int pivot = rand_partition(v, first, last);
    rand_qs(v, first, pivot-1);
    rand_qs(v, pivot, last);
  }
}

void quickSortRandom(vector<int>& v)
{
  srand(time(NULL));
  rand_qs(v,0,v.size());
}
