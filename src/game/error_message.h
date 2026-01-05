#pragma once
#include <QString>

class QWidget;

namespace game::err
{

enum class UserDecision
{
    Retry,
    Abort
};

UserDecision ShowErrorMessage(QWidget* parent, QString errDetails);

}
