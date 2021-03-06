/* Copyright 2020 Intel Corporation
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

#include <string>
#include "logic.h"
#include "io_helper.h"

#define USER_FILES_PATH "/tmp/tutorial/"

std::string ProcessHelloWorld(std::string in_str) {
    return "Hello " + in_str;
}  // ProcessHelloWorld 

std::string GetCountOrKey(std::string name, std::string hex_key) {
    std::string file_path = USER_FILES_PATH + name;
    IoHelper io_helper(file_path);
    std::string ret_str;

    if (hex_key.empty()) {
        io_helper.DeleteFile();
        // Generate symmetric hex key
        ret_str = io_helper.GenerateKey();        
        io_helper.SetKey(ret_str);
        io_helper.WriteFile("1");
    } else {
        io_helper.SetKey(hex_key);
        if (!io_helper.ReadFile(ret_str)) {
            size_t count = std::stoul(ret_str);
            count++;
            ret_str = std::to_string(count);
            io_helper.WriteFile(ret_str);
        }
    }

    return ret_str;
}  // GetCountOrKey
