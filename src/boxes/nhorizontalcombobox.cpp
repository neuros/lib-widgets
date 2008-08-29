/*
 *  Copyright(C) 2007 Neuros Technology International LLC. 
 *               <www.neurostechnology.com>
 *
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, version 2 of the License.
 *  
 *
 *  This program is distributed in the hope that, in addition to its 
 *  original purpose to support Neuros hardware, it will be useful 
 *  otherwise, but WITHOUT ANY WARRANTY; without even the implied 
 *  warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  
 *  See the GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 *
 ****************************************************************************
 *
 * NSpinBox implement routines.
 *
 * REVISION:
 * 
 * 1) Initial creation. ----------------------------------- 2008-07-22 WX
 *
 */

//#define QT_NO_DEBUG_OUTPUT
#include <QDebug>
#include <QLineEdit>
#include <QKeyEvent>
#include <QStylePainter>
#include "nlineedit.h"
#include "nhorizontalcombobox.h"
#include "nhorizontalcombobox_p.h"

NHorizontalComboBox::NHorizontalComboBox(QWidget *parent)
: QComboBox(parent), d(new NHorizontalComboBoxPrivate)
{
    setLineEdit(new NLineEdit(this));
    QPalette pal = palette();
    pal.setColor(QPalette::ButtonText, QColor(0xFF,0x66,0));
    setPalette(pal);
    setSizeAdjustPolicy(QComboBox::AdjustToContents);
    setWrapping(true);
    setEditable(false);
    setPlayRole(PlayAsComboBox);
    setLineEditTransparent(true);
}

bool NHorizontalComboBox::isLineEditTransparent() const 
{
    if (lineEdit() == NULL)
        return false; //No editor, just return false.

    QPalette pal = lineEdit()->palette();
    return(QColor(Qt::transparent) == pal.color(lineEdit()->backgroundRole()));
}

void NHorizontalComboBox::setLineEditTransparent(bool transparent)
{
    if ((lineEdit() == NULL)
        || (transparent == isLineEditTransparent()))
        return;

    QPalette pal = lineEdit()->palette();
    if (transparent)
    {
        //Backup the background color
        d->editorBackgroundColor = pal.color(lineEdit()->backgroundRole());
        pal.setColor(lineEdit()->backgroundRole(), Qt::transparent);
    }
    else
    {
        pal.setColor(lineEdit()->backgroundRole(), d->editorBackgroundColor);
    }

    lineEdit()->setPalette(pal);
}

bool NHorizontalComboBox::isWrapping() const
{
    return d->wrapping;
}

void NHorizontalComboBox::setWrapping(bool w)
{
    d->wrapping = w;
}

NHorizontalComboBox::PlayRole NHorizontalComboBox::playRole() const
{
    return d->role;
}

void NHorizontalComboBox::setPlayRole(PlayRole pr)
{
    if (pr == d->role)
        return;

    d->role = pr;
    NLineEdit *le = qobject_cast<NLineEdit *>(lineEdit());
    if (le == NULL)
        return;

    switch (d->role)
    {
    case PlayAsComboBox:
        le->setAcceptKeyMode(NLineEdit::AcceptAllKey);
        break;
    case PlayAsSpinBox:
        le->setAcceptKeyMode(NLineEdit::AcceptNumericKey | NLineEdit::AcceptMiscKey);
        break;
    default:
        break;
    }
}

void NHorizontalComboBox::keyPressEvent(QKeyEvent *e)
{
    switch (e->key())
    {
    case Qt::Key_Clear:
    case Qt::Key_Left:
    case Qt::Key_Right:
    case Qt::Key_Up:
    case Qt::Key_Down:
        {
            // Convert Keys
            int convertedKey = e->key();
            switch (e->key())
            {
            case Qt::Key_Clear:
                // Clear => Backspace
                convertedKey = Qt::Key_Backspace;
                break;
            case Qt::Key_Left:
                // if items wrapping and current is the first one, then Left => End, else Left => Up
                convertedKey = (d->wrapping && (currentIndex() == 0)) ? Qt::Key_End : Qt::Key_Up;
                break;
            case Qt::Key_Right:
                // if items wrapping and current is the last one, then Left => Home, else Left => Down
                convertedKey = (d->wrapping && (currentIndex() == count() - 1)) ? Qt::Key_Home : Qt::Key_Down;
                break;
            case Qt::Key_Up:
                // Up => Left
                convertedKey = Qt::Key_Left;
                e->ignore(); // ignore this key event, pass it to its parent
                break;
            case Qt::Key_Down:
                // Down => Right
                convertedKey = Qt::Key_Right;
                e->ignore(); // ignore this key event, pass it to its parent
                break;
            }

            QKeyEvent convertedKeyEvent(e->type(), convertedKey, e->modifiers(),
                                        e->text(), e->isAutoRepeat(), e->count());
            return QComboBox::keyPressEvent(&convertedKeyEvent);
        }
        break;
    default:
        break;
    }

    return QComboBox::keyPressEvent(e);
}

void NHorizontalComboBox::paintEvent(QPaintEvent *e)
{
    QStylePainter painter(this);

    QStyleOptionComboBox opt;
    initStyleOption(&opt);

    /* draw the NHorizontalComboBox left/right arrow */
    if ((opt.state & QStyle::State_HasFocus) && (opt.subControls & QStyle::SC_ComboBoxArrow))
    {
        int current = currentIndex();
        QRect ar = style()->subControlRect(QStyle::CC_ComboBox, &opt, QStyle::SC_ComboBoxArrow, this);
        QStyleOption arrowOpt(0);
        arrowOpt.rect = ar;
        arrowOpt.palette = opt.palette;
        arrowOpt.state = QStyle::State_None;

        if (opt.state & QStyle::State_Enabled)
            arrowOpt.state |= QStyle::State_Enabled;
        if (opt.activeSubControls == QStyle::SC_ComboBoxArrow && opt.state & QStyle::State_Sunken)
            arrowOpt.state |= QStyle::State_Sunken;

        if (current > 0 || d->wrapping)
            style()->drawPrimitive(QStyle::PE_IndicatorArrowLeft, &arrowOpt, &painter, this);

        arrowOpt.rect.moveLeft(opt.rect.x() + opt.rect.width() - ar.x() - ar.width());
        if (current < count() - 1 || d->wrapping)
            style()->drawPrimitive(QStyle::PE_IndicatorArrowRight, &arrowOpt, &painter, this);
    }

    /* draw the NHorizontalComboBox icon and text */
    painter.drawControl(QStyle::CE_ComboBoxLabel, opt);
}

QStringList NHorizontalComboBox::createNumericTexts(int from, int to) const
{
    QStringList numericTexts;

    if (from <= to)
    {
        for (int i = from; i <= to; ++ i)
            numericTexts.append(QString::number(i));
    }
    else
    {
        for (int i = from; i >= to; -- i)
            numericTexts.append(QString::number(i));
    }

    return numericTexts;
}



NHorizontalComboBoxPrivate::NHorizontalComboBoxPrivate()
{
    role = NHorizontalComboBox::PlayAsComboBox;
    wrapping = true;
}

NHorizontalComboBoxPrivate::~NHorizontalComboBoxPrivate()
{
}
