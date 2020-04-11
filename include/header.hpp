// Copyright 2018 Your Name <your_email>

#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_
#include <picosha2.h>
#include <regex>
#include <string>
#include <iostream>
#include <thread>
#include <logs.h>
#include <boost/thread.hpp>

namespace header {
    void tryregex(std::string s) {
        std::string hash_hex_str;
        picosha2::hash256_hex_string(s.begin(), s.end(), hash_hex_str);
        logs::logTrace(s, hash_hex_str);
        if (std::regex_match(hash_hex_str, std::regex {R"(\w{60}+[0]{4})"})) {
            logs::logInfo(s, hash_hex_str);
        }
    }

    void runner(int random){
        while (true){
            static unsigned int rand = time(nullptr)+random;
            unsigned int a = rand_r(&rand)%10000;
            tryregex(std::to_string(a));
        }
    }

    void startTreads(unsigned int m){
        logs::init();
        boost::thread_group threads;
        for (unsigned int i = 0; i < m; ++i)
            threads.create_thread(boost::bind(runner, boost::cref(i)));
        threads.join_all();
    }
}// namespace header
#endif // INCLUDE_HEADER_HPP_
