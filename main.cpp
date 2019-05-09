#include <llvm-3.8/llvm/Support/ThreadPool.h>
#include <future>
#include <functional>
#include <string>
#include <iostream>
#include <cstring>

void processData(char *data, int len, void *opa)
{
    std::cout << data << "---- len: " << len << std::endl;
}

void getData(std::string name, void (*cb)(char *data, int len, void * opa) )
{
    std::string str("Hello ");
    str.append(name);
    char * data = new char[64];
    memset(data, 0, 64);
    strcpy(data, str.c_str());
    cb(data,  str.size() , nullptr);
}

template<typename F, typename ...Args>
auto getDataT(std::string name, F &&f, Args &&... ArgList) ->decltype(f)
{
f(ArgList);
}

struct FOO
{
    FOO(int n) : thPool(n)
    {
    }

    void threadwork()
    {
        int a = 1;
        int b = 2;
        //std::packaged_task<void()> task(std::bind(&FOO::sum, this, a, b));
        //auto res = thPool.async(std::move(task));
        auto res = thPool.async([=]() {
            return sum(a, b);
        });

    }

    void threadwork1()
    {
    //   auto f = [=](char *data, int len, void * opa)
    //   {
    //        process(data, len, opa);
    //   };

    //   getData("jack", &f);
      //thPool.async(f);

    }

    
    void process(char *data, int len, void * opa)
    {
        std::cout <<__FUNCTION__ <<" : " <<data << "---- len: " << len << std::endl;
    }

    int sum(int a, int b)
    {
        return a + b;
    }

    llvm::ThreadPool thPool;
};

int main(int argc, char const *argv[])
{
    /* code */
    FOO foo(4);
    foo.threadwork();

    getData("robbie", processData);

    foo.threadwork1();

    auto f = [&foo](char *data, int len, void *opa) {
        foo.process(data, len, opa);
    };

    //getData("jack", &f);

    getDataT("lucy", processData, )

    return 0;
}
