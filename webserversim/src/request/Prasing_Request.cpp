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
        if(mymap["Transfer-Encoding"] != "chunked")
        {
            if (this->methode == "POST" && (mymap["Content-Length"].empty() || atoi(mymap["Content-Length"].c_str()) < 0))
            {
                std ::cout << "error on Content-Length !!!" << std::endl;
                status = 400;
                return;
            }
        }
        if (mymap["Host"].empty())
        {
            std ::cout << "error om HOST !!" << std ::endl;
            status = 400;
            return;
        }
        // if (atoi(mymap["Content-Length"].c_str()) > 2000)
        // {
        //     std ::cout << "eroore on size Content-Length " << std::endl;
        //     status = 400;
        //     return;
        // }
    }
}

Prasing_Request::Prasing_Request(std::string hedr)
{
    if (!hedr.at(0))
        return;
    this->status = 200;
    std ::string first;
    std ::string hdr;
    std :: string body;
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
    prasing_body(hedr);

    if (this->status != 200)
        return;
}
 void Prasing_Request :: prasing_body(std :: string body1)
{
    std :: cout << ":::::::::::::::::::::::::::::::::::::::::::::::::::::::" << body1 << ":::::::::::::::::::::"<< std :: endl;
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
        return ;
    else
    {
        index += 9;
        for (; body1[index] != '\r'; index++)
            nb.push_back(body1[index]);
    }
    int index2 = 0;
     int fin = 0;
     int rq  = 0;
    for(;index2 != -1; i++)
    {
        index2 = body1.find(nb, fin);
         fin = body1.find(nb, index2  + 1);
        one_body.push_back(body1.substr(index2, fin - index2));
        if(body1[fin + nb.length() + 1]== '-' && body1[fin + nb.length()]== '-') 
            break;
    }
    while( rq < i)
    {
        // return ;
        std::string fil = "filename=";
        int first = one_body[rq].find(fil) +fil.length() + 1;
        int finish = one_body[rq].find("\"", first);
         std::string filename;
        //   = one_body[0].substr(first, finish - 1);
        for( int j = first ; j < finish; j++)
            filename += one_body[rq][j];
        rq++;
    }
}

std :: string ft_chanked(std :: string body)
{
    int i = 0;
    int tr = 0;
    std :: string chunked;
    while(i < body.length())
    {
        std :: string hex; 
        if(body[i] == '\r' && body[i + 1] == '\n')
            i += 2;
        while(body[i] != '\r' && body[i + 1] != '\n')
        {
            hex += body[i];
            i++; 
        }
        tr = (int)strtol(hex.c_str(), NULL, 16);
        i += 2;
        while( tr > 0)
        {
            chunked += body[i];
            tr--;
            i++;
        }
    }
    return chunked;
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