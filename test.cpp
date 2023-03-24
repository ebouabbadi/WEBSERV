#include <iostream>
#include <vector>

std::vector<std::string> split(std::string str, char delimiter)
{
    std::vector<std::string> tokens;
    std::string token;

    for (int i = 0; i < str.length(); i++)
    {
        if (str[i] == delimiter)
        {
            tokens.push_back(token);
            token.clear();
        }
        else
            token += str[i];
    }
    tokens.push_back(token);
    return tokens;
}

int main()
{
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
    std::string nb;
    int index = rqpost.find("boundary=");
    if (index == -1)
        return (0);
    else
    {
        index += 9;
        while (rqpost[index] == '-')
            index++;
        for (; rqpost[index] != '\n'; index++)
            nb.push_back(rqpost[index]);
    }
    int i = 0;
    // std::cout << nb;
    std::vector<std::string> my_body;
    while (rqpost[i])
    {
        if (rqpost.compare(0, nb.length(), nb))
            std::cout<<"X\n";
        i++;
    }
    
    // std::vector<std::string> ft_fa = split(pos, '\n');
    // std::string search = ft_fa[0];
    // int i = 1;
    // // while (ft_fa[i] != search)
    // //     i++;
    // for (const auto &str : ft_fa)
    // {
    //     if (str == search)
    //         std::cout<<"X\n";
    //     std::cout << str<<std::endl;
    // }

    //     while (search != ft_fa[i])
    //     {
    //         std::cout<<"size = "<<ft_fa[i]<<std::endl;
    //         std::string my_body;
    //         for (size_t j = 0; j < ft_fa[i].size(); j++)
    //         {
    //             my_body.push_back(ft_fa[i][j]);
    //         }
    //         std::cout<<my_body<<std::endl;
    //         i++;
    //     }
    //     i++;
    // }
    return (0);
}