#include "stdafx.h"
#include "FileManager.h"
#include "Config.h"

#if defined(_MSC_VER)
#if _MSC_VER <= 1400
extern "C"
int __cdecl _input(FILE *, const unsigned char *, va_list);
#else
extern "C"
int __cdecl _input_l(FILE*, unsigned char*, _locale_t, va_list);
#endif
#endif

PFILE_STD::PFILE_STD()
	: m_fp(NULL)
{

}

PFILE_STD::~PFILE_STD()
{
	Close();
}

int	PFILE_STD::Scanf(const char* format, va_list arglist)
{
#if defined(_MSC_VER)
#if _MSC_VER <= 1400
	return (_input(m_fp, reinterpret_cast<unsigned char*>(const_cast<char *>(format) ), arglist) );
#else
	return (_input_l(m_fp, reinterpret_cast<unsigned char*>(const_cast<char *>(format) ), NULL, arglist ) );
#endif
#endif
}

char* PFILE_STD::Gets(char* string, int count)
{
	return fgets(string, count, m_fp);
}

int PFILE_STD::Getc()
{
	return ::getc(m_fp);
}

int	PFILE_STD::Seek(long int offset, int whence)
{
	return fseek(m_fp, offset, whence);
}

PFILE* PFILE_STD::Open(const char* filename, const char* mode)
{
	m_fp = fopen(filename, mode);

	if( m_fp == NULL )
	{
		delete this;
		return NULL;
	}

	return this;
}

void PFILE_STD::Close()
{
	if( m_fp != NULL )
		fclose(m_fp);

	m_fp = NULL;
}

size_t PFILE_STD::Read(void* ptr, size_t size, size_t n)
{
	return fread(ptr, size, n, m_fp);
}

int	PFILE_STD::Tell()
{
	return ftell(m_fp);
}
//////////////////////////////////////////////////////////////////////////
PFILE_NFS::PFILE_NFS()
	: m_vfp(NULL)
{

}

PFILE_NFS::~PFILE_NFS()
{
	Close();
}

int PFILE_NFS::Scanf(const char* format, va_list arglist)
{
	return vfscanf(m_vfp, format, arglist);
}

char* PFILE_NFS::Gets(char* string, int count)
{
	return vfgets(string, count, m_vfp);
}

int	PFILE_NFS::Getc()
{
	return vgetc(m_vfp);
}

int	PFILE_NFS::Seek(long int offset, int whence)
{
	return vfseek(m_vfp, offset, whence);
}

PFILE* PFILE_NFS::Open(const char* filename, const char* mode)
{
	m_vfp = vfopen(filename, mode);

	if( m_vfp == NULL )
	{
		delete this;
		return NULL;
	}

	return this;
}

void PFILE_NFS::Close()
{
	if( m_vfp != NULL )
		vfclose(m_vfp);

	m_vfp = NULL;
}

size_t PFILE_NFS::Read(void* ptr, size_t size, size_t n)
{
	return vfread(ptr, size, n, m_vfp);
}

int PFILE_NFS::Tell()
{
	return vftell(m_vfp);
}

//////////////////////////////////////////////////////////////////////////
FileManager::FileManager()
	: m_eFileType(eFILE_TYPE_NFS)
{
	FILE* fp = fopen("pack.cfg", "rt");
	if( fp != NULL )
	{
		int nUnPack = 0;
		fscanf(fp, "%d", &nUnPack);

		if( nUnPack == 1 )
			m_eFileType = eFILE_TYPE_STD;

		fclose(fp);
	}
}

FileManager::~FileManager()
{

}

int	FileManager::Scanf(PFILE* stream, const char* format, ...)
{
	int ret = 0;
	va_list arglist;
	va_start(arglist, format);
	ret = stream->Scanf(format, arglist);
	va_end(arglist);

	return ret;
}

char* FileManager::Gets(char* string, int count, PFILE* stream)
{
	return stream->Gets(string, count);
}

int FileManager::Getc(PFILE* stream)
{
	return stream->Getc();
}

int FileManager::Seek(PFILE* stream, long int offset, int whence)
{
	return stream->Seek(offset, whence);
}

PFILE* FileManager::Open(const char* filename, const char* mode, bool forceStd)
{
	PFILE* fp = NULL;

	if( m_eFileType == eFILE_TYPE_STD || (forceStd == true) )
		fp = new PFILE_STD();
	else if( m_eFileType == eFILE_TYPE_NFS )
		fp = new PFILE_NFS();

	return fp->Open(filename, mode);
}

void FileManager::Close(PFILE* fp)
{
	if( fp != NULL )
		fp->Close();

	SAFE_DELETE(fp);
}

size_t FileManager::Read(void* ptr, size_t size, size_t n, PFILE* stream)
{
	return stream->Read(ptr, size, n);
}

int FileManager::Tell(PFILE* stream)
{
	return stream->Tell();
}

void FileManager::PackInit()
{
	if( m_eFileType == eFILE_TYPE_NFS )
		vPackInitialize();
}

void FileManager::PackUninit()
{
	if( m_eFileType == eFILE_TYPE_NFS )
		vPackUninitialize();
}