#include "app/error_message.h"

#include <QMessageBox>

namespace app::err
{

UserDecision ShowErrorMessage(QWidget* parent, QString errDetails)
{
    if (!errDetails.endsWith('.'))
        errDetails += '.';

    auto bt = QMessageBox::critical(
        parent,
        "MapGuesser Error",
        errDetails,
        QMessageBox::Retry | QMessageBox::Abort,
        QMessageBox::Retry
    );

    return bt == QMessageBox::Retry ? UserDecision::Retry : UserDecision::Abort;
}

}
