/*
 * Hacking construction kit -- A GPL Windows security library.
 * While this library can potentially be used for nefarious purposes, 
 * it was written for educational and recreational
 * purposes only and the author does not endorse illegal use.
 *
 * This library is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 *
 * You should have received a copy of the GNU General Public License
 * along with this library.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Author: thirdstormofcythraul@outlook.com
 */
#pragma once

#include <vector>
#include <string>

#include <Windows.h>

/**
* Utility class for files management
*/
class File {

public:
	/**
	* Find files in folder recursively
	* vector<string> result as an array of files
	* path to search ex: "c:\\"
	* filename ex: "file.doc", can be empty
	* totalSize: totalSize for the files found
	* minSize: minimum size for file in bytes, 0 to report all files
	* maxSize: maximum size for file in bytes, 0 to report all files
	* exactSearch: filename must match exactly
	*/
	static bool findFile(std::vector<std::wstring>& files, std::wstring path, std::wstring filename, 
		DWORD &totalSize, DWORD minSize = 0, DWORD maxSize = 0, bool exactSearch = false);

	/**
	* Replace a string by another string in a file
	* filein: original file
	* fileout: destination file
	* searched: a string to search (without \0)
	* size: size of the string
	* replace: the new string. it'll be padded with \0 to fit the size and keep the file in original size
	*/
	static bool replaceInFile(const std::wstring& filein, const std::wstring& fileout, const char *searched, unsigned int size, const char *replace);

	/**
	* Get devices infos (hdd, cdrom, usb key...)
	* volumes: ex: \\?\Volume{2578cc83-6bfc-22e0-10f1-2542f6e6963}\
	* devices: ex: \Device\HarddiskVolume1
	* paths: ex: c:\
	*/
	static bool getDiskPath(std::vector<std::wstring> &volumes, std::vector<std::wstring> &devices, std::vector<std::wstring> &paths);
	static std::wstring displayVolumePaths(wchar_t *volumeName);

	/**
	* list files and directory from a path
	* path: ex: c:
	* files: all files in path
	* directories: all directories in path
	*/
	static bool listDirectory(std::wstring path, std::vector<std::wstring> &files, std::vector<std::wstring> &directories);

	/**
	* list files and directory from a path
	* path: ex: c:
	* files: all files and directory in path
	* directory will start with >
	* 
	*/
	static bool listDirectory(std::wstring path, std::vector<std::wstring> &files);

	static std::wstring fileTimeToString(FILETIME *filetime);

	static bool compare(std::wstring str1, std::wstring str2, bool exact);

	static void addFileInfoToStr(WIN32_FIND_DATA& ffd, std::vector<std::wstring>& files);

};