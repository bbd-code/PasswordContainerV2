#ifndef INPUTVALIDATION_H
#define INPUTVALIDATION_H

#include<QValidator>

class InputValidation
{

    using  State = QValidator::State;
    using  RegexValidator = QRegularExpressionValidator;
public:


    static State validateEmail(QString email);
    static State validatePassword(QString password);

private:
    static QRegularExpression emailPattern;
    static QRegularExpression passwordPattern;
};

#endif // INPUTVALIDATION_H
