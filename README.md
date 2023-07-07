# OS Project
# Content
### FIRST: Working Sets and LRU Lists
We have previously defined the working set as the set of all pages loaded in main memory of the program at run 
time which is implemented as a FIXED size array of virtual addresses corresponding to pages that are loaded in main 
memory. LRU lists are active list and second chance list which are linked lists to the elements in the working lists in 
an order according to the APPROXIMATED LRU strategy. So, the total MAX size of both LRU lists with each other 
must not exceed the MAX size of the working set array.

### SECOND: Page File
The page file is an area in the secondary memory (H.D.D.) that is used for saving and loading programs pages during 
runtime. Thus, for each running program, there is a storage space in the page file for ALL pages needed by the 
program, this means that user code, data, stack and heap sections are ALL written in page file. (Remember that not 
all these pages are in main memory, only the working set).

### THIRD: System Calls
1. You will need to implement a dynamic allocation function (and a free function) for your user programs to make runtime allocations (and frees).
2. The loading of ALL program binary segments plus the stack page to the page file is already implemented for you in "env_create()", you will need to maintain the page file in the rest of the project.
3. The initialization of the working set by the set of pages during the program loading is already implemented for you in "env_create()", and you will be responsible for maintaining the working set during the run time of the program.
4. The user should call the kernel to allocate/free memory for it.
5. Remember that the user code is not the kernel (i.e. when a user code is executing, the processor runs user mode (less privileged mode), and to execute kernel code the processor need to go from user mode to kernel mode)
6. The switch from user mode to kernel mode is done by a software interrupt called “System Call”.
7. All you need to do is to call a function prefixed “sys_” from your user code to call the kernel code that does the job, (e.g. from user function malloc(), call sys_allocateMem() which then will call kernel function allocateMem() to allocate memory for the user) as shown in figure
