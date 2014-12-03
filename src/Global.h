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

#pragma once

#define _CRT_RAND_S
#include <cstdlib>

//Forward declarations
class QString;
class QStringList;
class QDate;
class QTime;
class QIcon;
class QWidget;
class QProcess;
class QColor;
class LockedFile;
enum QtMsgType;

//Variables
extern const char* LAMEXP_DEFAULT_LANGID;
extern const char* LAMEXP_DEFAULT_TRANSLATION;

///////////////////////////////////////////////////////////////////////////////
// TYPE DEFINITIONS
///////////////////////////////////////////////////////////////////////////////

//Beep types
typedef enum
{
	lamexp_beep_info = 0,
	lamexp_beep_warning = 1,
	lamexp_beep_error = 2
}
lamexp_beep_t;

//Network connection types
typedef enum
{
	lamexp_network_err = 0,	/*unknown*/
	lamexp_network_non = 1,	/*not connected*/
	lamexp_network_yes = 2	/*connected*/
}
lamexp_network_t;

//System color types
typedef enum
{
	lamexp_syscolor_text = 0,
	lamexp_syscolor_background = 1,
	lamexp_syscolor_caption = 2
}
lamexp_syscolor_t;

//Icon type
class lamexp_icon_t;

///////////////////////////////////////////////////////////////////////////////
// GLOBAL FUNCTIONS
///////////////////////////////////////////////////////////////////////////////

const QIcon &lamexp_app_icon(void);
bool lamexp_append_sysmenu(const QWidget *win, const unsigned int identifier, const QString &text);
QStringList lamexp_available_codepages(bool noAliases = true);
bool lamexp_beep(int beepType);
void lamexp_blink_window(QWidget *poWindow, unsigned int count = 10, unsigned int delay = 150);
bool lamexp_block_window_move(void *message);
bool lamexp_bring_process_to_front(const unsigned long pid);
bool lamexp_bring_to_front(const QWidget *win);
bool lamexp_check_escape_state(void);
bool lamexp_check_sysmenu_msg(void *message, const unsigned int identifier);
bool lamexp_check_tool(const QString &toolName);
const QString lamexp_clean_filename(const QString &str);
const QString lamexp_clean_filepath(const QString &str);
unsigned long lamexp_dbg_private_bytes(void);
bool lamexp_enable_close_button(const QWidget *win, const bool bEnable = true);
void lamexp_finalization(void);
void lamexp_free_window_icon(lamexp_icon_t *icon);
int lamexp_init_ipc(void);
bool lamexp_install_translator(const QString &language);
bool lamexp_install_translator_from_file(const QString &qmFile);
void lamexp_ipc_read(unsigned int *command, char* message, size_t buffSize);
void lamexp_ipc_send(unsigned int command, const char* message);
const QString lamexp_lookup_tool(const QString &toolName);
const char *lamexp_mulders_url(void);
bool lamexp_play_sound(const QString &name, const bool bAsync);
bool lamexp_play_sound_file(const QString &library, const unsigned short uiSoundIdx, const bool bAsync);
bool lamexp_play_sound_alias(const QString &alias, const bool bAsync);
bool lamexp_portable_mode(void);
QStringList lamexp_query_translations(void);
void lamexp_register_tool(const QString &toolName, LockedFile *file, unsigned int version = 0, const QString *tag = NULL);
lamexp_icon_t *lamexp_set_window_icon(QWidget *window, const QIcon &icon, const bool bIsBigIcon);
bool lamexp_sheet_of_glass(QWidget *window);
bool lamexp_sheet_of_glass_update(QWidget *window);
QColor lamexp_system_color(const int color_id);
const char *lamexp_support_url(void);
bool lamexp_themes_enabled(void);
unsigned int lamexp_tool_version(const QString &toolName, QString *tag = NULL);
unsigned int lamexp_toolver_coreaudio(void);
unsigned int lamexp_toolver_fhgaacenc(void);
unsigned int lamexp_toolver_neroaac(void);
unsigned int lamexp_toolver_qaacenc(void);
const char *lamexp_tracker_url(void);
unsigned int lamexp_translation_country(const QString &langId);
bool lamexp_translation_init(void);
QString lamexp_translation_name(const QString &language);
bool lamexp_translation_register(const QString &langId, const QString &qmFile, const QString &langName, unsigned int &systemId, unsigned int &country);
unsigned int lamexp_translation_sysid(const QString &langId);
bool lamexp_update_sysmenu(const QWidget *win, const unsigned int identifier, const QString &text);
const QString lamexp_version2string(const QString &pattern, unsigned int version, const QString &defaultText, const QString *tag = NULL);
unsigned int lamexp_version_build(void);
unsigned int lamexp_version_confg(void);
bool lamexp_version_demo(void);
QDate lamexp_version_expires(void);
unsigned int lamexp_version_major(void);
unsigned int lamexp_version_minor(void);
const char *lamexp_version_release(void);
const char *lamexp_website_url(void);

///////////////////////////////////////////////////////////////////////////////
// HELPER MACROS
///////////////////////////////////////////////////////////////////////////////

#define NOBR(STR) (QString("<nobr>%1</nobr>").arg((STR)).replace("-", "&minus;"))
