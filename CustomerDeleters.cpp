#include<memory>
#include<functional>

#include"SharedPtr.hpp"
#include"WeakPtr.hpp"

class Socket 
{ };

void deleter1(Socket* sp)
{
   delete sp;
}

auto deleter2 = [](Socket* sp) { delete sp; };

std::function<void(Socket*)> deleter3 = [](Socket* sp) { delete sp; };

int main()
{
   std::unique_ptr<Socket, void(*)(Socket*)> up1(new Socket, deleter1);
   std::unique_ptr<Socket, decltype(deleter2)> up2(new Socket, deleter2);
   std::unique_ptr<Socket, decltype(deleter3)> up3(new Socket, deleter3);
   auto b = 0;
}

