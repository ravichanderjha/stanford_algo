#include<stdio.h>

#define MAX 100000


long long int mergesort(int arr[], int temp[], int, int);
long long int merge(int arr[], int temp[], int left, int mid, int right);
int main(void)
{
	int array[MAX], temp[MAX],i;
	long long int count = 0;
	for(i =0;i<MAX; i++)
	{
		scanf("%d", &array[i]);
	}
	count = mergesort(array,temp, 0, MAX-1);
	printf("Number of conversion: %lld", count);
	return 0;
}

long long int mergesort(int arr[],int temp[], int left, int right)
{
  int mid;
  long long int inv_count = 0;
  if (right > left)
  {
    /* Divide the array into two parts and call _mergesortAndCountInv()
       for each of the parts */
    mid = (right + left)/2;
  
    /* Inversion count will be sum of inversions in left-part, right-part
      and number of inversions in merging */
    inv_count  = mergesort(arr, temp, left, mid);
    inv_count += mergesort(arr, temp, mid+1, right);
  
    /*Merge the two parts*/
    inv_count += merge(arr, temp, left, mid+1, right);
  }
  return inv_count;
}

long long int merge(int arr[], int temp[], int left, int mid, int right)
{
  int i, j, k;
  long long int inv_count = 0;
  
  i = left; /* i is index for left subarray*/
  j = mid;  /* i is index for right subarray*/
  k = left; /* i is index for resultant merged subarray*/
  while ((i <= mid - 1) && (j <= right))
  {
    if (arr[i] <= arr[j])
    {
      temp[k++] = arr[i++];
    }
    else
    {
      temp[k++] = arr[j++];
  
     /*this is tricky -- see above explanation/diagram for merge()*/
      inv_count = inv_count + (mid - i);
    }
  }
  
  /* Copy the remaining elements of left subarray
   (if there are any) to temp*/
  while (i <= mid - 1)
    temp[k++] = arr[i++];
  
  /* Copy the remaining elements of right subarray
   (if there are any) to temp*/
  while (j <= right)
    temp[k++] = arr[j++];
  
  /*Copy back the merged elements to original array*/
  for (i=left; i <= right; i++)
    arr[i] = temp[i];
  
  return inv_count;
}