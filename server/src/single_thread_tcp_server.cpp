#include "single_thread_tcp_server.h"
#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>
#include <cmath>
#include <bits/stdc++.h>

typedef unsigned char uchar;
static const std::string b = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";//=
static std::string base64_encode(const std::string& in) {
    std::string out;

    int val = 0, valb = -6;
    for (uchar c : in) {
        val = (val << 8) + c;
        valb += 8;
        while (valb >= 0) {
            out.push_back(b[(val >> valb) & 0x3F]);
            valb -= 6;
        }
    }
    if (valb > -6) out.push_back(b[((val << 8) >> (valb + 8)) & 0x3F]);
    while (out.size() % 4) out.push_back('=');
    return out;
}


void handle_connection(SOCKET socket, sockaddr_in* addr) {
    char* str_in_addr = inet_ntoa(addr->sin_addr);
    printf("[%s]>>%s\n", str_in_addr, "Establish new connection");
    while (true) {
        char buffer[256] = "";
        int rc = recv(socket, buffer, sizeof(buffer), 0);
        if (rc > 0) {
            printf("[%s]:%s\n", str_in_addr, buffer);
            std::string login = "";
            std::string password = "";
            std::vector<int> x;
            std::vector<int> y;
            std::string s = buffer;
            std::string delimiter = " ";

            size_t pos = 0;
            std::string token;
            while ((pos = s.find(delimiter)) != std::string::npos) {
                login = s.substr(0, pos);
               }
            password = s;

            std::string msg = base64_encode(login + password);

            char cstr[msg.size()+ 1];
            strcpy(cstr, msg .c_str());    // or pass &s[0]
 
            std::cout << cstr << '\n';
            send(socket, cstr, sizeof(cstr), 0);
            }
        else {
            break;
        }
    }
    close_socket(socket);
    printf("[%s]>>%s", str_in_addr, "Close incomming connection");
}