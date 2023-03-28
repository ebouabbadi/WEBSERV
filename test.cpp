#include <iostream>


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
        "----------------------------700303798331205453821588\n"
        "Content-Disposition: form-data; name='text'\n"
        "\n"
        "how2 are you\n"
        "im fine\n"
        "----------------------------700303798331205453821588\n"
        "Content-Disposition: form-data; name='text'\n"
        "\n"
        "how3 are you\n"
        "im fine\n"
        "----------------------------700303798331205453821588\n"
        "Content-Disposition: form-data; name='text'\n"
        "\n"
        "how4 are you\n"
        "im fine\n"
        "----------------------------700303798331205453821588--\n";
#include <deque>

std::deque  <std::string>   parsingBody(std:: string rqpost)
{
    std::string nb;
    std::string body;

    int index = rqpost.find("boundary=");
    if (index == -1)
        exit(0);
    else
    {
        index += 9;
        for (; rqpost[index] != '\n'; index++)
            nb.push_back(rqpost[index]);
    }
    int index2 = rqpost.find(nb, index + nb.length());
    if (index2 == -1)
        exit(0);
    else
    {
        for (; index2 < rqpost.length(); index2++)
            body.push_back(rqpost[index2]);----------------------------755825179202272912921011
    }
    std::deque<std::string> files;
    int i = 0;
    int j = 0;
    int len;
    while ((body[len + nb.length() - 2] != '-' && body[len + nb.length() - 3] != '-'))
    {
        len = body.find(nb, i + nb.length());
        if (len == -1)
            break;
        else
        {
            i+= nb.length();
            for (; i < len - 2; i++)
            {
                files[j].push_back(body[i]);
            }
            j++;
        }
        i = len;
    }
        return (files);
}