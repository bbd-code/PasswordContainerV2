#include "inputvalidation.h"




InputValidation::State InputValidation::validateEmail(QString email)
{

    if(email.isEmpty())
        return State::Acceptable;

    RegexValidator * validator = new RegexValidator(emailPattern);

    int pos = 0;
    State result = validator->validate(email, pos);
    delete validator;
    return result;
}

InputValidation::State InputValidation::validatePassword(QString password)
{

    if(password.isEmpty())
        return State::Acceptable;
    RegexValidator * validator = new RegexValidator(passwordPattern);

    int pos = 0;
    State result = validator->validate(password, pos);
    delete validator;
    return result;
}


QRegularExpression InputValidation::emailPattern = QRegularExpression((R"(^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Z|a-z]{2,}$)"));
QRegularExpression InputValidation::passwordPattern = QRegularExpression((R"(.{7,})"));
