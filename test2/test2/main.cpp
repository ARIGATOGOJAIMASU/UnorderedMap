//
//  main.cpp
//  test2
//
//  Created by CD-a8389742a on 2023/04/17.
//

#include <iostream>
#include "Node.hpp"
#include "Un_order_map.hpp"

#include <unordered_map>
#include <sstream>


int main(int argc, const char * argv[]) {
    
//    std::unordered_map<int, int> test;
//
//    int size = 0;
//
//
//    int i = test.bucket_count();
//    int k = test.max_bucket_count();
//
////    Un_order_map<std::string, std::string> test;
//
//    int beforeBucketCnt = 0;
//
//    std::stringstream ss;
//
//    for (int i = 0; i < std::numeric_limits<int>::max(); ++i)
//    {
//
//        int curBucketCnt = test.bucket_count();
//        if(curBucketCnt != beforeBucketCnt)
//        {
//            ss << curBucketCnt << ", ";
//        }
//
//        beforeBucketCnt = test.bucket_count();
//
//        test.insert({i, i});
//
//        if(i == 1000000000)
//            break;
//
//    }
//
//    std::cout << ss.str();
//
//
//    int i2 = test.bucket_count();
//    int k2 = test.max_bucket_count();
//
//
//    int z = 0;
//    std::string result = test.find("test11");
    
    Un_order_map<int, std::string> test;
    
    test.insert({0,"rww"});
    test.insert({10,"ew"});
    test.insert({30,"w"});
    test.insert({40,"qwwt"});
    test.insert({50,"qwwy"});
    test.insert({60,"qwwu"});
    
    std::cout << test[0]->second() << std::endl;
    std::cout << test[10]->second() << std::endl;
    std::cout << test[30]->second() << std::endl;
    std::cout << test[41]->second() << std::endl;
    
    test.erase(1);
    test.erase(41);

//
//    test.insert(std::pair<int, std::string>(1,"test"));
//    test.insert(std::pair<int, std::string>(21,"예스"));
//    test.insert(std::pair<int, std::string>(31,"나이스"));
//    test.insert(std::pair<int, std::string>(2,"나이스"));
//
//    std::cout << test.find(1) << std::endl;
//    std::cout << test.find(21) << std::endl;
//    std::cout << test.find(31) << std::endl;
//    std::cout << test[1] << std::endl;
//    std::cout << test[21] << std::endl;
//    std::cout << test[31] << std::endl;
//    std::cout << test.empty() << std::endl;
//    std::cout << test.size() << std::endl;
//    test.erase(1);
//    test.erase(31);
//    test.erase(21);
//    std::cout << test.empty() << std::endl;
//    std::cout << test.size() << std::endl;
//
//    Un_order_map<std::string, std::string> testtest;
//
//    testtest.insert({"제발","test"});
//    testtest.insert({"되라","test"});
//    testtest.insert({"좋아","test"});
//    testtest.insert({"qqq","test"});
//    testtest.insert({"ww","test"});
//    testtest.insert({"vdvd","test"});
//    testtest.insert({"과연","test"});
    
    
    return 0;
}
