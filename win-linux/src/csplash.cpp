/*
 * (c) Copyright Ascensio System SIA 2010-2016
 *
 * This program is a free software product. You can redistribute it and/or
 * modify it under the terms of the GNU Affero General Public License (AGPL)
 * version 3 as published by the Free Software Foundation. In accordance with
 * Section 7(a) of the GNU AGPL its Section 15 shall be amended to the effect
 * that Ascensio System SIA expressly excludes the warranty of non-infringement
 * of any third-party rights.
 *
 * This program is distributed WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR  PURPOSE. For
 * details, see the GNU AGPL at: http://www.gnu.org/licenses/agpl-3.0.html
 *
 * You can contact Ascensio System SIA at Lubanas st. 125a-25, Riga, Latvia,
 * EU, LV-1021.
 *
 * The  interactive user interfaces in modified source and object code versions
 * of the Program must display Appropriate Legal Notices, as required under
 * Section 5 of the GNU AGPL version 3.
 *
 * Pursuant to Section 7(b) of the License you must retain the original Product
 * logo when distributing the program. Pursuant to Section 7(e) we decline to
 * grant you any rights under trademark law for use of our trademarks.
 *
 * All the Product's GUI elements, including illustrations and icon sets, as
 * well as technical writing content are licensed under the terms of the
 * Creative Commons Attribution-ShareAlike 4.0 International. See the License
 * terms at http://creativecommons.org/licenses/by-sa/4.0/legalcode
 *
*/


#include "csplash.h"
#include "defines.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QSettings>

CSplash * _splash;
extern uchar g_dpi_ratio;

CSplash::CSplash(const QPixmap &p, Qt::WindowFlags f)
    : QSplashScreen(p, f)
{
    _splash = NULL;
}

void CSplash::show()
{
    if (QApplication::desktop()->screenCount() > 1) {
        GET_REGISTRY_USER(reg_user)

        if (reg_user.contains("position")) {
            int _scr_num = QApplication::desktop()->screenNumber(
                                reg_user.value("position").toRect().topLeft() );

            move(QApplication::desktop()->screenGeometry(_scr_num).center() - rect().center());
        }
    }

    QSplashScreen::show();
}

void CSplash::showSplash()
{
    if ( !_splash ) {
        QPixmap _pixmap = g_dpi_ratio > 1 ?
#ifdef _IVOLGA_PRO
            QPixmap(":/ivolga/splash@2x.png") : QPixmap(":/ivolga/splash.png");
#elif defined(_AVS)
            QPixmap(":/avs/splash@2x.png") : QPixmap(":/avs/splash.png");
#else
            QPixmap(":/res/icons/splash_2x.png") : QPixmap(":/res/icons/splash.png");
#endif

        (_splash = new CSplash(_pixmap, Qt::WindowStaysOnTopHint))
        ->show();
    }
}

void CSplash::hideSplash()
{
    if (_splash) {
//        g_splash->setParent((QWidget *)parent());
        _splash->close();

        delete _splash, _splash = NULL;
    }
}
