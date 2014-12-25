///////////////////////////////////////////////////////////////////////////////
// LameXP - Audio Encoder Front-End
// Copyright (C) 2004-2014 LoRd_MuldeR <MuldeR2@GMX.de>
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version, but always including the *additional*
// restrictions defined in the "License.txt" file.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program; if not, write to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
//
// http://www.gnu.org/licenses/gpl-2.0.txt
///////////////////////////////////////////////////////////////////////////////

#include "Global.h"

//LameXP includes
#define LAMEXP_INC_CONFIG 1
#include "Resource.h"
#include "Config.h"

//MUtils
#include <MUtils/Version.h>

//Qt includes
#include <QApplication>
#include <QDate>
#include <QFileInfo>
#include <QReadWriteLock>

///////////////////////////////////////////////////////////////////////////////
// GLOBAL VARS
///////////////////////////////////////////////////////////////////////////////

static QReadWriteLock g_lamexp_version_lock;

//Build version
static const unsigned int g_lamexp_version_major = VER_LAMEXP_MAJOR;
static const unsigned int g_lamexp_version_minor = (10 * VER_LAMEXP_MINOR_HI) + VER_LAMEXP_MINOR_LO;
static const unsigned int g_lamexp_version_build = VER_LAMEXP_BUILD;
static const unsigned int g_lamexp_version_confg = VER_LAMEXP_CONFG;
static const char*        g_lamexp_version_rname = VER_LAMEXP_RNAME;

//Demo Version
static int g_lamexp_demo = -1;

//Portable Mode
static int g_lamexp_portable = -1;

//Expiration date
static QScopedPointer<QDate> g_lamexp_expiration_date;

//Official web-site URL
static const char *g_lamexp_website_url = "http://lamexp.sourceforge.net/";
static const char *g_lamexp_mulders_url = "http://muldersoft.com/";
static const char *g_lamexp_support_url = "http://forum.doom9.org/showthread.php?t=157726";
static const char *g_lamexp_tracker_url = "https://github.com/lordmulder/LameXP/issues";

//Tool versions (expected versions!)
static const unsigned int g_lamexp_toolver_neroaac   = VER_LAMEXP_TOOL_NEROAAC;
static const unsigned int g_lamexp_toolver_fhgaacenc = VER_LAMEXP_TOOL_FHGAACENC;
static const unsigned int g_lamexp_toolver_qaacenc   = VER_LAMEXP_TOOL_QAAC;
static const unsigned int g_lamexp_toolver_coreaudio = VER_LAMEXP_TOOL_COREAUDIO;

///////////////////////////////////////////////////////////////////////////////
// GLOBAL FUNCTIONS
///////////////////////////////////////////////////////////////////////////////

/*
 * Version getters
 */
unsigned int lamexp_version_major(void)     { return g_lamexp_version_major;     }
unsigned int lamexp_version_minor(void)     { return g_lamexp_version_minor;     }
unsigned int lamexp_version_build(void)     { return g_lamexp_version_build;     }
unsigned int lamexp_version_confg(void)     { return g_lamexp_version_confg;     }
const char*  lamexp_version_release(void)   { return g_lamexp_version_rname;     }
unsigned int lamexp_toolver_neroaac(void)   { return g_lamexp_toolver_neroaac;   }
unsigned int lamexp_toolver_fhgaacenc(void) { return g_lamexp_toolver_fhgaacenc; }
unsigned int lamexp_toolver_qaacenc(void)   { return g_lamexp_toolver_qaacenc;   }
unsigned int lamexp_toolver_coreaudio(void) { return g_lamexp_toolver_coreaudio; }

/*
 * URL getters
 */
const char *lamexp_website_url(void) { return g_lamexp_website_url; }
const char *lamexp_mulders_url(void) { return g_lamexp_mulders_url; }
const char *lamexp_support_url(void) { return g_lamexp_support_url; }
const char *lamexp_tracker_url(void) { return g_lamexp_tracker_url; }

/*
 * Check for Demo (pre-release) version
 */
bool lamexp_version_demo(void)
{
	QReadLocker readLock(&g_lamexp_version_lock);

	if(g_lamexp_demo >= 0)
	{
		return (g_lamexp_demo > 0);
	}
	
	readLock.unlock();
	QWriteLocker writeLock(&g_lamexp_version_lock);

	if(g_lamexp_demo < 0)
	{
		g_lamexp_demo = (_strnicmp(g_lamexp_version_rname, "Final", 5) && _strnicmp(g_lamexp_version_rname, "Hotfix", 6)) ? (1) : (0);
	}

	return (g_lamexp_demo > 0);
}

/*
 * Calculate expiration date
 */
const QDate &lamexp_version_expires(void)
{
	QReadLocker readLock(&g_lamexp_version_lock);

	if(!g_lamexp_expiration_date.isNull())
	{
		return *g_lamexp_expiration_date;
	}

	readLock.unlock();
	QWriteLocker writeLock(&g_lamexp_version_lock);

	if(g_lamexp_expiration_date.isNull())
	{
		g_lamexp_expiration_date.reset(new QDate(MUtils::Version::app_build_date().addDays(MUTILS_DEBUG ? 7 : 30)));
	}

	return *g_lamexp_expiration_date;
}

/*
 * Check for LameXP "portable" mode
 */
bool lamexp_version_portable(void)
{
	QReadLocker readLock(&g_lamexp_version_lock);

	if(g_lamexp_portable >= 0)
	{
		return (g_lamexp_portable > 0);
	}
	
	readLock.unlock();
	QWriteLocker writeLock(&g_lamexp_version_lock);

	if(g_lamexp_portable < 0)
	{
		if(VER_LAMEXP_PORTABLE_EDITION)
		{
			qWarning("LameXP portable edition!\n");
			g_lamexp_portable = 1;
		}
		else
		{
			const QString baseName = QFileInfo(QApplication::applicationFilePath()).completeBaseName();
			const int idx1 = baseName.indexOf("lamexp", 0, Qt::CaseInsensitive);
			const int idx2 = baseName.lastIndexOf("portable", -1, Qt::CaseInsensitive);
			g_lamexp_portable = ((idx1 >= 0) && (idx2 >= 0) && (idx1 < idx2)) ? (1) : (0);
		}
	}
	
	return (g_lamexp_portable > 0);
}