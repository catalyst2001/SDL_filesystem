/*
  SDL_filesystem: A extended filesystem library for use with SDL
  Copyright (C) 2025  Kirill Deryabin <kd@allalg.ru>, Daniil Runin <daniluk2@allalg.ru>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/
#ifndef SDL_FS_H_
#define SDL_FS_H_
#include <SDL.h>

//HACK: K.D. remove this with upgrade to SDL3+
#include "begin_code.h"
#define SDL_DECLSPEC DECLSPEC

 /* Set up for C function definitions, even when using C++ */
#pragma region FS_API
#ifdef __cplusplus
extern "C" {
#endif

typedef enum SDLFS_STATUS {
  SDL_FS_STATUS_SUCCESS = 0,
} SDL_FS_STATUS;

#define SDL_FS_SUCCESS(status) ((status) == SDL_FS_STATUS_SUCCESS)

/**
* SDLFS ioctl codes
*/



/**
* @brief Initialize filesystem library
*/
extern SDL_DECLSPEC SDLFS_STATUS SDLCALL SDLFS_Init();

/**
* @brief Deinitialize filesystem library
*/
extern SDL_DECLSPEC SDLFS_STATUS SDLCALL SDLFS_Quit();


extern SDL_DECLSPEC SDLFS_STATUS SDLCALL SDLFS_AddSearchPathEx(const char *ppath, const char *ppathid, int is_override);

extern SDL_DECLSPEC SDLFS_STATUS SDLCALL SDLFS_GetSearchPath(const char* ppathid);

/**
* File API
*/
typedef struct SDLFS_file* SDLFS_hfile;
extern SDL_DECLSPEC SDLFS_STATUS SDLCALL SDLFS_OpenFileEx(SDLFS_hfile *dst);

extern SDL_DECLSPEC SDLFS_STATUS SDLCALL SDLFS_WriteEx(SDLFS_hfile hfile, const void *psrc_data, size_t *psrc_len);

extern SDL_DECLSPEC SDLFS_STATUS SDLCALL SDLFS_ReadEx(void *pdst, size_t *pread_len, SDLFS_hfile hfile);

extern SDL_DECLSPEC SDLFS_STATUS SDLCALL SDLFS_GetFilenameByFileHandle(char *pdst, size_t maxlen, SDLFS_hfile hfile);

/**
* async IO
*/
typedef SDLFS_STATUS (SDLCALL* SDLFS_IO_routine)(SDLFS_hfile hfile);
typedef SDLFS_STATUS (SDLCALL* SDLFS_IO_complete_routine)(SDLFS_hfile hfile);

typedef struct SDLFS_IO_async {
  SDLFS_IO_routine          pIO_routine;
  SDLFS_IO_complete_routine pIO_complete;
} SDLFS_IO_async;

extern SDL_DECLSPEC SDLFS_STATUS SDLCALL SDLFS_WriteAsyncEx(SDLFS_hfile hfile, SDLFS_IO_async *pIO_async_struct);
extern SDL_DECLSPEC SDLFS_STATUS SDLCALL SDLFS_ReadAsyncEx(SDLFS_hfile hfile, SDLFS_IO_async* pIO_async_struct);

extern SDL_DECLSPEC SDLFS_STATUS SDLCALL SDLFS_GetStatus(SDLFS_hfile hfile);
extern SDL_DECLSPEC SDLFS_STATUS SDLCALL SDLFS_Truncate(SDLFS_hfile hfile);
extern SDL_DECLSPEC SDLFS_STATUS SDLCALL SDLFS_Resize(SDLFS_hfile hfile, Uint64 newsize);
extern SDL_DECLSPEC SDLFS_STATUS SDLCALL SDLFS_GetSize(Uint64* dstsize, SDLFS_hfile hfile);
extern SDL_DECLSPEC SDLFS_STATUS SDLCALL SDLFS_Close(SDLFS_hfile *pfile);

/**
* Working with directories
* 
*/
typedef struct SDLFS_dir *SDLFS_hdir;

extern SDL_DECLSPEC SDLFS_STATUS SDLCALL SDLFS_OpenDir(SDLFS_hdir* dst, const char* p_path, const char* p_pathid = nullptr);
extern SDL_DECLSPEC SDLFS_STATUS SDLCALL SDLFS_ReadDir(SDLFS_hdir src);
extern SDL_DECLSPEC SDLFS_STATUS SDLCALL SDLFS_CloseDir(SDLFS_hdir* src);
extern SDL_DECLSPEC SDLFS_STATUS SDLCALL SDLFS_CreateDirectory();
extern SDL_DECLSPEC SDLFS_STATUS SDLCALL SDLFS_RemoveDirectory();
extern SDL_DECLSPEC SDLFS_STATUS SDLCALL SDLFS_MoveFile();
extern SDL_DECLSPEC SDLFS_STATUS SDLCALL SDLFS_DeleteFile();
extern SDL_DECLSPEC SDLFS_STATUS SDLCALL SDLFS_CreateTempFile();

extern SDL_DECLSPEC SDLFS_STATUS SDLCALL SDLFS_SetCurrentPath();
extern SDL_DECLSPEC SDLFS_STATUS SDLCALL SDLFS_GetCurrentPath();

/**
* assets API
*/
typedef struct SDLFS_hasset* SDLFS_hasset;

typedef struct SDLFS_asset_descriptor {

} SDLFS_asset_descriptor;

extern SDL_DECLSPEC SDLFS_STATUS SDLCALL SDLFS_CreateAsset(SDLFS_hasset *passet, SDLFS_asset_descriptor *passet_descriptor);
extern SDL_DECLSPEC SDLFS_STATUS SDLCALL SDLFS_CloseAsset(SDLFS_hasset *passet);

#ifdef __cplusplus
};
#endif
#pragma endregion

#endif //SDL_FS_H_