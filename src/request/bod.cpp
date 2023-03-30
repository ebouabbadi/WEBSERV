#include "Prasing_Request.hpp"
#include <iostream>
#include <vector>

#include <fstream>
using namespace std;

int main()
{
    // std :: cout << ":::::::::::::::::::::::::::::::::::::::::::::::::::::::" << body1 << ":::::::::::::::::::::"<< std :: endl;
    std ::string body1 = "POST / HTTP/1.1\r\n";
    body1 += "User-Agent: PostmanRuntime/7.31.3\r\n";
    body1 += "Accept: */*\r\n";
    body1 += "Postman-Token: 77f3dc34-770d-401f-b406-c774c7202228\r\n";
    body1 += "Host: localhost:7000\r\n";
    body1 += "Accept-Encoding: gzip, deflate, br\r\n";
    body1 += "Connection: keep-alive\r\n";
    body1 += "Content-Type: multipart/form-data; boundary=--------------------------700303798331205453821588\r\n";
    body1 += "Content-Length: 375\r\n";
    body1 += "\r\n\r\n";
    body1 += "----------------------------700303798331205453821588\r\n";
    body1 += "Content-Disposition: form-data; name=ss; filename=\"java_script.html\"\r\n";
    body1 += "Content-Type: text/html\r\n";
    body1 += "\r\n\r\n";
    body1 += "<!DOCTYPE html>\n";
    body1 += "<html>\n";
    body1 += "<h2>Demo JavaScript in Head</h2>\n";
    body1 += "</html>\n";
    body1 += "----------------------------700303798331205453821588\r\n";
    body1 += "Content-Disposition: form-data; name=ss; filename=\"java_simo.html\"\r\n";
    body1 += "Content-Type: text/html\r\n";
    body1 += "\r\n\r\n";
    body1 += "<!DOCTYPE html>\n";
    body1 += "<html>\n";
    body1 += "<h2>kin walh ta kin </h2>\n";
    body1 += "</html>\n";
    body1 += "----------------------------700303798331205453821588--\n";
    std::string nb;
    std::string body;
    std::string file1;
    std::string file2;
    std::string file3;
    std::string file4;
    int i = 0;
    std::vector<std::string> one_body;
    nb = "--";
    int index = body1.find("boundary=");
    if (index == -1)
        return 1;
    else
    {
        index += 9;
        for (; body1[index] != '\r'; index++)
            nb.push_back(body1[index]);
    }
    int index2 = 0;
    int fin = 0;
    int rq = 0;

    for (; index2 != -1; i++)
    {
        index2 = body1.find(nb, fin);
        fin = body1.find(nb, index2 + 1);
        one_body.push_back(body1.substr(index2, fin - index2));
        if (body1[fin + nb.length() + 1] == '-' && body1[fin + nb.length()] == '-')
            break;
    }
    while (rq <= i)
    {
        // return ;
        std::string fil = "filename=";

        std ::cout << one_body[0] << std ::endl;
        int first = one_body[rq].find(fil) + fil.length() + 1;
        int finish = one_body[rq].find("\"", first);
        std::string filename;
        //   = one_body[0].substr(first, finish - 1);
        for (int j = first; j < finish; j++)
            filename += one_body[rq][j];
        std ::string str = one_body[rq].substr(one_body[rq].find("\r\n\r\n") + 4);
        std ::string filee = "../../www/upload/" + filename;
        //   std :: cout << "======"<<filee<< "======="<<std :: endl;
        std ::ofstream MyFile(filee.c_str());
        MyFile << str;
        MyFile.close();
        rq++;
    }
    return 0;
}