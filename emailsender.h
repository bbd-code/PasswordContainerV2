#ifndef EMAILSENDER_H
#define EMAILSENDER_H

#define FROM_ADDR    "passcontprod@gmail.com"
#define FROM_MAIL "Password Container " FROM_ADDR

#include<QString>
#include<string>
#include<QRandomGenerator>
#include<curl/curl.h>

struct EmailSender
{

    static bool sendEmailCode(const std::string& email);

    static std::string CodeGeneration();
    static std::string getCode();

private:
    static size_t payload_source(char *ptr, size_t size, size_t nmemb, void *userp);
    static const char *payload_text;
    struct upload_status {
        size_t bytes_read;
    };
    static std::string code;


};

#endif // EMAILSENDER_H
