#include "Prasing_Request.hpp"
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
        std :: cout <<  hex <<"|||||||\n"; 
        tr =  (int)strtol(hex.c_str(), NULL, 16);
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
int main()
{
    std :: string body = "7\r\nMozill\n\r\n11\r\nDeveloper Network\r\n7\r\ndsvfdax\r\n";
    std :: string fin = ft_chanked(body);
    std :: cout << fin << std :: endl;
}