/*
 * Author: thirdstormofcythraul@outlook.com
 */
#include "czip.h"

#define ZLIB_WINAPI

#include "lib/zlib/zlib.h"
#include "lib/zlib/contrib/minizip/zip.h"

#pragma comment(lib, "zlibstat.lib")

#define WRITEBUFFERSIZE 2048

using namespace std;

uLong filetime(const char * f, tm_zip * tmzip, uLong * dt){
  int ret = 0;
  {
      FILETIME ftLocal;
      HANDLE hFind;
      WIN32_FIND_DATAA ff32;

      hFind = FindFirstFileA(f,&ff32);
      if (hFind != INVALID_HANDLE_VALUE)
      {
        FileTimeToLocalFileTime(&(ff32.ftLastWriteTime),&ftLocal);
        FileTimeToDosDateTime(&ftLocal,((LPWORD)dt)+1,((LPWORD)dt)+0);
        FindClose(hFind);
        ret = 1;
      }
  }
  return ret;
}

int Zip::compressFiles(const std::wstring& sourcePath, const std::vector<std::wstring>& files, const std::wstring& output){
	char buffer[Zip::WRITE_BUFFER_SIZE];
	wstring localSourcePath = sourcePath;
	zipFile zf = zipOpen(tosS(output).c_str(), APPEND_STATUS_CREATE);
	if (zf == 0){
		return 3;
	}

	for (unsigned int i= 0; i < files.size(); i++) {
	
		string fileToZip;

		if (sourcePath.size() == 0){
			fileToZip = tosS(files[i]);
		} else {
			fileToZip = tosS(localSourcePath.append(L"\\").append(files[i]));
		}
		
		zip_fileinfo fileInfo = {};
		ZeroMemory( &fileInfo.tmz_date, sizeof( fileInfo.tmz_date ) );

		filetime(fileToZip.c_str(), &fileInfo.tmz_date, &fileInfo.dosDate);

		int error = zipOpenNewFileInZip2(zf, fileToZip.c_str(),
			&fileInfo, 0, 0, 0, 0, 
			0,
			Z_DEFLATED,
			Z_DEFAULT_COMPRESSION, 0
			);
		if (error != ZIP_OK) {
			zipClose(zf, 0);
			return 4;
		}

		FILE *fin;
		if (fopen_s(&fin, fileToZip.c_str(), "rb") != 0) {
			zipClose(zf, NULL);
			return 5;
		}

		int	size_read;
		do {
			size_read = (int)fread(&buffer, 1, Zip::WRITE_BUFFER_SIZE, fin);
			if (size_read < Zip::WRITE_BUFFER_SIZE)
				if (feof(fin) == 0)	{
					zipClose(zf, 0);
					fclose(fin);
					return 6;
				}

				if (size_read > 0) {
					error = zipWriteInFileInZip (zf, &buffer, size_read);
					if (error < 0) {
						zipClose(zf, 0);
						fclose(fin);
						return 7;
					}
				}

		} while (size_read > 0);

		if (fin){
			fclose(fin);
		}

		error = zipCloseFileInZip(zf);
		if (error != ZIP_OK) {
			zipClose(zf, 0);
			return 8;
		}
	}

	int errclose = zipClose(zf, 0);
	if (errclose != ZIP_OK)	{
		return 9;
	}

	return 10;

}