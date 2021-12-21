#include <inc/lib.h>

// malloc()
//	This function use FIRST FIT strategy to allocate space in heap
//  with the given size and return void pointer to the start of the allocated space

//	To do this, we need to switch to the kernel, allocate the required space
//	in Page File then switch back to the user again.
//
//	We can use sys_allocateMem(uint32 virtual_address, uint32 size); which
//		switches to the kernel mode, calls allocateMem(struct Env* e, uint32 virtual_address, uint32 size) in
//		"memory_manager.c", then switch back to the user mode here
//	the allocateMem function is empty, make sure to implement it.

//==================================================================================//
//============================ REQUIRED FUNCTIONS ==================================//
//==================================================================================//
int NumberOfHeapPages = (USER_HEAP_MAX - USER_HEAP_START)/PAGE_SIZE;
int HeapChunks[(USER_HEAP_MAX - USER_HEAP_START)/PAGE_SIZE];

void* malloc(uint32 size)
{
	//TODO: [PROJECT 2021 - [2] User Heap] malloc() [User Side]
	// Write your code here, remove the panic and write your code
	//panic("malloc() is not implemented yet...!!");

	int MinimumSize = 1000000;
	int AddressIndex = -1;
	int ContinuousPageCounter = 0;
	size =ROUNDUP(size,PAGE_SIZE);
	int NumberOfAllocatedPages = size/PAGE_SIZE;

	for(int i=0;i<NumberOfHeapPages;++i)
	{
		if(HeapChunks[i] != 0)
		{
			if(ContinuousPageCounter != 0)
			{
				if(ContinuousPageCounter >= NumberOfAllocatedPages && ContinuousPageCounter < MinimumSize)
				{
					MinimumSize = ContinuousPageCounter;
					AddressIndex = i - ContinuousPageCounter;
				}
				ContinuousPageCounter = 0;
			}
			i += HeapChunks[i]-1;
		}

		else
			++ContinuousPageCounter;
	}


	if(ContinuousPageCounter != 0)
	{
		if(ContinuousPageCounter >= NumberOfAllocatedPages && ContinuousPageCounter < MinimumSize)
		{
			MinimumSize = ContinuousPageCounter;
			AddressIndex = NumberOfHeapPages - ContinuousPageCounter;

		}
	}
	if(AddressIndex != -1)
	{
		int Address = USER_HEAP_START + (AddressIndex*PAGE_SIZE);
		HeapChunks[AddressIndex] = NumberOfAllocatedPages;
		sys_allocateMem(Address, size);
		return (void*)Address;
	}
	//This function should find the space of the required range
	//using the BEST FIT strategy
	//refer to the project presentation and documentation for details
	return NULL;

}


// free():
//	This function frees the allocation of the given virtual_address
//	To do this, we need to switch to the kernel, free the pages AND "EMPTY" PAGE TABLES
//	from page file and main memory then switch back to the user again.
//
//	We can use sys_freeMem(uint32 virtual_address, uint32 size); which
//		switches to the kernel mode, calls freeMem(struct Env* e, uint32 virtual_address, uint32 size) in
//		"memory_manager.c", then switch back to the user mode here
//	the freeMem function is empty, make sure to implement it.

void free(void* virtual_address)
{
	//TODO: [PROJECT 2021 - [2] User Heap] free() [User Side]
	// Write your code here, remove the panic and write your code
	//panic("free() is not implemented yet...!!");

	sys_freeMem((uint32)virtual_address,(uint32)HeapChunks[((uint32)virtual_address-USER_HEAP_START)/PAGE_SIZE]*PAGE_SIZE);

	HeapChunks[(((int)virtual_address)-USER_HEAP_START)/PAGE_SIZE] = 0;

	//you should get the size of the given allocation using its address
	//refer to the project presentation and documentation for details
}

//==================================================================================//
//================================ OTHER FUNCTIONS =================================//
//==================================================================================//

void* smalloc(char *sharedVarName, uint32 size, uint8 isWritable)
{
	panic("this function is not required...!!");
	return 0;
}

void* sget(int32 ownerEnvID, char *sharedVarName)
{
	panic("this function is not required...!!");
	return 0;
}

void sfree(void* virtual_address)
{
	panic("this function is not required...!!");
}

void *realloc(void *virtual_address, uint32 new_size)
{
	panic("this function is not required...!!");
	return 0;
}

void expand(uint32 newSize)
{
	panic("this function is not required...!!");
}
void shrink(uint32 newSize)
{
	panic("this function is not required...!!");
}

void freeHeap(void* virtual_address)
{
	panic("this function is not required...!!");
}
