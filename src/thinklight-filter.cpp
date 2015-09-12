/*
 *    Copyright (C) 2015  Andrea Scarpino <scarpino@kde.org>
 *
 *    This library is free software; you can redistribute it and/or
 *    modify it under the terms of the GNU Lesser General Public
 *    License as published by the Free Software Foundation; either
 *    version 2.1 of the License, or (at your option) any later version.
 *
 *    This library is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *    Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public
 *    License along with this library; if not, write to the Free Software
 *    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301  USA
*/

#include "thinklight-filter.h"

#include <QDebug>
#include <QFile>
#include <QFileInfo>
#include <QTimer>

#include <KPluginFactory>

#include <TelepathyQt/Account>
#include <TelepathyQt/Constants>
#include <TelepathyQt/Presence>

#include "thinklightconfig.h"

const static QString LIGHT_PATH = QStringLiteral("/proc/acpi/ibm/light");

ThinkLightFilter::ThinkLightFilter(QObject* parent, const QVariantList &)
    : AbstractMessageFilter(parent)
    , m_blinking(false)
    , m_times(0)
{
}

ThinkLightFilter::~ThinkLightFilter()
{
}

void ThinkLightFilter::filterMessage(KTp::Message &message, const KTp::MessageContext &context)
{
    Q_UNUSED(context);

    if (message.direction() == KTp::Message::LocalToRemote) {
        return;
    }

    if (message.isHistory()) {
        return;
    }

    Tp::ConnectionPresenceType status = context.account().data()->currentPresence().type();

    if (status == Tp::ConnectionPresenceTypeBusy)
    {
        return;
    }

    if (ThinkLightConfig::self()->awayOnly()) {
        if (status != Tp::ConnectionPresenceTypeExtendedAway && status != Tp::ConnectionPresenceTypeAway) {
            return;
        }
    }

    if (!m_blinking) {
        m_blinking = true;
        m_times = ThinkLightConfig::self()->times();
        powerOn();
    }
}

void ThinkLightFilter::powerOff()
{
    setState(false);
    QTimer::singleShot(ThinkLightConfig::self()->offMsec(), this, &ThinkLightFilter::powerOn);
}

void ThinkLightFilter::powerOn()
{
    if (m_times > 0) {
        setState(true);
        QTimer::singleShot(ThinkLightConfig::self()->onMsec(), this, &ThinkLightFilter::powerOff);
        m_times--;
    } else {
        m_blinking = false;
    }
}

void ThinkLightFilter::setState(const bool powered)
{
    QFile lightFile(LIGHT_PATH);
    lightFile.open(QIODevice::ReadWrite);

    if (lightFile.isOpen()) {
        if (powered) {
            qDebug() << "Turning light on";
            lightFile.write(QByteArray("on"));
        } else {
            qDebug() << "Turning light off";
            lightFile.write(QByteArray("off"));
        }

        lightFile.close();
    } else {
        qDebug() << "Cannot open" << QFileInfo(lightFile).absoluteFilePath();
    }
}

K_PLUGIN_FACTORY(MessageFilterFactory, registerPlugin<ThinkLightFilter>();)

#include "thinklight-filter.moc"
