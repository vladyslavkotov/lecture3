#include <memory>
#include <windows.h>
#include <stdexcept>

class CreateFileGuard
{
   HANDLE handle;
public:
   CreateFileGuard(const wchar_t* fileName, DWORD desiredAccess, DWORD shareMode, DWORD creationDisposition, DWORD flagsAndAttributes, LPSECURITY_ATTRIBUTES lpSecurityAttributes = nullptr, HANDLE templateFile = nullptr)
      : handle(CreateFile(fileName, desiredAccess, shareMode, lpSecurityAttributes, creationDisposition, flagsAndAttributes, templateFile))
   {
      if (handle == INVALID_HANDLE_VALUE)
      {
         throw std::runtime_error("File cannot be opened/created");
      }
   }

   ~CreateFileGuard()
   {
      if (handle != INVALID_HANDLE_VALUE)
      {
         CloseHandle(handle);
      }
   }

   HANDLE get()
   {
      return handle;
   }
};