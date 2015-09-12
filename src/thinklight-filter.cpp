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

#include <KPluginFactory>

#include <TelepathyQt/Account>
#include <TelepathyQt/Constants>
#include <TelepathyQt/Presence>

#include "thinklightconfig.h"

ThinkLightFilter::ThinkLightFilter(QObject* parent, const QVariantList &)
    : AbstractMessageFilter(parent)
    , m_blinking(false)
    , m_process(new QProcess(this))
{
    connect(m_process, (void (QProcess::*)(int))&QProcess::finished, this, &ThinkLightFilter::finished);
}

ThinkLightFilter::~ThinkLightFilter()
{
    if (m_process->state() == QProcess::Running) {
        m_process->kill();
    }

    delete m_process;
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
        QStringList parameters;
        parameters << QString::number(ThinkLightConfig::self()->times());
        parameters << QString::number(ThinkLightConfig::self()->onMsec());
        parameters << QString::number(ThinkLightConfig::self()->offMsec());
        m_process->start(ThinkLightConfig::self()->thinkAlertPath(), parameters);
    }
}

void ThinkLightFilter::finished(int exitCode)
{
    m_blinking = false;

    if (!exitCode) {
        qDebug() << "ThinkAlert failed with exit code" << exitCode;
    }
}

K_PLUGIN_FACTORY(MessageFilterFactory, registerPlugin<ThinkLightFilter>();)

#include "thinklight-filter.moc"
