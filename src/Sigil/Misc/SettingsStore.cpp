/************************************************************************
**
**  Copyright (C) 2011  John Schember <john@nachtimwald.com>
**
**  This file is part of Sigil.
**
**  Sigil is free software: you can redistribute it and/or modify
**  it under the terms of the GNU General Public License as published by
**  the Free Software Foundation, either version 3 of the License, or
**  (at your option) any later version.
**
**  Sigil is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU General Public License for more details.
**
**  You should have received a copy of the GNU General Public License
**  along with Sigil.  If not, see <http://www.gnu.org/licenses/>.
**
*************************************************************************/

#include <stdafx.h>
#include <QSettings>
#include "SettingsStore.h"

SettingsStore *SettingsStore::m_instance = 0;

static const QString SETTINGS_GROUP = "user_preferences";
static const QString KEY_DEFAULT_METADATA_LANGUAGE = "default_metadata_lang";

SettingsStore *SettingsStore::instance()
{
    if (m_instance == 0) {
        m_instance = new SettingsStore();
    }

    return m_instance;
}

SettingsStore::~SettingsStore()
{
    writeSettings();
}

QString SettingsStore::defaultMetadataLang()
{
    return m_defaultMetadataLang;
}

void SettingsStore::setDefaultMetadataLang(const QString &lang)
{
    m_defaultMetadataLang = lang;
}

void SettingsStore::triggerSettingsChanged()
{
    emit settingsChanged();
}

void SettingsStore::writeSettings()
{
    QSettings settings;
    settings.beginGroup( SETTINGS_GROUP );

    settings.setValue(KEY_DEFAULT_METADATA_LANGUAGE, m_defaultMetadataLang);
}

SettingsStore::SettingsStore()
{
    readSettings();
}

void SettingsStore::readSettings()
{
    QSettings settings;
    settings.beginGroup( SETTINGS_GROUP );

    m_defaultMetadataLang = settings.value(KEY_DEFAULT_METADATA_LANGUAGE, tr("English")).toString();
}
