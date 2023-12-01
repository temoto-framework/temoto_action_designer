
#include "condition_edit_widget.hpp"
#include <QHBoxLayout>
#include <QVBoxLayout>

ConditionEditWidget::ConditionEditWidget(const std::string parent_name, QWidget* parent)
: QWidget(parent)
{
    setSizePolicy(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Minimum);

    QVBoxLayout *vl = new QVBoxLayout(this);
    vl->setAlignment(Qt::AlignTop);
    vl->setContentsMargins(0, 0, 0, 0);
    vl->setSpacing(0);
    // vl->addStretch();

    name_label_ = new QLabel(parent_name.c_str());
    vl->addWidget(name_label_);

    QHBoxLayout* hl_on_true = new QHBoxLayout();
    QLabel* label_on_true = new QLabel("on 'true': ");
    hl_on_true->addWidget(label_on_true);
    vl->addLayout(hl_on_true);

    QHBoxLayout* hl_on_false = new QHBoxLayout();
    QLabel* label_on_false = new QLabel("on 'false': ");
    hl_on_false->addWidget(label_on_false);
    vl->addLayout(hl_on_false);

    QHBoxLayout* hl_on_error = new QHBoxLayout();
    QLabel* label_on_error = new QLabel("on 'error': ");
    hl_on_error->addWidget(label_on_error);
    vl->addLayout(hl_on_error);

    // vl->addLayout(_left);
    // vl->addSpacing(50);
    // vl->addLayout(_right);
}

ConditionEditWidget::~ConditionEditWidget()
{
    //
}

void ConditionEditWidget::setName(const std::string& name)
{
    name_label_->setText(name.c_str());
    name_label_->adjustSize();
}

// void ConditionEditWidget::populateButtons(PortType portType, unsigned int nPorts)
// {
//     QVBoxLayout *vl = (portType == PortType::In) ? _left : _right;

//     // we use [-1} in the expression `vl->count() - 1` because
//     // one element - a spacer - is alvays present in this layout.

//     if (vl->count() - 1 < nPorts)
//         while (vl->count() - 1 < nPorts) {
//             addButtonGroupToLayout(vl, 0);
//         }

//     if (vl->count() - 1 > nPorts) {
//         while (vl->count() - 1 > nPorts) {
//             removeButtonGroupFromLayout(vl, 0);
//         }
//     }
// }

// QHBoxLayout *ConditionEditWidget::addButtonGroupToLayout(QVBoxLayout *vbl, unsigned int portIndex)
// {
//     auto l = new QHBoxLayout();
//     l->setContentsMargins(0, 0, 0, 0);

//     auto button = new QPushButton("+");
//     button->setFixedHeight(25);
//     l->addWidget(button);
//     connect(button, &QPushButton::clicked, this, &ConditionEditWidget::onPlusClicked);

//     button = new QPushButton("-");
//     button->setFixedHeight(25);
//     l->addWidget(button);
//     connect(button, &QPushButton::clicked, this, &ConditionEditWidget::onMinusClicked);

//     vbl->insertLayout(portIndex, l);

//     return l;
// }

// void ConditionEditWidget::removeButtonGroupFromLayout(QVBoxLayout *vbl, unsigned int portIndex)
// {
//     // Last item in the layout is always a spacer
//     if (vbl->count() > 1) {
//         auto item = vbl->itemAt(portIndex);

//         // Delete [+] and [-] QPushButton widgets
//         item->layout()->itemAt(0)->widget()->deleteLater();
//         item->layout()->itemAt(1)->widget()->deleteLater();

//         vbl->removeItem(item);

//         delete item;
//     }
// }

// void ConditionEditWidget::onPlusClicked()
// {
//     // index of the plus button in the QHBoxLayout
//     int const plusButtonIndex = 0;

//     PortType portType;
//     PortIndex portIndex;

//     // All existing "plus" buttons trigger the same slot. We need to find out which
//     // button has been actually clicked.
//     std::tie(portType, portIndex) = findWhichPortWasClicked(QObject::sender(), plusButtonIndex);

//     // We add new "plus-minus" button group to the chosen layout.
//     addButtonGroupToLayout((portType == PortType::In) ? _left : _right, portIndex + 1);

//     // Trigger changes in the model
//     _model.addPort(_nodeId, portType, portIndex + 1);

//     adjustSize();
// }

// void ConditionEditWidget::onMinusClicked()
// {
//     // index of the minus button in the QHBoxLayout
//     int const minusButtonIndex = 1;

//     PortType portType;
//     PortIndex portIndex;

//     std::tie(portType, portIndex) = findWhichPortWasClicked(QObject::sender(), minusButtonIndex);

//     removeButtonGroupFromLayout((portType == PortType::In) ? _left : _right, portIndex);

//     // Trigger changes in the model
//     _model.removePort(_nodeId, portType, portIndex);

//     adjustSize();
// }

// std::pair<PortType, PortIndex> ConditionEditWidget::findWhichPortWasClicked(QObject *sender,
//                                                                             int const buttonIndex)
// {
//     PortType portType = PortType::None;
//     PortIndex portIndex = QtNodes::InvalidPortIndex;

//     auto checkOneSide = [&portType, &portIndex, &sender, &buttonIndex](QVBoxLayout *sideLayout) {
//         for (int i = 0; i < sideLayout->count(); ++i) {
//             auto layoutItem = sideLayout->itemAt(i);
//             auto hLayout = dynamic_cast<QHBoxLayout *>(layoutItem);

//             if (!hLayout)
//                 continue;

//             auto widget = static_cast<QWidgetItem *>(hLayout->itemAt(buttonIndex))->widget();

//             if (sender == widget) {
//                 portIndex = i;
//                 break;
//             }
//         }
//     };

//     checkOneSide(_left);

//     if (portIndex != QtNodes::InvalidPortIndex) {
//         portType = PortType::In;
//     } else {
//         checkOneSide(_right);

//         if (portIndex != QtNodes::InvalidPortIndex) {
//             portType = PortType::Out;
//         }
//     }

//     return std::make_pair(portType, portIndex);
// }
