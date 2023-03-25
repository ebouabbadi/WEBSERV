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
    std::string body;
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
    int index2 = rqpost.find(nb, index + nb.length());
    for (; index2 < rqpost.length(); index2++)
        body.push_back(rqpost[index2]);
    
    // int index3 = rqpost.find(nb, index2 + nb.length());
    // for (; index3 < rqpost.length(); index3++)
    // {
    //     std::cout<<rqpost[index3];
    // }
    std::cout << "==============================================================\n";

    return (0);
}