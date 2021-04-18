#include <windows.h>
#include <stdio.h>
DWORD Sum;  /* data is shared by the thread(s) */
/* the thread runs in this separate function */
DWORD WINAPI Summation(LPVOID Param)
{
   DWORD Upper = *(DWORD*)Param;
   for (DWORD i = 0; i <= Upper; i++)
      Sum += i;
   return 0;
}

int main(int argc, char * argv[])
{
   DWORD ThreadId;
   HANDLE ThreadHandle;
   int Param;
   /* perform some basic error checking */
   if (argc != 2) {
      fprintf(stderr, “An integer parameter is required\n”);
      return -1;
   }
   Param = atoi(argv[1];
   // create the thread
   ThreadHandle = CreateThread(
      NULL,        // default security attributes
      0,           // default stack size
      Summation,   // thread function
      &Param,      // parameter to thread function
      0,           // default creation flags
      &ThreadId);  // returns the thread identifier

   if (ThreadHandle != NULL) {
      // now wait for the thread to finish
      WaitForSingleObject(ThreadHandle, INFINITE);

      // close the thread handle
      CloseHandle(ThreadHandle);

      printf(“Sum = %d\n”, Sum);
   }
}
