
#include "Prasing_Request.hpp"

#include <bits/stdc++.h>

int Prasing_Request::check_first_line(std::string first_line)
{
    this->methode = strtok((char *)first_line.c_str(), " ");
    if (this->methode != "GET" && this->methode != "POST" && this->methode != "DELETE")
    {
        std ::cout << "405 Method Not Allowed" << std::endl;
        status = 405;
        return (0);
    }
    char *urlll = strtok(NULL, " ");
    this->url = urlll;
    if (urlll[0] != '/')
    {
        std ::cout << "400 Bad Request" << std::endl;
        status = 400;
        return (0);
    }
    std ::string htb = strtok(NULL, " ");
    if (htb != "HTTP/1.1")
    {
        std::cout << "505 HTTP Version Not Supported" << std::endl;
        status = 505;
        return (0);
    }
    if (strchr(this->url.c_str(), '?'))
    {
        strtok((char *)this->url.c_str(), "?");
        char *str = strtok(NULL, "?");
        this->budy_url = str;
        // std ::cout << this->budy_url << std::endl;
    }
    return (1);
}

std ::vector<std ::string> split(std::string str, std::string delimiter)
{
    std ::vector<std ::string> v;
    if (!str.empty())
    {
        int start = 0;
        do
        {
            int idx = str.find(delimiter, start);
            if (idx == std ::string::npos)
            {
                break;
            }

            int length = idx - start;
            v.push_back(str.substr(start, length));
            start += (length + delimiter.size());
        } while (true);
        v.push_back(str.substr(start));
    }

    return v;
}

void Prasing_Request::prasing_headr(std ::string headrs)
{

    std ::vector<std ::string> res = split(headrs, "\r\n");
    for (int i = 0; i < res.size(); i++)
    {
        std ::string key = res[i].substr(0, res[i].find(":"));
        std ::string value = res[i].substr(res[i].find(" "));
        mymap.insert(std ::pair<std ::string, std::string>(key, value));
    }
    // std :: cout << mymap["Host"] << std::endl;
    if (status == 200)
    {
        if (this->methode == "POST" && mymap["Content-Type"].empty())
        {
            std ::cout << "error on Content-Type !!!" << std::endl;
            status = 400;
            return;
        }
        if (this->methode == "POST" && (mymap["Content-Length"].empty() || atoi(mymap["Content-Length"].c_str()) < 0))
        {
            std ::cout << "error on Content-Length !!!" << std::endl;
            status = 400;
            return;
        }
        if (mymap["Host"].empty())
        {
            std ::cout << "error om HOST !!" << std ::endl;
            status = 400;
            return;
        }
        if (atoi(mymap["Content-Length"].c_str()) > 2000)
        {
            std ::cout << "eroore on size Content-Length " << std::endl;
            status = 400;
            return;
        }
    }
}

Prasing_Request::Prasing_Request(std::string hedr)
{
    if (!hedr.at(0))
        return;
    this->status = 200;
    /*-----------------------------------------------------------------------------------------------------*/
    std::string rqpost = 
        "POST / HTTP/1.1\n"
        "User-Agent: PostmanRuntime/7.31.3\n"
        "Accept: */*\n"
        "Postman-Token: 77f3dc34-770d-401f-b406-c774c7202228\n"
        "Host: localhost:7000\n"
        "Accept-Encoding: gzip, deflate, br\n"
        "Connection: keep-alive\n"
        "Content-Type: multipart/form-data; boundary=--------------------------700303798331205453821588\n"
        "Cookie: Cookie_1=value; Cookie_2=value; Cookie_3=value; Cookie_4=value\n"
        "Content-Length: 375\n"
        "\n"
        "----------------------------700303798331205453821588\n"
        "Content-Disposition: form-data; name='file'; filename='texte.txt'\n"
        "Content-Type: text/plain\n"
        "\n"
        "HI i'am  Mehdi\n"
        "23 y  i have experience\n"
        "ok save\n"
        "----------------------------700303798331205453821588\n"
        "Content-Disposition: form-data; name='text'\n"
        "\n"
        "how are you\n"
        "im fine\n"
        "----------------------------700303798331205453821588--\n";
    /*--------------------------------------------------------------------------------------------------------------*/

        
    std::cout<<"--------------------------------------------------------------------------\n";
    std::cout<<rqpost<<std::endl;
    std::cout<<"--------------------------------------------------------------------------\n";
    std ::string first;
    std ::string hdr;
    std::string body;
    int i = 0;
    while (i < hedr.length())
    {
        if (hedr.at(i) == '\r' || hedr.at(i) == '\n')
            break;
        i++;
    }

    first = hedr.substr(0, i);
    hdr = hedr.substr(0, hedr.find("\r\n\r\n"));
    body = hedr.substr(hedr.find("\r\n\r\n"));
    if (!check_first_line(first))
        return;
    prasing_headr(hdr);

    if (this->status != 200)
        return;
}
std ::string Prasing_Request::get_url()
{
    return this->url;
}
std::map<std::string,std::string> Prasing_Request::get_mymap()
{
    return (mymap);
}
int Prasing_Request::get_status()
{
    return(status);
}
std::string Prasing_Request::get_method()
{
    return(methode);
}
std::string Prasing_Request::get_budy_url()
{
    return(budy_url);
}