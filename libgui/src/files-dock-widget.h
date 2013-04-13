/*

Copyright (C) 2011-2012 Jacob Dawid

This file is part of Octave.

Octave is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation; either version 3 of the License, or (at your
option) any later version.

Octave is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License
along with Octave; see the file COPYING.  If not, see
<http://www.gnu.org/licenses/>.

*/

#ifndef FILESDOCKWIDGET_H
#define FILESDOCKWIDGET_H

#include <QListView>
#include <QDate>
#include <QObject>
#include <QWidget>
#include <QListWidget>
#include <QFileSystemModel>
#include <QToolBar>
#include <QToolButton>
#include <QVBoxLayout>
#include <QAction>
#include <QTreeView>
#include <QSettings>

#include <QComboBox>
#include "octave-dock-widget.h"

/**
   \class files_dock_widget
   \brief Dock widget to display files in the current directory.
*/
class files_dock_widget : public octave_dock_widget
{
  Q_OBJECT

public:

  files_dock_widget (QWidget *parent = 0);

  ~files_dock_widget ();

public slots:

  /** Slot for handling a change in directory via double click. */
  void item_double_clicked (const QModelIndex & index);

  /** Slot for handling the up-directory button in the toolbar. */
  void change_directory_up ();

  /** Slot for handling the sync octave directory button in the toolbar. */
  void do_sync_octave_directory ();

  /** Slot for handling the sync browser directory button in the toolbar. */
  void do_sync_browser_directory ();

  /** Sets the current directory being displayed. */
  void set_current_directory (const QString& dir);

  /** Accepts user input a the line edit for the current directory. */
  void accept_directory_line_edit ();

  /** set the internal variable that holds the actual octave variable **/
  void update_octave_directory (const QString& dir);

  /** Tells the widget to react on changed settings. */
  void notice_settings (const QSettings *settings);

private slots:
  /** context menu wanted */
  void contextmenu_requested (const QPoint& pos);

  /* context menu actions */
  void contextmenu_open (bool);
  void contextmenu_run (bool);
  void contextmenu_load (bool);
  void contextmenu_rename (bool);
  void contextmenu_delete (bool);
  void contextmenu_newfile (bool);
  void contextmenu_newdir (bool);
  void contextmenu_setcurrentdir (bool);

signals:

  /** Emitted, whenever the user requested to open a file. */
  void open_file (const QString& fileName);

  /** Emitted, whenever the currently displayed directory changed. */
  void displayed_directory_changed (const QString& dir);

  /** Emitted, whenever the user requested to load a file. */
  void load_file_signal (const QString& fileName);

  /** Emitted, whenever the user requested to run a file. */
  void run_file_signal (const QString& fileName);

private:

  // TODO: Add toolbar with buttons for navigating the path, creating dirs, etc

  /** set a new directory or open a file **/
  void display_directory (const QString& dir, bool set_octave_dir = true);

  /** Variables for the actions **/
  QAction *         _sync_octave_directory_action;
  QAction *         _sync_browser_directory_action;

  /** The file system model. */
  QFileSystemModel *_file_system_model;

  /** The file system view. */
  QTreeView *       _file_tree_view;
  QComboBox *       _current_directory;

  /** Internal variables **/
  bool              _sync_octave_dir;    // flag if syncing with octave
  QString           _octave_dir;         // the actual octave dir

  enum { MaxMRUDirs = 10 };
};

#endif // FILESDOCKWIDGET_H
