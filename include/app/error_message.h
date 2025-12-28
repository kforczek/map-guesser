#pragma once
#include <QString>

class QWidget;

namespace app::err
{

enum class UserDecision
{
    Retry,
    Abort
};

UserDecision ShowErrorMessage(QWidget* parent, QString errDetails);

}
