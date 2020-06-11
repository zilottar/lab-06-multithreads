// Copyright 2018 Your Name <your_email>

#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_

#include <iostream>
#include "picosha2.h"
#include <thread>
#include <vector>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/sources/severity_feature.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/expressions.hpp>

namespace logging = boost::log;
namespace keywords = boost::log::keywords;


using std::string;
using std::cout;
using std::endl;
using std::vector;


class hashMaster {
public:
    uint64_t threadNumber;
    vector <std::thread> allThreads;
    
    hashMaster() {
        threadNumber = std::thread::hardware_concurrency();
        setThreads();
    }

    explicit hashMaster(int number) {
        threadNumber = number;
        setThreads();
    }



    void setThreads() {
        for (uint64_t i = 0; i < threadNumber; i++) {
            std::thread th(hashHandler, i, this);
            allThreads.push_back(std::move(th));
        }
        for (uint64_t i = 0; i < threadNumber; i++) {
            allThreads.at(i).join();
        }
    }



    static void hashHandler(int a, hashMaster *obj) {
        obj->init_logging();
        while (true){
            int stringLenth = 30;
            std::thread::id threadID=obj->allThreads.at(a).get_id();
            string stringForHash;
            for (int i = 0; i < stringLenth; ++i) {
                stringForHash.push_back(std::rand()%255);
            }
            const std::string hash = picosha2::hash256_hex_string(stringForHash);
            if (hash.find("0000", 60) == 60) {
                
                BOOST_LOG_TRIVIAL(info) << stringForHash << " - " << hash << " - " << threadID << endl;
                break;
            }
            else
                BOOST_LOG_TRIVIAL(trace) << stringForHash << " - " << " - " << hash << " - " << threadID << endl;
        }
    }

    static void init_logging() {
        
        logging::add_file_log (
                        keywords::file_name = "info.log",
                        keywords::format = "[%TimeStamp%] [%ThreadID%] [%Severity%] %Message%"
                );

        logging::add_console_log (
                std::cout,
                keywords::format = "[%TimeStamp%] [%ThreadID%] [%Severity%] %Message%"
        );

        logging::add_common_attributes();
    }
};

