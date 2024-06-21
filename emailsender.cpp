#include "emailsender.h"





bool EmailSender::sendEmailCode(const std::string &email)
{
    code = CodeGeneration();

    std::string temp = "Date: Mon, 29 Nov 2024 21:54:29 +1100\r\n"
                       "To: "+ email + "\r\n"
                       "From: " FROM_MAIL " \r\n"
                       "Subject: Код подтверждения\r\n"
                       "\r\n" /* Разделение заголовка письма от тела see RFC 5322 */
                       "Ваш код подтверждения :  " + code  + "\r\n"
                       "\r\n";

    payload_text = temp.c_str();

    CURL *curl;
    CURLcode res = CURLE_OK;
    struct curl_slist *recipients = nullptr;
    struct upload_status upload_ctx = {0};

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_USERNAME, FROM_ADDR);
        curl_easy_setopt(curl, CURLOPT_PASSWORD, "mddu yurl fmnd cigx");
        curl_easy_setopt(curl, CURLOPT_URL, "smtps://smtp.gmail.com:465");
        curl_easy_setopt(curl, CURLOPT_MAIL_FROM, FROM_ADDR);
        recipients = curl_slist_append(recipients, email.c_str());
        curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);
        curl_easy_setopt(curl, CURLOPT_READFUNCTION, payload_source);
        curl_easy_setopt(curl, CURLOPT_READDATA, &upload_ctx);
        curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, FALSE);
        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
            curl_slist_free_all(recipients);
            curl_easy_cleanup(curl);
            return false;
        }
        curl_slist_free_all(recipients);
        curl_easy_cleanup(curl);
        return true;
    }
    return false;
}





std::string EmailSender::CodeGeneration()
{
    return std::to_string(QRandomGenerator::securelySeeded().bounded(100000, 999999));
}

size_t EmailSender::payload_source(char *ptr, size_t size, size_t nmemb, void *userp)
{
    struct upload_status *upload_ctx = (struct upload_status *)userp;
    const char *data;
    size_t room = size * nmemb;

    if((size == 0) || (nmemb == 0) || ((size*nmemb) < 1)) {
        return 0;
    }

    data = &payload_text[upload_ctx->bytes_read];

    if(data) {
        size_t len = strlen(data);
        if(room < len)
            len = room;
        memcpy(ptr, data, len);
        upload_ctx->bytes_read += len;

        return len;
    }

    return 0;
}

std::string EmailSender::getCode()
{
    return code;
}

const char* EmailSender::payload_text = "";
std::string EmailSender::code;
