/*******************************************************************************************************
 ReadFramework is the basis for modules developed at CVL/TU Wien for the EU project READ. 
  
 Copyright (C) 2016 Markus Diem <diem@caa.tuwien.ac.at>
 Copyright (C) 2016 Stefan Fiel <fiel@caa.tuwien.ac.at>
 Copyright (C) 2016 Florian Kleber <kleber@caa.tuwien.ac.at>

 This file is part of ReadFramework.

 ReadFramework is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 ReadFramework is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.

 The READ project  has  received  funding  from  the European  Union’s  Horizon  2020  
 research  and innovation programme under grant agreement No 674943
 
 related links:
 [1] http://www.caa.tuwien.ac.at/cvl/
 [2] https://transkribus.eu/Transkribus/
 [3] https://github.com/TUWien/
 [4] http://nomacs.org
 *******************************************************************************************************/

#pragma once

#pragma warning(push, 0)	// no warnings from includes
#include <QSharedPointer>
#pragma warning(pop)

#pragma warning (disable: 4251)	// inlined Qt functions in dll interface

#ifndef DllCoreExport
#ifdef DLL_CORE_EXPORT
#define DllCoreExport Q_DECL_EXPORT
#else
#define DllCoreExport Q_DECL_IMPORT
#endif
#endif

// Qt defines
class QSettings;

namespace rdf {


class DllCoreExport GenericSettings {

public:
	GenericSettings() { mName = "GenericSettings"; }

	virtual void load(QSharedPointer<QSettings> ) {};
	virtual void save(QSharedPointer<QSettings> , const GenericSettings& , bool = false) const {};

protected:
	virtual void defaultSettings() {};

	QString mName = "DkGenericSettings";
};

class DllCoreExport GlobalSettings : public GenericSettings {

public:
	GlobalSettings();

	void load(QSharedPointer<QSettings> settings) override;
	void save(QSharedPointer<QSettings> settings, const GenericSettings& init, bool force = false) const override;

	QString workingDir;
	QString settingsFileName;
	QString xmlSubDir;
	QString superPixelClassifierPath;

	// number of scales in the scale space
	// this value is assigned by ScaleSpaceSuperPixel
	int numScales = 1;

protected:
	void defaultSettings() override;
};

// read defines
class DllCoreExport Config {

public:
	static Config& instance();
	static GlobalSettings& global();	// convenience
	QSettings& settings();

	void load();
	void save() const;

	bool isPortable() const;
	void setSettingsFile(const QString& filePath);
	QString settingsFilePath() const;

private:
	Config();
	Config(const Config&);

	QString settingsPath() const;

	GlobalSettings& globalIntern();

	QSharedPointer<QSettings> mSettings;
	GlobalSettings mGlobal;
	GlobalSettings mGlobalInit;

};

};